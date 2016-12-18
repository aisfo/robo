import socket
import signal
import sys


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

RESET = 1
MOVE_TO = 2
MOVE_BY = 3
READ_ORIENTATION = 4

bd_addr = "20:15:07:02:05:92"
port = 1



class Robot():

    def __init__(self):
        self.connection = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)


    # Connection

    def connect(self):
        log("Connecting to body...")
        self.connection.connect((bd_addr, port))
        log("Connected to body at {0} :: {1}".format(bd_addr, port))


    def close(self):
        log("Disconnecting from body...")
        self.connection.shutdown(2)
        self.connection.close()


    def send(self, msg):
        log("Sending the message :: {}".format(msg))
        msg += '\x04'
        connection.send(msg.encode())


    # Commands: 

    # 0 RESET()
    def reset(self):
        self.send("{0}".format(RESET))


    # 1 MOVE_TO(joint_id, value)
    def moveTo(self, jointId, value):
        self.send("{0} {1} {2}".format(MOVE_TO, jointId, value))


    # 2 MOVE_BY(joint_id, value)
    def moveBy(self, jointId, value):
        self.send("{0} {1} {2}".format(MOVE_BY, jointId, value))


    # 4 READ_ORIENTATION()
    def readOrientation(self):
        self.send("{0}".format(READ_ORIENTATION))

        values = []
        temp = ""
        start = False

        while(True):
            data = self.connection.recv(1)
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
    print("DRIVER {0} :: {1}".format(level, msg))


def run_script(script_to_run):
    robot = Robot()

    def exit(signal, frame):
        if robot: robot.close()
        sys.exit(0)

    signal.signal(signal.SIGINT, exit)

    try:
        robot.connect()
        script_to_run(robot)
    except Exception as e:
        print(e)

    exit(None, None)


