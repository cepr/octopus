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

#ifndef PACKETLISTENER_H_
#define PACKETLISTENER_H_

#include "Listener.h"

/**
 * @brief Packet listener
 *
 * @ingroup COM_STACK
 */
class PacketListener : public Listener {
public:
	/**
	 * @brief Listener called when a new packet is received
	 *
	 * @param[in] data Incoming packet bytes, excluding START and STOP bytes.
	 * @param[in] size Size of @a data.
	 */
    virtual void onPacketReceived(const unsigned char *data, unsigned char size) = 0;

	/**
	 * @brief Listener called when new packets can be sent
	 *
	 * @param[in,out] data     Packet data
	 * @param[in,out] size     Packet size
	 * @param[in]     capacity Capacity of @a data
	 *
	 * @return @a true if a packet should be sent with content of @a data, @a false otherwise.
	 *
	 * This method is called recursively by itself, starting from the root remote property.
	 */
	virtual bool onReadyToSend(unsigned char* data, unsigned char & size, unsigned char capacity) = 0;
};

#endif /* PACKETLISTENER_H_ */
