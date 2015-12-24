import socket


# Joint IDs

NE0 = 0
NE1 = 1
NE2 = 2 
SE0 = 3
SE1 = 4
SE2 = 5 
SW0 = 6 
SW1 = 7
SW2 = 8 
NW0 = 9
NW1 = 10
NW2 = 11


# Connection

bd_addr = "20:15:07:02:05:92"
port = 1
connection = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)

def connect():
    log("Connecting to body...")
    connection.connect((bd_addr, port))
    log("Connected to body at {0} :: {1}".format(bd_addr, port))

def close():
    log("Disconnecting from body...")
    connection.shutdown(2)
    connection.close()

def send(msg):
    log("Sending the message :: {}".format(msg))
    msg += '\x04'
    connection.send(msg.encode())


# Commands: 

# 0 RESET()
def reset():
    send("1")

# 1 MOVE_TO(joint_id, value)
def moveTo(jointId, value):
    send("2 {0} {1}".format(jointId, value))

# 2 MOVE_BY(joint_id, value)
def moveBy(jointId, value):
    send("3 {0} {1}".format(jointId, value))

# 4 READ_ORIENT()
def readOrientation():
    send("4")

    values = []
    temp = ""
    start = False

    while(True):
        data = connection.recv(1)
        if data == b'\x02': # start of text
            start = True
        elif data == b'\x1f': # value separator 
            values.append(temp)
            temp = ""
        elif data == b'\x03': # end of text
            values.append(temp)
            break
        elif start:
            temp += data.decode("utf-8")

    return values


# Helpers

def log(msg, level="LOG"):
    print("BODY [{0}] :: {1}".format(level, msg))
