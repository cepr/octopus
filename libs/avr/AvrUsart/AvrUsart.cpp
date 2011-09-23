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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "AvrUsart.h"
#include "UsartBuffer.h"
#include "Handler.h"
#include "fatal.h"
#include "Looper.h"

static UsartBuffer mRxBuffer;
static UsartBuffer mTxBuffer;
static Handler* mHandler;

//#define CROSS_TEST

/* USART Rx Complete */
ISR(USART_RX_vect) {
    while(UCSR0A & _BV(RXC0)) {
#ifdef CROSS_TEST
		unsigned char tmp = UDR0;
		UDR0 = tmp;
#else
        if (!mRxBuffer.PutChar(UDR0)) {
            fatal(FATAL_USART_RX_OVERFLOW);
        }
#endif
    }
    PostEvent(mHandler, 0);
}

static void trysend() {
    /* Try to send data now if possible */
    while((UCSR0A & _BV(UDRE0)) && (mTxBuffer.mCount > 0)) {
        UDR0 = mTxBuffer.GetChar();
    }
    /* If not everything has been send, activate the interrupt */
    if (mTxBuffer.mCount > 0) {
        UCSR0B |= _BV(UDRIE0); // USART Data Register Empty Interrupt Enable
    } else {
        UCSR0B &=~_BV(UDRIE0); // USART Data Register Empty Interrupt Enable
    }
}

/* USART, Data Register Empty */
ISR(USART_UDRE_vect) {
    trysend();
}

AvrUsart::AvrUsart(UsartBaudrate baudrate) : Usart() {
    mHandler = this;

	switch(baudrate) {
#if (F_CPU == 8000000L)
		case B115200:
			UCSR0A = _BV(U2X0);
			UBRR0 = 8;
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
    UCSR0B = _BV(RXCIE0) | // RX Complete Interrupt Enable
             _BV(RXEN0)  | // Receiver Enable
             _BV(TXEN0);   // Transmitter Enable
    UCSR0C = _BV(UCSZ01) |
             _BV(UCSZ00);
}

void AvrUsart::sendByte(unsigned char c) {
    cli();
    if (!mTxBuffer.PutChar(c)) {
        fatal(FATAL_USART_TX_OVERFLOW);
    }
    trysend();
    sei();
}

void AvrUsart::onEvent(char what) {
    while(mRxBuffer.mCount > 0) {
        cli();
        unsigned char c = mRxBuffer.GetChar();
        sei();
        if (mListener) {
            mListener->onUsartReceived(c);
        }
    }
}
