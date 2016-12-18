from time import sleep
import driver


def simple_walking(robot):
    robot.reset()
    
    for i in range(0,2):
        sleep(0.2)

        robot.moveBy(driver.SE1, -10)
        robot.moveBy(driver.SE2, 10)

        robot.moveBy(driver.NE1, 20)
        robot.moveBy(driver.NE2, -10)

        sleep(0.4)

        robot.moveBy(driver.SW1, -20)
        robot.moveBy(driver.SW2, 20)

        robot.moveBy(driver.NW1, 30)
        robot.moveBy(driver.NW2, -20)

        robot.moveBy(driver.SE1, -10)
        robot.moveBy(driver.SE2, 10)

        sleep(0.4)

        robot.reset()


if __name__ == '__main__':
    driver.run_script(simple_walking)