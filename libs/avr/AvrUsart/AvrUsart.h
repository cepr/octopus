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

#ifndef AVRUSART_H_
#define AVRUSART_H_

#include "Usart.h"
#include "event.h"

/**
 * @brief USART port of an ATMEGA328P.
 *
 * This class is an implementation of Usart class for the ATMEGA328P and similar.
 *
 * The communication protocol is as follow:
 * - baudrate can be choosen
 * - 8 bits per byte
 * - no parity
 * - 1 stop bit
 * - software flow control XON/XOFF
 *
 * It is recommended to use the LinuxSerialPort class to handle the communication protocol correctly.
 *
 * @ingroup COM_STACK
 */
class AvrUsart: public Usart, public Event
{

public:

	typedef enum {
	    B115200,
	    B57600,
	    B38400,
	    B9600,
	    B2400
	} UsartBaudrate;

	/**
	 * @brief Constructor.
	 *
	 * @param[in] baudrate Baudrate:
	 *                     - B115200
	 *                     - B57600
	 *                     - B38400
	 *                     - B9600
	 *                     - B2400
	 */
	AvrUsart(UsartBaudrate baudrate = B57600);

	/**
	 * @brief Send a single byte to the AVR USART controller.
	 *
	 * @param c Byte to send.
	 */
	void sendByte(unsigned char c);

	/**
	 * @copydoc Usart#isUsartBufferEmpty()
	 */
	virtual bool isUsartBufferEmpty();

private:

	/**
	 * @brief Internal event handler.
	 *
	 * @param[in] what Unused
	 */
	void onEvent(char what);
};

#endif /* AVRUSART_H_ */
