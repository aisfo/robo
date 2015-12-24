from time import sleep

import script
import body

def simple_walking():
    body.reset()
    
    for i in range(0,2):

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

        sleep(0.4)

        body.reset()


if __name__ == '__main__':
    script.run(simple_walking)