import serial
import socket
import bluetooth


# with serial.Serial('/dev/rfcomm0', 9600) as ser:
#     print("Connected to {}".format(ser.name))
    
#     while True:
#         s = input()
#         ser.write(s.encode())
    # inp = ser.read(1)
    # print(inp)
    # while True:
    #     inp = ser.read(1)
    #     print("New byte: {}".format(inp))

bd_addr = "20:15:07:02:05:92"
port = 1 #1

# s = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
with socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM) as s:
    s.connect((bd_addr, port))

    while(1):
        msg = input("enter message:\n")
        if msg == "quit":
            break
        
        s.send(msg.encode())
        #s.recv(1024)

# commands: 
# 1 - MOVE_TO(joint_id, value)
# 2 - MOVE_BY(joint_id, value)