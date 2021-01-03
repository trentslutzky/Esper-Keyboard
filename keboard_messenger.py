#!/bin/python3.9

import os, serial, time

#baudRate = 115200
#serialPortName = '/dev/ttyACM1'
#serialPort = serial.Serial(port= serialPortName, baudrate = baudRate, timeout=0, rtscts=True)

steam = os.popen('arduino-cli board list | grep USB')
output = stream.read()[:26]
print(output)

# while True:
#    time.sleep(0.05)
#    stream = os.popen("amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $2 }'")
#    output = stream.read()
#    volume = int(output.replace('%','').replace('\n',''))
#
#    output_string = '<'+str(volume)+'>'
#    print(output_string)
#
#    serialPort.write(output_string.encode('utf-8'))
