import driver


def read_orientation(robot):
    while(True):
        orientation = robot.readOrientation()
        print(orientation)


if __name__ == '__main__':
    driver.run_script(read_orientation)

