import socket


bd_addr = "20:15:07:02:05:92"
port = 1
connection = None


def connect():
    log("Connecting to body...")
    global connection
    connection = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
    connection.connect((bd_addr, port))
    log("Connected to body at {0} :: {1}".format(bd_addr, port))

# commands: 
# 1 - MOVE_TO(joint_id, value)
# 2 - MOVE_BY(joint_id, value)
def send(msg):
    if connection is None:
        raise BodyError("Missing connection")
    log("Sending the message: {}".format(msg))
    msg += "\n"
    connection.send(msg.encode())

def moveTo(jointId, value):
    send("1 {0} {1}".format(jointId, value))

def moveBy(jointId, value):
    send("2 {0} {1}".format(jointId, value))

def close():
    if connection is not None:
        connection.close()

def log(msg):
    print("BODY [LOG] :: {}".format(msg))



class BodyError(Exception):
    def __init__(self, reason):
        self.reason = reason
    def __str__(self):
        return "BODY [ERROR] :: {}".format(self.reason)

    # while(1):
    #     msg = input("enter message:\n")
    #     if msg == "quit":
    #         break
        
    #     s.send(msg.encode())
    #     #s.recv(1024)

