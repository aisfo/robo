import socket


bd_addr = "20:15:07:02:05:92"
port = 1
connection = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)


def connect():
    log("Connecting to body...")
    connection.connect((bd_addr, port))
    log("Connected to body at {0} :: {1}".format(bd_addr, port))

def close():
    connection.close()

def log(msg):
    print("BODY [LOG] :: {}".format(msg))


# commands: 
# 1 - MOVE_TO(joint_id, value)
# 2 - MOVE_BY(joint_id, value)
def send(msg):
    log("Sending the message: {}".format(msg))
    msg += "\n"
    connection.send(msg.encode())

def moveTo(jointId, value):
    send("1 {0} {1}".format(jointId, value))

def moveBy(jointId, value):
    send("2 {0} {1}".format(jointId, value))

