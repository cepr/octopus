/*
 * Copyright 2010 Cedric Priscal
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

#include "LinuxSerialPort.h"

#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

LinuxSerialPort::LinuxSerialPort(const char* device) : Usart() {
	if (device) {
		// Use a serial port for communication
		mFdInput = -1;
		mFdOutput = -1;
	} else {
		// Use STDIN/STDOUT for communication
		mFdInput = 0;
		mFdOutput = 1;
		start();
	}
    mDevice = device;
}

void LinuxSerialPort::tryopen() {

    // Open and configure serial port in NON-BLOCKING MODE for configuration
	mFdInput = mFdOutput = open(mDevice, O_RDWR | O_NDELAY);

	if (mFdOutput >= 0) {

		struct termios termios_p;
		if (tcgetattr(mFdOutput, &termios_p)) {
			perror("tcgetattr failed");
			close(mFdOutput);
			mFdOutput = -1;
			return;
		}
		cfmakeraw(&termios_p);
        termios_p.c_cflag |= CLOCAL;
		if (cfsetspeed(&termios_p, B9600) || tcsetattr(mFdOutput, TCSANOW, &termios_p)) {
			perror("cfsetspeed or tcsetattr failed");
			close(mFdOutput);
			mFdOutput = -1;
			return;
		}

        // Reopen port with BLOCKING MODE activated
        close(mFdOutput);
	} else {
		perror("Warning: port configuration failed\n");
	}

	mFdInput = mFdOutput = open(mDevice, O_RDWR);
	if (mFdInput >= 0) {
		// Start port reading thread
		start();
	} else {
		perror("Cannot open port!");
		exit(1);
	}
}

void LinuxSerialPort::sendByte(unsigned char c) {
	if (mFdOutput < 0) {
		tryopen();
	}
	if (mFdOutput >= 0) {
		if (write(mFdOutput, &c, sizeof(unsigned char)) == sizeof(unsigned char)) {
//			fprintf(stderr, "\033[0;34m%02x \033[0m", (int)c);
		} else {
//			fprintf(stderr, "\033[0;31mWRITE_ERROR \033[0m");
			close(mFdOutput);
			mFdOutput = -1;
		}
	}
}

void LinuxSerialPort::run() {
	for(;;) {
		unsigned char incoming;
		int size = read(mFdInput, &incoming, sizeof(incoming));
		if (size == sizeof(incoming)) {
//			fprintf(stderr, "\033[0;32m%02x \033[0m", (int)incoming);
			if (mListener) {
				mListener->onUsartReceived(incoming);
			}
		} else {
//			fprintf(stderr, "\033[0;31mREAD_ERROR \033[0m");
			close(mFdInput);
			mFdInput = -1;
			return;
		}
	}
}
