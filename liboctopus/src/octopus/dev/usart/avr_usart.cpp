/*
 * Copyright 2010-2012 Cedric Priscal
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

#ifdef __AVR

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr_usart.h"
#include "usart_buffer.h"
#include "octopus/util/fatal.h"

namespace
{
	// Warning: mRxBuffer and mTxBuffer must be accessed with masked interrupts to avoid concurrent access.
	UsartBuffer mRxBuffer;
	UsartBuffer mTxBuffer;
	Event* mEvent = 0;

	// Uplink
	bool isRemoteSuspended = false;		// true if XOFF has been received
	bool isEscapedBytePending = false;	// true if ESC has been sent, and a XOR must be done on next byte
	bool isXOFFPending = false;			// true if XOFF must be send as soon as possible
	bool isXONPending = true;			// true if XON must be send as soon as possible
	bool isNAKPending = false;			// true if NAK must be send as soon as possible
	unsigned char mEscapedByte = 0;		// byte to send if isEscapedBytePending is set

	// Downlink
	bool isLocalSuspended = false; 		// true if we have nothing to send
	bool isEscapeReceived = false;		// true if ESC has been received

	inline void resetBuffersUnsafe(void)
	{
		mRxBuffer.reset();
		mTxBuffer.reset();
		isRemoteSuspended = false;
		isEscapedBytePending = false;
		isXOFFPending = false;
		isXONPending = true;
		isNAKPending = false;
		isLocalSuspended = false;
		isEscapeReceived = false;
		mEscapedByte = 0;
	}

	inline void resumeTransmission(void)
	{
		UCSR0B |= _BV(UDRIE0); // USART Data Register Empty Interrupt Enable
	}

	inline void suspendTransmission(void)
	{
		UCSR0B &= ~_BV(UDRIE0); // USART Data Register Empty Interrupt Enable
	}

	inline void sendByteUnsafe(unsigned char c)
	{
		if (!mTxBuffer.PutChar(c)) {
			resetBuffersUnsafe();
			isNAKPending = true;
			resumeTransmission();
		}
		if (!isRemoteSuspended) {
			resumeTransmission();
		}
	}
}

/* USART Rx Complete */
ISR(USART_RX_vect)
{

	while(UCSR0A & _BV(RXC0)) {
		// At first we check for data overrun
		if (UCSR0A & _BV(DOR0)) {
			fatal(FATAL_USART_RX_OVERRUN);
		}

		// Get the received byte
		unsigned char b = UDR0;

		if (isEscapeReceived) {
			// b is a modified data byte
			b ^= Usart::ESC_XOR_MASK;
			isEscapeReceived = false;
		} else if ((b < Usart::DATA_MIN_VALUE) || (b == Usart::AVRDUDE)) {
			// special command byte
			switch(b) {
			case Usart::XON:
				isRemoteSuspended = false;
				resumeTransmission();
				break;
			case Usart::XOFF:
				isRemoteSuspended = true;
				break;
			case Usart::ESC:
				isEscapeReceived = true;
				break;
			case Usart::NAK:
				resetBuffersUnsafe();
				break;
			case Usart::AVRDUDE:
				enter_boot_loader();
				break;
			}
			continue;
		}

		// Data byte
		if (mRxBuffer.PutChar(b)) {
			// Success, check if an XOFF is needed
			if ((!isLocalSuspended) && (mRxBuffer.mCount >= UsartBuffer::USARTBUFFER_HIGH_THRESHOLD)) {
				isLocalSuspended = true;
				isXOFFPending = true;
				resumeTransmission();
			}
		} else {
			// Buffer overflow: reset buffers and send a NAK
			resetBuffersUnsafe();
			isNAKPending = true;
			resumeTransmission();
		}
	}

	mEvent->Post(0);
}

/* USART, Data Register Empty */
ISR(USART_UDRE_vect)
{
	/* Try to send data now if possible */
	while(UCSR0A & _BV(UDRE0)) {
		if (isEscapedBytePending) {
			// The escape byte has been send, we MUST send the escaped data now
			UDR0 = mEscapedByte ^ Usart::ESC_XOR_MASK;
			isEscapedBytePending = false;
		} else if (isNAKPending) {
			UDR0 = Usart::NAK;
			isNAKPending = false;
		} else if (isXOFFPending) {
			UDR0 = Usart::XOFF;
			isXOFFPending = false;
		} else if (isXONPending) {
			UDR0 = Usart::XON;
			isXONPending = false;
		} else if ((mTxBuffer.mCount > 0) && (!isRemoteSuspended)) {
			unsigned char c = mTxBuffer.GetChar();
			if ((c < Usart::DATA_MIN_VALUE) || (c == Usart::AVRDUDE)) {
				// The byte cannot be send as-is, it must be escaped
				mEscapedByte = c;
				isEscapedBytePending = true;
				UDR0 = Usart::ESC;
			} else {
				// The byte can be send as-is
				UDR0 = c;
			}
		} else {
			/* If everything has been send or if remote is overloaded (XOFF received), deactivate the interrupt */
			suspendTransmission();
			if (mTxBuffer.mCount == 0) {
				mEvent->Post(1);
			}
			break;
		}
	}
}

AvrUsart::AvrUsart(UsartBaudrate baudrate) : Usart()
{
	mEvent = this;

	switch(baudrate) {
#if (F_CPU == 8000000L)
	case B115200:
		UCSR0A = _BV(U2X0);
		UBRR0 = 8;
		break;
	case B57600:
		UCSR0A = _BV(U2X0);
		UBRR0 = 16;
		break;
	case B38400:
		UCSR0A = 0;
		UBRR0 = 12;
		break;
	case B9600:
		UCSR0A = 0;
		UBRR0 = 51;
		break;
	case B2400:
		UCSR0A = 0;
		UBRR0 = 207;
		break;
#else
# error Unknown CPU frequency
#endif
	}

	/* Set options, stop bits, etc */
	UCSR0C = _BV(UCSZ01) | // 8 bits, 1 stop bit, no parity
	         _BV(UCSZ00);
	UCSR0B = _BV(RXCIE0) | // RX Complete Interrupt Enable
	         _BV(UDRIE0) | // USART Data Register Empty Interrupt Enable
	         _BV(RXEN0)  | // Receiver Enable
	         _BV(TXEN0);   // Transmitter Enable
}

void AvrUsart::sendByte(unsigned char c)
{
	cli();
	sendByteUnsafe(c);
	sei();
}

void AvrUsart::onEvent(char what)
{
	if (what == 0) {
		// Reception event
		while(mRxBuffer.mCount > 0) {
			cli();
			unsigned char c = mRxBuffer.GetChar();
			if (isLocalSuspended && (mRxBuffer.mCount <= UsartBuffer::USARTBUFFER_LOW_THRESHOLD)) {
				// We can receive more bytes now
				isLocalSuspended = false;
				isXONPending = true;
				resumeTransmission();
			}
			sei();
			if (mListener) {
				mListener->onUsartReceived(c);
			}
		}
	} else {
		// Transmission event
		if (mListener) {
			mListener->onUsartBufferEmpty();
		}
	}
}

bool AvrUsart::isUsartBufferEmpty()
{
	return (mTxBuffer.mCount == 0);
}

#endif /* __AVR */
