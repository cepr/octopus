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

#include "Usart.h"

Usart::Usart() {
    mListener = 0;
}

void Usart::registerListener(UsartListener *listener) {
	mListener = listener;
}

void Usart::sendBuffer(const unsigned char *buffer, char size) {
	while(size > 0) {
		sendByte(*buffer++);
		size--;
	}
}

void Usart::sendHexByte(unsigned char c) {
    unsigned char digit = (c >> 4) & 15;
    if (digit < 10) {
        sendByte((unsigned char)('0' + digit));
    } else {
        sendByte((unsigned char)(('a'-10) + digit));
    }
    digit = c & 15;
    if (digit < 10) {
        sendByte((unsigned char)('0' + digit));
    } else {
        sendByte((unsigned char)(('a'-10) + digit));
    }
}

void Usart::sendHexShort(unsigned short s) {
    sendHexByte(s >> 8);
    sendHexByte(s & 0xff);
}

void Usart::sendString(const char *txt) {
    while(*txt != 0) {
        sendByte((unsigned char)*txt++);
    }
}

