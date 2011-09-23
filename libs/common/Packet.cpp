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

#include "Packet.h"

Packet::Packet(Usart *usart) {
	mSize = 0;
	mStarted = false;
	mEscape = false;
	mUsart = usart;
	mListener = 0;
	usart->registerListener(this);
}

void Packet::registerListener(PacketListener* listener) {
	mListener = listener;
}

void Packet::onUsartReceived(unsigned char byte) {

	if (byte == ESCAPE) {
		mEscape = true;
	} else if (byte == START) {
		mStarted = true;
        mEscape = false;
		mSize = 0;
	} else if (byte == STOP) {
		// Packet complete, send it to listener.
		if (mStarted && mListener) {
			mListener->onPacketReceived(mBuffer, mSize);
		}
		mStarted = false;
        mEscape = false;
	} else {
		// This is not a special byte
		if (mEscape) {
            byte ^= ESCAPE;
            mEscape = false;
        }
		if (mStarted) {
			mBuffer[mSize++] = byte;
			if (mSize > sizeof(mBuffer)) {
				// Packet too big !
				mStarted = false;
			}
		}
	}
}

void Packet::sendPacket(const unsigned char *buffer, char size) {
	mUsart->sendByte(START);
	while(size > 0) {
		unsigned char byte = *buffer++;
		if ((byte == START) || (byte == ESCAPE) || (byte == STOP)) {
			mUsart->sendByte(ESCAPE);
            mUsart->sendByte(byte ^ ESCAPE);
		} else {
        	mUsart->sendByte(byte);
        }
		size--;
	}
	mUsart->sendByte(STOP);
}
