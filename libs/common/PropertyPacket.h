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

#ifndef PROPERTYPACKET_H_
#define PROPERTYPACKET_H_

class PropertyPacket;

#include "Packet.h"
#include "PacketListener.h"
#include "PropertyPacketListener.h"

/**
 * @brief Class used to transmit and received messages on a serial link.
 * The incoming messages are forwarded either to a RemotePropertyServer, either to
 * a RemotePropertyClient.
 */
class PropertyPacket: public PacketListener {

private:
	Packet*						mPacket;
	PropertyPacketListener*     mServer;
	PropertyPacketListener*     mClient;
	bool						mEscape;
	unsigned char				mAddress[8];
	char                        mAddressSize;
	unsigned char				mCommand;
	unsigned char				mData[16];
	char           				mDataSize;

protected:

public:
	PropertyPacket(Packet* packet);
	void registerClient(PropertyPacketListener* client);
	void registerServer(PropertyPacketListener* server);
	void onPacketReceived(unsigned char *data, char size);
	void send(PropertyAddress* address, unsigned char command, const unsigned char* data, char size);
};

#endif /* PROPERTYPACKET_H_ */
