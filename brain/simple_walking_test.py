from time import sleep
import driver


def simple_walking(robot):
    robot.reset()
    
    for i in range(0,2):
        sleep(0.2)

        robot.moveBy(robot.get('SE1'), -10)
        robot.moveBy(robot.get('SE2'), 10)

        robot.moveBy(robot.get('NE1'), 20)
        robot.moveBy(robot.get('NE2'), -10)

        sleep(0.4)

        robot.moveBy(robot.get('SW1'), -20)
        robot.moveBy(robot.get('SW2'), 20)

        robot.moveBy(robot.get('NW1'), 30)
        robot.moveBy(robot.get('NW2'), -20)

        robot.moveBy(robot.get('SE1'), -10)
        robot.moveBy(robot.get('SE2'), 10)

        sleep(0.4)

        robot.reset()


if __name__ == '__main__':
    driver.run_script(simple_walking)