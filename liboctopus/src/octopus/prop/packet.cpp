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

#include "packet.h"
#if !defined(AVR)
#include <wx/log.h>
#endif

#include "octopus/event/looper.h"
using octopus::event::Looper;

Packet::Packet(Usart *usart)
{
	mSize = 0;
	mStarted = false;
	mEscape = false;
	mUsart = usart;
	mListener = 0;
	usart->registerListener(this);
}

void Packet::registerListener(PacketListener* listener)
{
	mListener = listener;
}

void Packet::onUsartReceived(unsigned char byte)
{

	if (byte == ESCAPE) {
		mEscape = true;
	} else if (byte == START) {
		mStarted = true;
		mEscape = false;
		mSize = 0;
	} else if (byte == STOP) {
		// Packet complete, send it to listener.
		if (mStarted) {
#if !defined(AVR) && defined(DEBUG)
			{
				wxString msg = "\033[0;32m[I]";
				for (int i=0; i<mSize; i++) {
					msg.Append(wxString::Format(" %02x", mBuffer[i]));
				}
				msg.Append("\033[0m");
				wxLogDebug(msg);
			}
#endif
			if (mListener) {
				mListener->onPacketReceived(mBuffer, mSize);
			}
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

void Packet::onUsartBufferEmpty()
{
	if (mListener) {

		// Packet buffer is a local array
		unsigned char buffer[32];
		unsigned char size = 0;

		// Retrieve packet content from listener
		if (mListener->onReadyToSend(buffer, size, sizeof(buffer))) {

#if !defined(AVR) && defined(DEBUG)
			{
				wxString msg = "\033[0;34m[O]";
				for (int i=0; i<size; i++) {
					msg.Append(wxString::Format(" %02x", buffer[i]));
				}
				msg.Append("\033[0m");
				wxLogDebug(msg);
			}
#endif

			// Send packet
			mUsart->sendByte(START);
			unsigned char* ptr = buffer;
			while(size > 0) {
				unsigned char byte = *ptr++;
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
	}
}

void Packet::requestToSend()
{
	if ((mUsart) && (mUsart->isUsartBufferEmpty())) {
		Looper::get()->insert(this);
	}
}

void Packet::onEvent()
{
	onUsartBufferEmpty();
}
