################## Libraries ##################
import serial
import struct
import time
import board
import busio
import adafruit_gps
'''#########################################'''

################# Add. Codes ##################
from HaversineFunction import haversine
from BearingAngleFunction import calculate_initial_compass_bearing
'''#########################################'''

#################################### Motors Setup #################################
rightMotor = 0                       ##Motor Values should start at 0
leftMotor = 0
rightMotorTrim = 0                   ##Trim Motor Values (they may not be the same strength out of the box
leftMotorTrim = 0
maxSpeed = 100                       ##Max Value as a percent. The motors may be much stronger than we need them to be
turnFactor = 5                       ##Divide max speed by this factor to slow down turns
headingRange = 10                     ##Allowable Tolerance in degrees
'''#############################################################################'''

################################### Heading Setup #################################
currentHeading = 0                   ##Current Heading of Boat
requiredHeading = 0                  ##Current Required heading to go to the dock
waypointDistance = 0                 ##Distance from boat to waypoint
maxRange = 18                      ##Max Accuaracy of GPS in feet
'''#############################################################################'''


##################################### IMU Setup ###################################
IMU = serial.Serial(
    port='/dev/ttyACM1',
    baudrate=115200,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)
print (IMU.name)
IMU.isOpen()

total = 0
averageCounter = 0
averageHeading = 0

command = "#o1"
print(command)
send = bytes(command, 'utf-8')
IMU.write(send)
print("IMU Ready")

'''#############################################################################'''

################################## Serial out Setup ###############################

Arduino = serial.Serial('/dev/ttyACM0')  ##Define a Serial Port
print (Arduino.name)                     ##Print The Serial Port
Arduino.baudrate = 115200                ##Define the Baudrate. Must Match Arduino Code
time.sleep(2)                        ##Wait for the Serial Communication to begin
string = ''                          ##Creates an empty string to send over Serial
startMark = '<'
endMark = '/'
delimiter = ','                      ##Creates a demiliter for arduino to split the values
status = 0;                          ##Currently used by the docking code in arduino.
                                     ##If 0, run normally, If 1, ignore Python motor Values
'''#############################################################################'''


##################################### GPS Setup ###################################
waypoint_lat = 30.545517
waypoint_long = -87.216602
uart = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=3000)
print(uart.port)
gps = adafruit_gps.GPS(uart, debug=False)
gps.send_command(b'PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0')
gps.send_command(b'PMTK220,1000')
last_print = time.monotonic()
'''#############################################################################'''

def getCurrentHeading():

    #print("IMU")
    IMU.flushInput()
    IMU.flushOutput()
    time.sleep(.1)
    line = IMU.readline().strip()
    strLine = str(line.decode('utf-8'))
    if(strLine):
        rawHeading = float(strLine)
    try:
        calHeading = rawHeading
    except:
        calHeading = 0
        pass
    #print("calHeading = " , calHeading)
    return calHeading



def updateMotors():
    #print("updateMotors")
    
    angularDiff = angle - getCurrentHeading() ##Final -Initial
    #print("Angle = ", angle)
    if (abs(angularDiff) > headingRange):            ##If we are outside of the set tolerance:
    
        if (abs(angularDiff) > 180):                  ##If angular difference is greater than 180, optimize turn:
            if (angularDiff >= 0):                     
                angularDiff = angularDiff - 360
                print("angular Diff = ", angularDiff)
            else:
                angularDiff = angularDiff + 360
                
            if (angularDiff > 0):                      ##If new angular diff is greater than 0 turn RIGHT
                rightMotor = -maxSpeed*abs(angularDiff/180)
                leftMotor = maxSpeed*abs(angularDiff/180)
            else:                                    ##Else angular diff is less than 0 turn LEFT
                rightMotor = maxSpeed*abs(angularDiff/180)
                leftMotor = -maxSpeed*abs(angularDiff/180)
                
        elif (abs(angularDiff) == 180):            ##Else If angular difference is 180, turn RIGHT
                rightMotor = -maxSpeed
                leftMotor = maxSpeed
        
        else:                                        ##Else no optimization is required
            if (angularDiff > 0):                       ##If required > current turn right
                rightMotor = -maxSpeed*abs(angularDiff/180)
                leftMotor = maxSpeed*abs(angularDiff/180)
            else:                                     ##Else required < current turn left
                rightMotor = maxSpeed*abs(angularDiff/180)
                leftMotor = -maxSpeed*abs(angularDiff/180)
    else:                                           ##Else if we are in the set tolerance FULL SPEED AHEAD
        rightMotor = maxSpeed   
        leftMotor = maxSpeed
        
    if(abs(rightMotor) < 20):
        if(rightMotor > 0):
            rightMotor = 20
        if(rightMotor < 0):
            rightMotor = -20
            
    if(abs(leftMotor) < 20):
        if(leftMotor > 0):
            leftMotor = 20
        if(leftMotor < 0):
            leftMotor = -20
            
    #print("angular Diff = ", angularDiff)
    return rightMotor, leftMotor


def getWayPointHeading():
    #print("getWaypointHeading")
    requiredHeading = calculate_initial_compass_bearing(longit, lat, waypoint_long, waypoint_lat)
    
    return requiredHeading

def getDistance():
    #print("getDistance")
    waypointDistance = haversine(longit, lat, waypoint_long, waypoint_lat)
    
    return waypointDistance

def checkStatus():
    #print("checkStatus")
    if distance > maxRange:
        status = 0
    else:
        status = 1
    
    return status

def toArduino():
    #time.sleep(2)   #must have a delay between sends.
    #print("ToArduino")
    rightMotor, leftMotor = updateMotors()
    #print(checkStatus(), " ", leftMotor, " ", rightMotor)
    string = startMark + str(checkStatus()) + delimiter + str(leftMotor) + delimiter + str(rightMotor) + endMark
    b = bytes(string, 'utf-8')
    print(b)
    Arduino.write(b)
    #print("Exit")
    
def newToArduino():
    time.sleep(1)
    string = startMark + str(status) + delimiter + str(leftMotor) + delimiter + str(rightMotor) + endMark
    #string = startMark + str(0) + delimiter + str(50) + delimiter + str(100) + endMark
    b = bytes(string, 'utf-8')
    print(b)
    Arduino.write(b)
    

while True:
    #print("GPS")
    #print(getCurrentHeading())
    
    # Make sure to call gps.update() every loop iteration and at least twice
    # as fast as data comes from the GPS unit (usually every second).
    try:
        gps.update()
    except:
        print("ERROR IN GPS CODE")
        pass
    
    # Every second print out current location details if there's a fix.
    #print("UGH")
    current = time.monotonic()
    if current - last_print >= 1.0:
        last_print = current
        if not gps.has_fix:
            # Try again if we don't have a fix yet.
            print('Waiting for fix...')
            continue
        # We have a fix! (gps.has_fix is true)
        # Print out details about the fix like location, date, etc.
        
        #print('=' * 40)  # Print a separator line.
        #print("loop")
        print('Latitude: {0:.6f} degrees'.format(gps.latitude))
        print('Longitude: {0:.6f} degrees'.format(gps.longitude))
        
        lat = float(gps.latitude)
        longit = float(gps.longitude)
        #print(type(lat))


        angle = getWayPointHeading()             ##Get heading from GPS
        #print("angle = ", angle)
        distance = getDistance()                 ##Get distance from GPS
        print("distance = ", distance)
        #getCurrentHeading()
        #toArduino()                              ##Send status and motor values to Arduino
        status = checkStatus()
        rightMotor,leftMotor = updateMotors()
        rightMotor = round(rightMotor)
        leftMotor = round(leftMotor)
        newToArduino()


        



