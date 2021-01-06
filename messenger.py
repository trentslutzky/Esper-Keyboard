#!/bin/python3.9

import os, serial, time, platform
from datetime import datetime
from ahk import AHK

ahk = AHK()

print('Launching Esper Messenger!')
time.sleep(1)
print('Detected system type:',end=' ')
sys_type = platform.system()
print(sys_type)

# get the serial port of the teensy usb 
# linux
if(sys_type == 'Linux'):
    stream = os.popen('arduino-cli board list | grep USB')
    output = stream.read()[:12]
    serialPortName = output

elif(sys_type == 'Windows'):
   serialPortName = 'COM4' 

print('Teensy found at port:',serialPortName)

# setup the serial connection
baudRate = 115200
serialPort = serial.Serial(port= serialPortName, baudrate = baudRate, timeout=0, rtscts=True)

time_string = ''
current_time = ''
last_time = ''

current_volume = 0
last_volume = 0

# loop forever
while True:
    now = datetime.now()
    current_time = now.strftime("%H:%M")

    if(current_time != last_time):
            time_string = '<T'+current_time+'>'
            print(time_string)
            serialPort.write(time_string.encode('utf-8'))
            last_time = current_time

    time.sleep(0.1)
    #linux volume getter
    if(sys_type == 'Linux'):
        stream = os.popen("amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $2 }'")
        output = stream.read()
        volume = int(output.replace('%','').replace('\n',''))
    elif(sys_type):
        volume = int(round(float(ahk.sound_get(device_number=1
                        , component_type='MASTER'
                        , control_type='VOLUME')),0))

    current_volume = volume
    if(current_volume != last_volume):
        volume_string = '<V'+str(volume)+'>'
        print(volume_string)
        serialPort.write(volume_string.encode('utf-8'))
        last_volume = current_volume

