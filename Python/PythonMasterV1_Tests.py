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

import IMU  ##Change to name of IMU code
'''#########################################'''

################################## Serial out Setup ###############################
Arduino = serial.Serial('/dev/ttyACM0')  ##Define a Serial Port
print (Arduino.name)                     ##Print The Serial Port
Arduino.baudrate = 115200                ##Define the Baudrate. Must Match Arduino Code
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

##################################### GPS Setup ###################################
waypoint_lat = 30
waypoint_long = 50
uart = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3000)
gps = adafruit_gps.GPS(uart, debug=False)
gps.send_command(b'PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0')
gps.send_command(b'PMTK220,1000')
last_print = time.monotonic()
'''#############################################################################'''

##################################### IMU Setup ###################################
IMU = serial.Serial(
    port='COM10',
    baudrate=115200,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)
IMU.isOpen()

total = 0
averageCounter = 0
average = 0

command = "#o1"
print(command)
send = bytes(command, 'utf-8')
IMU.write(send)

command = "#osn"
print(command)
send = bytes(command, 'utf-8')
IMU.write(send)

'''#############################################################################'''


while True:
    updateGPS()
    getCurrentHeading()              ##Get heading from IMU magnetometer code
    getWayPointHeading()             ##Get heading from GPS (description below)
    getDistance()                    ##Get distance from GPS (description below)
    checkStatus()                    ##If the boat is closer than the max range the enable docking mode
    updateMotors()                   ##Update the motors, based on required and current headings
    toArduino()                      ##Send status and motor values to Arduino

def updateGPS():
    gps.update()
    # Every second print out current location details if there's a fix.
    current = time.monotonic()
    if current - last_print >= 1.0:
        last_print = current
        if not gps.has_fix:
            # Try again if we don't have a fix yet.
            print('Waiting for fix...')
            continue
        lat = int(gps.latitude)
        longit = int(gps.longitude)

def updateMotors():
    angularDiff = requiredHeading - currentHeading ##Final -Initial
    
    if (abs(angularDiff) > headingRange):            ##If we are outside of the set tolerance:
        if (abs(angularDiff) > 180):                  ##If angular difference is greater than 180, optimize turn:
            if (angularDiff >= 0):                     
                angularDiff = angularDiff - 180
            else:
                angluarDiff - angularDiff + 180
                
            if (angularDiff > 0):                      ##If new angular diff is greater than 0 turn LEFT
                rightMotor = maxSpeed/turnFactor
                leftMotor = -maxSpeed/turnFactor
            else:                                    ##Else angular diff is less than 0 turn RIGHT
                rightMotor = -maxSpeed/turnFactor
                leftMotor = maxSpeed/turnFactor
                
        elif (abs(angularDiff) == 180):            ##Else If angular difference is 180, turn RIGHT
                rightMotor = -maxSpeed/turnFactor
                leftMotor = maxSpeed/turnFactor
        
        else:                                        ##Else no optimization is required
            if (angularDiff > 0):                       ##If required > current turn right
                rightMotor = -maxSpeed/turnFactor
                leftMotor = maxSpeed/turnFactor
            else:                                     ##Else required < current turn left
                rightMotor = maxSpeed/turnFactor
                leftMotor = -maxSpeed/turnFactor
    else:                                           ##Else if we are in the set tolerance FULL SPEED AHEAD
        rightMotor = maxSpeed   
        leftMotor = maxSpeed
        

def checkStatus():
    if waypointDistance > maxRange:
        status = 0
    else:
        status = 1

def getCurrentHeading():
    currentHeading = IMU.heading()
    line = IMU.readline().strip()

    strLine = str(line.decode('utf-8'))
    rawHeading = float(strLine)

    calHeading = rawHeading

    if(averageCounter == 5):
        average = total / 5
        total = 0
        averageCounter = 0

    if(averageCounter < 5):
        total = total+calHeading
        averageCounter = averageCounter + 1

    

def getWaypointHeading():
    requiredHeading = calculate_initial_compass_bearing(longit, lat, waypoint_long, waypoint_lat)
    
def getDistance():
    waypointDistance = haversine(longit, lat, waypoint_long, waypoint_lat)


def toArduino():
    string = str(status) + delimiter + str(leftMotor) + delimiter + str(rightMotor)
    b = bytes(string, 'utf-8')
    print(b)
    Arduino.write(b)
    #time.sleep(2)   #must have a delay between sends. 
