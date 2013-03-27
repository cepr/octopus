/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __AVR__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "octopus/avr_usart.h"
#include "octopus/fatal.h"
#include "octopus/gpio.h"
#include "octopus/power_management.h"

namespace octopus {

// The AvrUsart instance
AvrUsart AvrUsart::instance;

// ///////////////////////////////////////////////////////
//   Construction and configuration
// ///////////////////////////////////////////////////////

AvrUsart::AvrUsart() :
        write_ptr(0),
        write_size(0)
{
    setBaudrate(B57600);
    UCSR0C = _BV(UCSZ01) | // 8 bits, 1 stop bit, no parity
             _BV(UCSZ00);
    UCSR0B = 0; // USART is deactivated by default

    // Set RX pin in input with pull-up
    Gpio::D0.setDirection(Gpio::INPUT);
    Gpio::D0.activatePullUp();

    // Set TX pin in output high
    Gpio::D0.setDirection(Gpio::OUTPUT);
    Gpio::D0.set();
}

void AvrUsart::setBaudrate(Baudrate baudrate)
{
    switch(baudrate) {
    case B115200:
#       define BAUD 115200
#       include <util/setbaud.h>
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
#       if USE_2X
            UCSR0A |= (1 << U2X0);
#       else
            UCSR0A &= ~(1 << U2X0);
#       endif
#       undef BAUD
        break;

    case B57600:
#       define BAUD 57600
#       include <util/setbaud.h>
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
#       if USE_2X
            UCSR0A |= (1 << U2X0);
#       else
            UCSR0A &= ~(1 << U2X0);
#       endif
#       undef BAUD
        break;

    case B38400:
#       define BAUD 38400
#       include <util/setbaud.h>
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
#       if USE_2X
            UCSR0A |= (1 << U2X0);
#       else
            UCSR0A &= ~(1 << U2X0);
#       endif
#       undef BAUD
        break;

    case B9600:
#       define BAUD 9600
#       include <util/setbaud.h>
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
#       if USE_2X
            UCSR0A |= (1 << U2X0);
#       else
            UCSR0A &= ~(1 << U2X0);
#       endif
#       undef BAUD
        break;

    case B2400:
#       define BAUD 2400
#       include <util/setbaud.h>
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
#       if USE_2X
            UCSR0A |= (1 << U2X0);
#       else
            UCSR0A &= ~(1 << U2X0);
#       endif
#       undef BAUD
        break;
    }
}

// ///////////////////////////////////////////////////////
//   Reception
// ///////////////////////////////////////////////////////

void AvrUsart::resumeRX()
{
    Buffer* buf;

    // Skip all full buffer
    while( ( (buf = read_list.front()) != 0) &&
          (buf->size >= buf->capacity) ) {
        // Trying to read in an empty buffer, skip to the next one
        read_list.remove(buf);
        if (buf->callback) {
            buf->callback->onReadFinished(buf);
        }
    }

    if (!buf) {
        // No more read buffers, abort
        return;
    }

    // Keep clkIO ON.
    PowerManagement::instance.clk_IO.acquire(PowerManagement::LOCK_USART_RX);

    UCSR0B |= _BV(RXCIE0) | // RX Complete Interrupt Enable
              _BV(RXEN0);   // Receiver Enable
}

void AvrUsart::suspendRX()
{
    UCSR0B &= ~_BV(RXCIE0); // RX Complete Interrupt Enable
}

/* USART Rx Complete */
ISR(USART_RX_vect)
{
    AvrUsart::instance.rxInterrupt();
}

void AvrUsart::rxInterrupt()
{
    while(UCSR0A & _BV(RXC0)) {
        // At first we check for data overrun
        if (UCSR0A & _BV(DOR0)) {
            fatal(FATAL_USART_RX_OVERRUN);
        }

        // Read the received byte
        unsigned char rx = UDR0;

        // Append the received byte to the current buffer
        Buffer* buf = read_list.front();
        buf->ptr[buf->size++] = (char)rx;

        // Check if the current buffer is full or if the termination
        // character has been read.
        if ( (buf->size == buf->capacity) ||
             ((int)rx == buf->term_char) ) {

            do {
                read_list.remove(buf);

                // Call its callback
                if (buf->callback) {
                    buf->callback->onReadFinished(buf);
                }

                // Get the next buffer
                buf = read_list.front();
                if (!buf) {
                    suspendRX();
                    return;
                }
            } while (buf->size >= buf->capacity);
        }
    }
}


// ///////////////////////////////////////////////////////
//   Transmission
// ///////////////////////////////////////////////////////

void AvrUsart::resumeTX()
{
    while (!write_size) {
        Buffer* buf = write_list.front();
        if (buf) {
            write_size = buf->size;
            write_ptr =  buf->ptr;
            if (!write_size) {
                // Empty write buffer, skip to the next one
                write_list.remove(buf);
                if (buf->callback) {
                    buf->callback->onWriteFinished(buf);
                }
            }
        } else {
            // No more write buffers, abort
            return;
        }
    }

    // keep clkIO ON
    PowerManagement::instance.clk_IO.acquire(PowerManagement::LOCK_USART_TX);

    UCSR0B |= _BV(UDRIE0) | // USART Data Register Empty Interrupt Enable
              _BV(TXEN0);   // Transmitter Enable
}

void AvrUsart::suspendTX()
{
    UCSR0B &=~ _BV(UDRIE0); // USART Data Register Empty Interrupt Enable
}

/* USART, Data Register Empty */
ISR(USART_UDRE_vect)
{
    AvrUsart::instance.txInterrupt();
}

/* USART, USART Transmit Complete */
ISR(USART_TX_vect)
{
    PowerManagement::instance.clk_IO.release(PowerManagement::LOCK_USART_TX);
}

void AvrUsart::txInterrupt()
{
    /* Try to send data now if possible */
    while(UCSR0A & _BV(UDRE0)) {

        // Get next byte from the write buffer list
        if (write_size) {

            UDR0 = *write_ptr++;
            if (--write_size == 0) {
                // The current write buffer is empty

                // Remove this buffer from the list
                Buffer* buf = write_list.front();
                do {
                    write_list.remove(buf);

                    // Call its callback
                    if (buf->callback) {
                        buf->callback->onWriteFinished(buf);
                    }

                    // Get the next buffer
                    buf = write_list.front();
                    if (buf) {
                        write_ptr = buf->ptr;
                        write_size = buf->size;
                    } else {
                        // No more buffers to write, suspend TX
                        suspendTX();
                        return;
                    }
                } while(!write_size);
            }
        } else {
            // Should not happen
            suspendTX();
            return;
        }
    }
}

// ///////////////////////////////////////////////////////
//   Power management
// ///////////////////////////////////////////////////////
void AvrUsart::sleep()
{
    Gpio::D0.registerListener(this);
    PowerManagement::instance.clk_IO.release(PowerManagement::LOCK_USART_RX);
}

void AvrUsart::onPinChange()
{
    // Incoming data, deactivate sleep
    Gpio::D0.unregisterListener(this);
    PowerManagement::instance.clk_IO.acquire(PowerManagement::LOCK_USART_RX);
}

} /* namespace octopus */

#endif /* __AVR */
