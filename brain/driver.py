import socket
import signal
import sys



bd_addr = "20:15:07:02:05:92"
port = 1


class Robot():

    def __init__(self):
        #self.connection = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        self.config = read_config()


    def get(self, key):
        if key in self.config:
            return self.config[key]
        return None


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
        msg += '\n'
        connection.send(msg.encode())


    # Commands: 

    def reset(self):
        # RESET()
        self.send("{0}".format(self.get('RESET')))


    def moveTo(self, jointId, value):
        # MOVE_TO(joint_id, value)
        self.send("{0} {1} {2}".format(self.get('MOVE_TO'), jointId, value))


    def moveBy(self, jointId, value):
        # MOVE_BY(joint_id, value)
        self.send("{0} {1} {2}".format(self.get('MOVE_BY'), jointId, value))


    def readOrientation(self):
        # READ_ORIENTATION()
        self.send("{0}".format(self.get('READ_ORIENTATION')))

        msg_string = readMessage(self.connection)
        values = msg_string.split()
        return {
            roll: values[0],
            pitch: values[1],
            yaw: values[2]
        }



# Helpers

def read_config():
    config = {}
    with open('../body/common.h') as f:
      content = f.readlines()
      for line in content:
        line = line.split()
        if len(line) >= 3 and line[0] == "#define":
          key = line[1]
          value = line[2]
          config[key] = value

    return config


def readMessage(conn):
    msg_string = ""
    while(True):
        data = self.connection.recv(1).decode("utf-8")
        if data == '\n':
            return msg_string
        else:
            msg_string += data


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




