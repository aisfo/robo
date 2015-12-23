import body
from time import sleep
import signal
import sys

def exit(signal, frame):
    body.close()
    sys.exit(0)

signal.signal(signal.SIGINT, exit)


try:
    body.connect()

    while(True):
        orientation = body.read()
        print(orientation)

except Exception as e:
    print(e)
    

exit()

