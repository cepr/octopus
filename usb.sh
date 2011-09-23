#!/bin/bash
socat -x open:/dev/ttyUSB0,nonblock=1,b9600,ignbrk=1,brkint=0,icrnl=0,imaxbel=0,opost=0,onlcr=0,isig=0,icanon=0,iexten=0,echo=0,echoe=0,echok=0,echoctl=0,echoke=0 EXEC:out/OctopusControlPanel/Debug/OctopusControlPanel

