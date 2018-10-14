################## Libraries ##################
import serial
import struct
import time
'''#########################################'''

################# Add. Codes ##################
import GPS  ##Change to name of GPS code
import IMU  ##Change to name of IMU code
'''#########################################'''

################################## Serial out Setup ###############################
ser = serial.Serial('/dev/ttyACM0')  ##Define a Serial Port
print (ser.name)                     ##Print The Serial Port
ser.baudrate = 115200                ##Define the Baudrate. Must Match Arduino Code
time.sleep(2)                        ##Wait for the Serial Communication to begin
string = ''                          ##Creates an empty string to send over Serial
delimiter = ','                      ##Creates a demiliter for arduino to split the values
status = 0;                          ##Currently used by the docking code in arduino.
                                     ##If 0, run normally, If 1, ignore Python motor Values
'''#############################################################################'''

#################################### Motors Setup #################################
rightMotor = 0                       ##Motor Values should start at 0
leftMotor = 0
rightMotorTrim = 0                   ##Trim Motor Values (they may not be the same strength out of the box
leftMotorTrim = 0
maxSpeed = 100                       ##Max Value as a percent. The motors may be much stronger than we need them to be
turnFactor = 4                       ##Divide max speed by this factor to slow down turns
headingRange = 1                     ##Allowable Tolerance in degrees
'''#############################################################################'''

################################### Heading Setup #################################
currentHeading = 0                   ##Current Heading of Boat
requiredHeading = 0                  ##Current Required heading to go to the dock
waypointDistance = 0                 ##Distance from boat to waypoint
maxRange = 18                        ##Max Accuaracy of GPS in feet
'''#############################################################################'''

while True:
    getCurrentHeading()              ##Get heading from IMU magnetometer code
    getWayPointHeading()             ##Get heading from GPS (description below)
    getDistance()                    ##Get distance from GPS (description below)
    checkStatus()                    ##If the boat is closer than the max range the enable docking mode
    updateMotors()                   ##Update the motors, based on required and current headings
    toArduino()                      ##Send status and motor values to Arduino

def updateMotors()
    angularDiff = requiredHeading - currentHeading ##Final -Initial
    
    if abs(angularDiff) > headingRange:            ##If we are outside of the set tolerance:
        if abs(angularDiff) > 180:                  ##If angular difference is greater than 180, optimize turn:
            if angularDiff >= 0:                     
                angularDiff = angularDiff - 180
            else:
                angluarDiff - angularDiff + 180
                
            if angularDiff > 0:                      ##If new angular diff is greater than 0 turn LEFT
                rightMotor = maxSpeed/turnFactor
                leftMotor = -maxSpeed/turnFactor
            else:                                    ##Else angular diff is less than 0 turn RIGHT
                rightMotor = -maxSpeed/turnFactor
                leftMotor = maxSpeed/turnFactor
                
        else if  abs(angularDiff) == 180:            ##Else If angular difference is 180, turn RIGHT
                rightMotor = -maxSpeed/turnFactor
                leftMotor = maxSpeed/turnFactor
        
        else:                                        ##Else no optimization is required
            if angularDiff > 0:                       ##If required > current turn right
                rightMotor = -maxSpeed/turnFactor
                leftMotor = maxSpeed/turnFactor
            else:                                     ##Else required < current turn left
                rightMotor = maxSpeed/turnFactor
                leftMotor = -maxSpeed/turnFactor
    else:                                           ##Else if we are in the set tolerance FULL SPEED AHEAD
        rightMotor = maxSpeed   
        leftMotor = maxSpeed
        

def checkStatus()
    if waypointDistance > maxRange:
    status = 0
    else:
    status = 1

def getCurrentHeading()
    currentHeading = IMU.heading()
    ##pull heading directly from the IMU

def getWaypointHeading()
    requiredHeading = GPS.reqHeading()
    ##determine the required angle to get to the waypoint, directly
    '''
def calculate_initial_compass_bearing(pointA, pointB):
    """
    Calculates the bearing between two points.
    The formulae used is the following:
        θ = atan2(sin(Δlong).cos(lat2),
                  cos(lat1).sin(lat2) − sin(lat1).cos(lat2).cos(Δlong))
    :Parameters:
      - `pointA: The tuple representing the latitude/longitude for the
        first point. Latitude and longitude must be in decimal degrees
      - `pointB: The tuple representing the latitude/longitude for the
        second point. Latitude and longitude must be in decimal degrees
    :Returns:
      The bearing in degrees
    :Returns Type:
      float
    """
    if (type(pointA) != tuple) or (type(pointB) != tuple):
        raise TypeError("Only tuples are supported as arguments")

    lat1 = math.radians(pointA[0])
    lat2 = math.radians(pointB[0])

    diffLong = math.radians(pointB[1] - pointA[1])

    x = math.sin(diffLong) * math.cos(lat2)
    y = math.cos(lat1) * math.sin(lat2) - (math.sin(lat1)
            * math.cos(lat2) * math.cos(diffLong))

    initial_bearing = math.atan2(x, y)

    # Now we have the initial bearing but math.atan2 return values
    # from -180° to + 180° which is not what we want for a compass bearing
    # The solution is to normalize the initial bearing as shown below
    initial_bearing = math.degrees(initial_bearing)
    compass_bearing = (initial_bearing + 360) % 360

    return compass_bearing
    '''

def getDistance()
    waypointDistance = GPS.getDistance()
    ##use the haversine formula to find the distance between the coordinates of the
    ##waypoint and the coordinates of the boat (in feet)
    
    '''
from math import radians, cos, sin, asin, sqrt

def haversine(lon1, lat1, lon2, lat2):
    """
    Calculate the great circle distance between two points 
    on the earth (specified in decimal degrees)
    """
    # convert decimal degrees to radians 
    lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])

    # haversine formula 
    dlon = lon2 - lon1 
    dlat = lat2 - lat1 
    a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
    c = 2 * asin(sqrt(a)) 
    r = 3956 # Radius of earth in miles
    return c * r
    '''

def toArduino()
    string = str(status) + delimiter + str(leftMotor) + delimiter + str(rightMotor)
    b = bytes(string, 'utf-8')
    print(b)
    ser.write(b)
    #time.sleep(2)   #must have a delay between sends. 
