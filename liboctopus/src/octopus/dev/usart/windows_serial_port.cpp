/*
 * Copyright 2012 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __WIN32

#include "octopus/dev/usart/windows_serial_port.h"

WindowsSerialPort::WindowsSerialPort(const wxString& devicepath) {
	// TODO Implement WindowsSerialPort
}

WindowsSerialPort::~WindowsSerialPort() {
	// TODO Implement WindowsSerialPort
}

void WindowsSerialPort::sendByte(unsigned char c) {
	// TODO Implement WindowsSerialPort
}

bool WindowsSerialPort::isUsartBufferEmpty() {
	// TODO Implement WindowsSerialPort
	return true;
}

#endif /* __WIN32 */
