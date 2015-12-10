import body
from time import sleep


try:
    body.connect()
    body.reset()
    
    for i in range(0,5):

        sleep(0.2)

        body.moveBy(body.SE1, -10)
        body.moveBy(body.SE2, 10)

        body.moveBy(body.NE1, 20)
        body.moveBy(body.NE2, -10)

        sleep(0.4)

        body.moveBy(body.SW1, -20)
        body.moveBy(body.SW2, 20)

        body.moveBy(body.NW1, 30)
        body.moveBy(body.NW2, -20)

        body.moveBy(body.SE1, -10)
        body.moveBy(body.SE2, 10)

        sleep(0.7)

        body.reset()

except Exception as e:
    print(e)
    

body.close()