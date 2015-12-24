import signal
import sys

import body


def run(script_to_run):

    def exit(signal, frame):
        body.close()
        sys.exit(0)

    signal.signal(signal.SIGINT, exit)

    try:
        body.connect()
        script_to_run()
    except Exception as e:
        print(e)

    exit(None, None)



