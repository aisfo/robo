import body
from time import sleep


try:
    body.connect()
    body.send("2 0 10")
    sleep(1)
    body.moveTo(0, -180)
except Exception as e:
    print(e)
    

body.close()

