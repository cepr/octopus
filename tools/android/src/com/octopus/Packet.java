/*
 * Copyright 2011 Cedric Priscal
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

package com.octopus;

/**
 * @brief Class that listens to incoming bytes from an Usart, and formats complete packets.
 */
public class Packet implements IUsartListener {

	private static final byte ESCAPE = (byte) 0x80;
	private static final byte START = 's';
	private static final byte STOP = '\n';

	private Usart mUsart;
	byte[] mBuffer;
	int mSize;
	boolean mStarted;
	boolean mEscape;
	IPacketListener mListener;

	void onUsartReceived(byte b) {
		if (b == ESCAPE) {
			mEscape = true;
		} else if (b == START) {
			mStarted = true;
	        mEscape = false;
		} else if (b == STOP) {
			// Packet complete, send it to listener.
			if (mStarted && (mListener != null)) {
				byte[] packet = new byte[mSize];
				System.arraycopy(mBuffer, 0, packet, 0, mSize);
				mListener.onPacketReceived(mBuffer);
			}
			mStarted = false;
	        mEscape = false;
		} else {
			// This is not a special byte
			if (mEscape) {
	            b ^= ESCAPE;
	            mEscape = false;
	        }
			if (mStarted) {
				mBuffer[mSize++] = b;
				if (mSize > mBuffer.length) {
					// Packet too big !
					mStarted = false;
				}
			}
		}
	}

	/**
	 * @brief Constructor
	 *
	 * @param usart Usart to connect to
	 */
	Packet(Usart usart) {
		mBuffer = new byte[512];
		mSize = 0;
		mStarted = false;
		mEscape = false;
		mUsart = usart;
		mListener = null;
		usart.registerListener(this);
	}

	/**
	 * @brief Registers a listener which will be called any time a new complete packet is received
	 * @param[in] listener Listener
	 */
	void registerListener(IPacketListener listener) {
		mListener = listener;
	}

	/**
	 * @brief Sends a packet
	 *
	 * @param buffer Data to send
	 * @param size   Size of \a buffer
	 */
	void sendPacket(final byte buffer[], char size) {
		mUsart.sendByte(START);
		for(int i=0; i<size; i++) {
			byte b = buffer[i++];
			if ((b == START) || (b == ESCAPE) || (b == STOP)) {
				mUsart.sendByte(ESCAPE);
	            mUsart.sendByte((byte) (b ^ ESCAPE));
			} else {
	        	mUsart.sendByte(b);
	        }
			size--;
		}
		mUsart.sendByte(STOP);
	}
}
