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

#ifndef AVRUSART_H_
#define AVRUSART_H_

#include "Usart.h"
#include "Handler.h"

/**
 * @brief Implementation of Usart class for the USART port of an ATMEGA328P.
 */
class AvrUsart: public Usart, public Handler {

public:

	typedef enum {
		B115200,
		B38400,
		B9600,
		B2400
	} UsartBaudrate;

	/**
	 * @brief Constructor.
	 * AVR USART is setup as 115200,N,8,1
	 */
	AvrUsart(UsartBaudrate baudrate = B115200);

	/**
	 * @brief Send a single byte on the AVR USART controller.
	 * @param c Byte to send.
	 */
	void sendByte(unsigned char c);

	/**
	 * @copydoc Handler::onEvent()
	 */
	void onEvent(char what);
};

#endif /* AVRUSART_H_ */
