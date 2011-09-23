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

#ifndef USARTLISTENER_H_
#define USARTLISTENER_H_

#include "Listener.h"

/**
 * @brief USART listener.
 */
class UsartListener : public Listener {
public:
	/**
	 * @brief Listener called when a new byte is received on the USART port.
	 * @param byte Incoming byte.
	 */
    virtual void onUsartReceived(unsigned char byte) = 0;
};

#endif /* USARTLISTENER_H_ */
