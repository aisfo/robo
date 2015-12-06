import serial
from time import sleep

with serial.Serial('/dev/rfcomm0', 9600) as ser:
    print("Connected to {}".format(ser.name))
    
    while True:
        s = input()
        ser.write(s.encode())
    # inp = ser.read(1)
    # print(inp)
    # while True:
    #     inp = ser.read(1)
    #     print("New byte: {}".format(inp))

