#!/usr/local/bin/python
# -*- coding: utf-8 -*-

from __future__ import print_function

import RPi.GPIO as GPIO
import time
import datetime

# 4 GPIO nest nederste rekke. 
PORTS = [19,26,16,20]
PORTS_OUT = 21

GPIO.setmode(GPIO.BCM)
for i in range(len(PORTS)):
    GPIO.setup(PORTS[i], GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(PORTS_OUT, GPIO.OUT)

PORT_STATES = [0,0,0,0]
GPIO.output(PORTS_OUT, 1)

def read_ports():
    for i in range(len(PORT_STATES)):
        #PORT_STATES[i] = GPIO.input(PORTS[i])
        if GPIO.input(PORTS[i]) == 1: # Only one port can be active at a time!
            return i+1
    return 0

    #print("Port 0   Port 2")
    #print(PORT_STATES[0], "    ", PORT_STATES[2])
    #print(PORT_STATES[1], "    ", PORT_STATES[3])
    #print("Port 1   Port 3")
    #print()

def write_port(port):
    print(f"Read port {port}")
    with open(r'test_file.txt', 'r+') as fil:
        content = []
        for row in fil:
            content.append(row[0])
        print(content)
        if str(port) in content:
            print("Port is in file")
        else:
            fil.write(str(port) + ',' + datetime.now().strftime("%H,%M,%S") + '\n')
            print("Wrote port to file")

while True:
    port = read_ports()
    if port != 0:
        write_port(port)
    time.sleep(0.5)

GPIO.cleanup()
