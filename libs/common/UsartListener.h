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

#ifndef USARTLISTENER_H_
#define USARTLISTENER_H_

#include "Listener.h"

/**
 * @brief USART listener
 *
 * @ingroup COM_STACK
 */
class UsartListener : public Listener {
public:
	/**
	 * @brief Listener called when a new byte is received on the USART port
	 *
	 * @param byte Incoming byte.
	 *
	 * You should override this method in order to receive bytes from an Usart instance.
	 * In addition, you should register your class using Usart::registerListener().
	 */
    virtual void onUsartReceived(unsigned char byte) = 0;

	/**
	 * @brief Listener called when output buffer is empty
     *
	 * You should override this method in order to be notified when the output buffer is
	 * ready to receive new data.
	 * In addition, you should register your class using Usart::registerListener().
	 */
    virtual void onUsartBufferEmpty() = 0;
};

#endif /* USARTLISTENER_H_ */
