/*
 * Copyright 2010-2011 Cedric Priscal
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

#ifndef AVR

#include "linux_serial_port.h"

#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

LinuxSerialPort::LinuxSerialPort(const wxString & devicepath) :
		mDevicePath(devicepath)
{
	mRxThread = new PipeReceptionThread(*this);
	mTxThread = new PipeTransmissionThread(*this);
}

bool LinuxSerialPort::openDevice(wxFile & file, wxFile::OpenMode mode)
{
	// Configure serial port in NON-BLOCKING MODE for configuration
	int fd = open(mDevicePath.ToAscii(), O_RDWR | O_NDELAY);
	if (fd >= 0) {
		struct termios termios_p;
		if (tcgetattr(fd, &termios_p)) {
			perror("tcgetattr failed");
			close(fd);
			return false;
		}
		cfmakeraw(&termios_p);
		termios_p.c_iflag |= IXON | IXOFF;
		termios_p.c_cflag |= CLOCAL;
		if (cfsetspeed(&termios_p, B57600) || tcsetattr(fd, TCSANOW, &termios_p)) {
			perror("cfsetspeed or tcsetattr failed");
			close(fd);
			return false;
		}

		// Close (the reading and writing threads will reopen their own descriptor in blocking mode)
		close(fd);
	} else {
		perror("Warning: port configuration failed\n");
		return false;
	}

	// Open file
	return file.Open(mDevicePath, mode);
}

void LinuxSerialPort::sendByte(unsigned char c)
{
	mTxThread->sendByte(c);
}

bool LinuxSerialPort::isUsartBufferEmpty()
{
	return mTxThread->isUsartBufferEmpty();
}

LinuxSerialPort::~LinuxSerialPort()
{
	mRxThread->Terminate();
	mTxThread->Terminate();
}

#endif /* AVR */
