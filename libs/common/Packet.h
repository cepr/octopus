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

#ifndef PACKET_H_
#define PACKET_H_

#include "Usart.h"
#include "UsartListener.h"
#include "PacketListener.h"

/**
 * \brief Class that listens to incoming bytes from an Usart, and formats complete packets.
 *
 * \ingroup COM_STACK
 */
class Packet : private UsartListener {

private:
	static const unsigned char ESCAPE	= 0x80;
	static const unsigned char START	= 's';
	static const unsigned char STOP		= '\n';

	Usart* 			mUsart;
#ifdef linux
	unsigned char 	mBuffer[512];
#else
	unsigned char 	mBuffer[64];
#endif
	unsigned char	mSize;
	bool 			mStarted;
	bool 			mEscape;
	PacketListener* mListener;

	/**
	 * \copydoc UsartListener::onUsartReceived()
	 */
	void onUsartReceived(unsigned char byte);

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
	 * \brief Sends a packet
	 *
	 * \param[in] buffer Data to send
	 * \param[in] size   Size of \a buffer
	 */
	void sendPacket(const unsigned char *buffer, char size);
};

#endif /* PACKET_H_ */
