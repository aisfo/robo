import script
import body

def read_orientation():
    while(True):
        orientation = body.readOrientation()
        print(orientation)

if __name__ == '__main__':
    script.run(read_orientation)

