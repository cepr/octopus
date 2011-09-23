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

#include "PropertyPacket.h"
#include "RemoteProperty.h"
#include "PropertyAddress.h"

PropertyPacket::PropertyPacket(Packet* packet) {
	mPacket = packet;
    mClient = 0;
    mServer = 0;
	mPacket->registerListener(this);
}

void PropertyPacket::registerClient(PropertyPacketListener* client) {
	mClient = client;
}

void PropertyPacket::registerServer(PropertyPacketListener* server) {
	mServer = server;
}

void PropertyPacket::onPacketReceived(unsigned char *data, char size) {

	char i;
	PropertyAddress address;
	address.mData = data;

	for (i = 0; i < size; i++) {

		switch(data[(int)i]) {
		case RemoteProperty::CMD_GET_TYPE:
		case RemoteProperty::CMD_GET_NAME:
		case RemoteProperty::CMD_GET_DESCRIPTION:
		case RemoteProperty::CMD_GET_VALUE:
		case RemoteProperty::CMD_SET_VALUE:
			// Packet is a request: RemotePropertyServer will deal with it.
			address.mSize = i;
			mServer->onPropertyPacketReceived(&address, data[(int)i], &data[(int)i+1], size-i-1);
			return;
		case RemoteProperty::RET_GET_TYPE:
		case RemoteProperty::RET_GET_NAME:
		case RemoteProperty::RET_GET_DESCRIPTION:
		case RemoteProperty::RET_GET_VALUE:
			// Packet is a response: RemotePropertyClient will deal with it.
			address.mSize = i;
			mClient->onPropertyPacketReceived(&address, data[(int)i], &data[(int)i+1], size-i-1);
			return;
		}
	}
}

void PropertyPacket::send(
		PropertyAddress* address,
		unsigned char command,
		const unsigned char* data,
		char size) {
	unsigned char packet[64];
	char i,j;
	for (i=0; i<address->mSize; i++) {
		packet[(int)i] = address->mData[(int)i];
	}
	packet[(int)i++] = command;
	for (j=0; j<size; j++) {
		packet[(int)i++] = data[(int)j];
	}
	mPacket->sendPacket(packet, i);
}
