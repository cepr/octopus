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

#ifndef PACKET_H_
#define PACKET_H_

#include "octopus/dev/usart/usart.h"
#include "octopus/dev/usart/usart_listener.h"
#include "packet_listener.h"
#include "octopus/event/event.h"

/**
 * @brief Data link layer of the Octopus Communication Stack
 *
 * This class handle the data link layer of the Octopus Communication Stack. Its role is
 * to transfer data-link frames between two devices.
 *
 * The data link layer is the layer 2 of the seven-layer OSI model of computer networking.
 * <a href="http://en.wikipedia.org/wiki/Data_link_layer">Read more on Wikipedia...</a>
 *
 * @ingroup COM_STACK
 */
class Packet : private UsartListener, private Event
{
public:
	/**
	 * \brief Constructor
	 *
	 * \param[in] usart Usart to connect to
	 */
	Packet(Usart *usart);

	/**
	 * \brief Registers a listener which will be called any time a new complete packet is received
	 *
	 * \param[in] listener Listener
	 */
	void registerListener(PacketListener* listener);

	/**
	 * @brief Request to send a packet
	 */
	void requestToSend();

private:
	static const unsigned char ESCAPE	= 0x80;
	static const unsigned char START	= 's';
	static const unsigned char STOP		= '\n';

	Usart* 			mUsart;
	unsigned char 	mBuffer[64];
	unsigned char	mSize;
	bool 			mStarted;
	bool 			mEscape;
	PacketListener* mListener;

	/**
	 * @copydoc UsartListener::onUsartReceived()
	 */
	void onUsartReceived(unsigned char byte);

	/**
	 * @copydoc UsartListener::onUsartBufferEmpty()
	 */
	virtual void onUsartBufferEmpty();

	/**
	 * @copydoc Event::onEvent()
	 */
	virtual void onEvent(char what);
};

#endif /* PACKET_H_ */
