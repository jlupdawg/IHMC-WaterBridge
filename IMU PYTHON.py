import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM10',
    baudrate=115200,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

print ('Enter your commands below.\r\nInsert "exit" to leave the application.')



#command = "#osct"
#command = String(input("Enter command:"))
#type(command)

command = raw_input('Input: ')
print(command)

send = bytes(command, 'utf-8')
ser.write(send)

#print("Sent")

print(ser.read(1000))

