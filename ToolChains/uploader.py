import serial
import subprocess
import sys
import os
import time
import _thread
log = print


class Uploader(object):
    def __init__(self, ser, file):
        self.ser = ser
        self.file = file

    def load(self):
        s = serial.Serial(self.ser, baudrate=9600, timeout=1)
        # Set M2 baudrate to 19200
        s.write(b'1')
        time.sleep(0.1)
        s.write(b'1f800702\n')
        time.sleep(0.1)
        s.write(b'1000\n')
        time.sleep(0.2)

        # Set computer baudrate to 19200
        s.baudrate = 19200
        time.sleep(0.1)

        # Erase flash
        s.write(b'1')
        time.sleep(0.1)
        s.write(b'10300000\n')
        time.sleep(0.1)
        s.write(b'1\n')
        time.sleep(0.2)

        # Bootloader
        s.write(b'5')
        time.sleep(0.1)
        s.write(b'10000000\n')
        time.sleep(0.2)
        with open(self.file, 'rb') as f:
            bin = f.read()
            s.write(bin)
            time.sleep(1)

        # Set baudrate to 9600
        s.write(b'1')
        time.sleep(0.1)
        s.write(b'1f800702\n')
        time.sleep(0.1)
        s.write(b'0\n')
        time.sleep(0.3)

        s.baudrate = 9600
        time.sleep(0.3)

        print('Upload completed.')


def main():
    if len(sys.argv) > 1:
        uploader = Uploader(ser=sys.argv[1],file=sys.argv[2])
        uploader.load()
    else:
        print("Usage: uploader [port] [bin_file_path]\n")

if __name__ == "__main__":
    main()
