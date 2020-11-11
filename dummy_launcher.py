# dummy_launcher.py
# launches a series of dummy devices

# imports
from sys import argv
import subprocess

# GLOBALS
# max number of devices we support in server.cpp
NUMBER_OF_DEVICES = 50

def main():

    # check that sys.argv is of the correct length
    if len(argv) == 3:
        arg_good = True
    # if not, print/return error
    else:
        print("Wrong number of arguments.")
        return 1

    if arg_good:

        # launch a series of subprocess dummy devices
        # placeholder for now...
        # subprocess.run(dummy_device)
        pass
    
    return 0

# we only want to run if we're main, so:
if __name__ == "__main__":
    main()
