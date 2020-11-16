# dummy_launcher.py
# launches a series of dummy devices

# imports
from sys import argv
import subprocess

# GLOBALS
# number of devices we want to launch
# server.cpp currently supports 50, but this is more readable in output
NUMBER_OF_DEVICES = 10

def main():

    # get opt number from argv
    if (len(argv) == 2):
        opt = argv[1]
    # if bad, exit with error code 1
    else:
        print('Usage: dummy_launcher.py opt_num')
        exit(1)

    conf = {
        1 : [
            ['./dummy-device/exe/dummy', '01', '1.2', '0', 'false'],
            ['./dummy-device/exe/dummy', '02', '1.2', '0.5', 'false'],
            ['./dummy-device/exe/dummy', '03', '1.2', '1', 'false'],
            ['./dummy-device/exe/dummy', '04', '1.2', '1.5', 'false'],
            ['./dummy-device/exe/dummy', '05', '1.2', '2', 'false'],
            ['./dummy-device/exe/dummy', '06', '1.2', '2.5', 'false'],
            ['./dummy-device/exe/dummy', '07', '1.2', '3', 'false'],
            ['./dummy-device/exe/dummy', '08', '1.2', '3.5', 'false'],
            ['./dummy-device/exe/dummy', '09', '1.2', '4', 'false'],
            ['./dummy-device/exe/dummy', '10', '1.2', '4.5', 'false']
        ], # none out of bounds
        2 : [
            ['./dummy-device/exe/dummy', '01', '1.2', '0', 'false'],
            ['./dummy-device/exe/dummy', '02', '1.2', '0.5', 'true'],
            ['./dummy-device/exe/dummy', '03', '1.2', '1', 'false'],
            ['./dummy-device/exe/dummy', '04', '1.2', '1.5', 'true'],
            ['./dummy-device/exe/dummy', '05', '1.2', '2', 'false'],
            ['./dummy-device/exe/dummy', '06', '1.2', '2.5', 'true'],
            ['./dummy-device/exe/dummy', '07', '1.2', '3', 'false'],
            ['./dummy-device/exe/dummy', '08', '1.2', '3.5', 'false'],
            ['./dummy-device/exe/dummy', '09', '1.2', '4', 'false'],
            ['./dummy-device/exe/dummy', '10', '1.2', '4.5', 'false']
        ], # a few set to go out sometimes
        3 : [
            ['./dummy-device/exe/dummy', '01', '1.2', '0', 'false'],
            ['./dummy-device/exe/dummy', '02', '1.75', '0.5', 'true'],
            ['./dummy-device/exe/dummy', '03', '1.2', '1', 'false'],
            ['./dummy-device/exe/dummy', '04', '3.0', '1.5', 'true'],
            ['./dummy-device/exe/dummy', '05', '1.2', '2', 'false'],
            ['./dummy-device/exe/dummy', '06', '2.5', '2.5', 'true'],
            ['./dummy-device/exe/dummy', '07', '1.2', '3', 'false'],
            ['./dummy-device/exe/dummy', '08', '1.2', '3.5', 'false'],
            ['./dummy-device/exe/dummy', '09', '1.2', '4', 'false'],
            ['./dummy-device/exe/dummy', '10', '1.2', '4.5', 'false']
        ] # way out consistently
    }

    print('Using option ' + opt)

    # launch all processes for given conf option
    procs = [subprocess.Popen(com) for com in conf[int(opt)]]
    # wait for all launched processes to terminate
    print('Waiting for all 10 dummy devices to terminate...')
    for proc in procs:
        ret = proc.poll()
        if ret == 0:
            break

    print('All devices terminated. Exiting...')
    # end execution, no error
    exit(0)

# we only want to run if we're main, so:
if __name__ == '__main__':
    main()

# default ampl should be 1.2 - account for fp errors
# shif should be a random small value to move things around
# serial should be a serial number
# oob_gen should be a low chance random (or just set to be a few?)