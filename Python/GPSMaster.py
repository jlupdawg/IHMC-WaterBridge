
import time
import board
import busio
import adafruit_gps
import serial
from HaversineFunction import haversine
from BearingAngleFunction import calculate_initial_compass_bearing


###################################################### Change Me ##########################################################
waypoint_lat = 30
waypoint_long = 50
###########################################################################################################################

uart = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3000)

# Create a GPS module instance.
gps = adafruit_gps.GPS(uart, debug=False)

gps.send_command(b'PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0')

# Set update rate to once a second (1hz) which is what you typically want.
gps.send_command(b'PMTK220,1000')

last_print = time.monotonic()

while True:
    # Make sure to call gps.update() every loop iteration and at least twice
    # as fast as data comes from the GPS unit (usually every second).
    gps.update()
    # Every second print out current location details if there's a fix.
    current = time.monotonic()
    if current - last_print >= 1.0:
        last_print = current
        if not gps.has_fix:
            # Try again if we don't have a fix yet.
            print('Waiting for fix...')
            continue
        
        #print('Latitude: {0:.6f} degrees'.format(gps.latitude))
        #print('Longitude: {0:.6f} degrees'.format(gps.longitude))
        
        lat = int(gps.latitude)
        long = int(gps.longitude)

        distance = haversine(long, lat, waypoint_long, waypoint_lat)
        angle = calculate_initial_compass_bearing(long, lat, waypoint_long, waypoint_lat)

        
        
        
        '''
        if gps.satellites is not None:
            print('# satellites: {}'.format(gps.satellites))
        if gps.altitude_m is not None:
            print('Altitude: {} meters'.format(gps.altitude_m))
        if gps.track_angle_deg is not None:
            print('Speed: {} knots'.format(gps.speed_knots))
        if gps.track_angle_deg is not None:
            print('Track angle: {} degrees'.format(gps.track_angle_deg))
        if gps.horizontal_dilution is not None:
            print('Horizontal dilution: {}'.format(gps.horizontal_dilution))
        if gps.height_geoid is not None:
            print('Height geo ID: {} meters'.format(gps.height_geoid))
        '''
