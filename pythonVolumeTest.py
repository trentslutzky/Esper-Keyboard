#!/bin/python3.9

import os, serial
stream = os.popen("amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $2 }'")
output = stream.read()
volume = int(output.replace('%','').replace('\n',''))

output_string = '<Volume:'+str(volume)+'>'
print(output_string)

baudRate = 115200
serialPortName = '/dev/ttyACM0'

serialPort = serial.Serial(port= serialPortName, baudrate = baudRate, timeout=0, rtscts=True)

serialPort.write(output_string.encode('utf-8'))
