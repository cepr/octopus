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

#ifndef AVRUSART_H_
#define AVRUSART_H_

#ifndef __AVR__
#error avr_usart.h is only supported for AVR
#endif

#include "usart.h"

namespace octopus {

/**
 * @brief USART port of an ATMEGA328P.
 *
 * This class is an implementation of Usart class for the ATMEGA328P and
 * similar.
 *
 * The serial port configuration is as follow:
 * - 57600 bits/s (modifiable with setBaudrate())
 * - 8 bits per character
 * - no parity
 * - 1 stop bit
 */
class AvrUsart: public Usart
{
public:
    /**
     * @brief AvrUsart instance
     */
    static AvrUsart instance;

    /**
     * @brief List of supported baudrates
     *
     * @see #setBaudrate()
     */
	typedef enum {
	    B115200,
	    B57600,
	    B38400,
	    B9600,
	    B2400
    } Baudrate;

    /**
     * @brief Sets the Usart baudrate.
     *
     * @param baudrate  Baudrate:
     *                     - B115200
     *                     - B57600
     *                     - B38400
     *                     - B9600
     *                     - B2400
     */
    void setBaudrate(Baudrate baudrate);

private:
    // Pointer and size for current read and write buffers
    char *write_ptr;
    size_t write_size;

    // Private constructor
    AvrUsart();

    // Called by Usart when a read buffer is added.
    virtual void resumeRX();

    // Suspend reception
    void suspendRX();

    // Called by Usart when write_list is not more empty.
    virtual void resumeTX();

    // Suspend transmission
    void suspendTX();

public:
    // Reception interrupt handler
    void rxInterrupt();

    // Transmission interrupt handler
    void txInterrupt();
};

} /* namespace octopus */

#endif /* AVRUSART_H_ */
