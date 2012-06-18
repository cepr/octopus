
# Octopus SDK

## Presentation

Octopus SDK is an open-source C++ development framework for
micro-controllers. It is compatible with AVR micro-controllers,
including the famous Arduino boards.

## Why not Arduino software ?

Arduino is a good framework and is quite simple to learn, but has a
limitation: you can use only one execution flow, which can be
problematic if you want to handle a lot of incoming events (GPIOs
modifications, timers, incoming byte on the serial port, etc).

Octopus framework uses an event-queue to handle incoming events. As
a consequence the CPU stays in idle mode as long as no event arises.
If you want to simply blink a led, you just have to code an timer
event handler which will toggle the GPIO output, and start a timer
for 1 second with this event handler. 

Another advantage of Octopus SDK is its remote control and telemetry
framework. Simply change the type of your C++ variables to the
`RemoteProperty` type, and you will be able to monitor and modify
in real-time the variable with the GUI application *OctopusControlPanel*.
This application is available for Windows, Linux and MacOS X, and an
Android version is coming.

## Supported boards

For the moment, Octopus SDK is compatible with AVR ATmega328P, which
is used in the following board:
* Arduino Uno
* Arduino Ethernet
* Arduino Pro boards
* Arduino BT
* LilyPad Arduino
* Arduino Fio
* Arduino Pro
* Arduino Nano
* Arduino Mini
* Arduino Pro Mini

## License

Copyright (C) 2010-2012 PRISCAL Cedric

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

