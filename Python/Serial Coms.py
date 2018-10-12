import serial
import struct
import time

##open a port with no timeout

##ser = serial.Serial('/dev/ttyACM0')  # open serial port
##print(ser.name)         # check which port was really used
##ser.write(b'hello')     # write a string
##ser.close()             # close port

##

##Open a port with a 1s timeout

##with serial.Serial('/dev/ttyACM0', 19200, timeout=1) as ser:   
##    x = ser.read()          # read one byte
##    s = ser.read(10)        # read up to ten bytes (timeout)
##    line = ser.readline()   # read a '\n' terminated line

##

##Arduino Test Code


ser = serial.Serial('/dev/ttyACM0')
print (ser.name)
ser.baudrate = 115200
time.sleep(2)

string = ''

while True:
    valueA = 50
    valueB = 100
    delimiter = ','


    string = str(valueA) + delimiter + str(valueB)
    b = bytes(string, 'utf-8')
    print(b)
    ser.write(b)

    valueA = 50
    valueB = 100
    delimiter = ','
    time.sleep(2)   #must have a delay between sends. 


    string = str(valueA) + delimiter + str(valueB)
    b = bytes(string, 'utf-8')
    print(b)
    ser.write(b)

    valueA = 100
    valueB = 50
    delimiter = ','
    time.sleep(2)

    string = str(valueA) + delimiter + str(valueB)
    b = bytes(string, 'utf-8')
    print(b)
    ser.write(b)
    time.sleep(2)
