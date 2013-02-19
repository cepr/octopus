#!/bin/sh
stty -F /dev/ttyUSB0 raw 57600 pass8 -cstopb
trend -f s /dev/ttyUSB0 1000x1
