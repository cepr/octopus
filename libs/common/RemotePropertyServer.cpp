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

#include "RemotePropertyServer.h"
#include "RemoteProperty.h"

static char strlen(const char *str) {
	char i=0;
	while (str[(int)i]) i++;
	return i;
}

RemotePropertyServer::RemotePropertyServer(Property* root, PropertyPacket* bridge) {
	mRoot = root;
	mBridge = bridge;
	mBridge->registerServer(this);
}

void RemotePropertyServer::onPropertyPacketReceived(
		PropertyAddress* address,
		unsigned char command,
		const unsigned char *data, char size) {

	// Parse local properties tree
	Property* p = mRoot;
	for (char i=0; (i < address->mSize) && (p != 0); i++) {
		p = p->getChild(address->mData[(int)i]);
	}

	// Compute response
	switch(command) {
	case RemoteProperty::CMD_GET_TYPE:
		{
			unsigned char type;
			if (p) {
				type = (unsigned char)p->getType();
			} else {
				type = (unsigned char)PROPERTY_TYPE_UNKNOWN;
			}
			mBridge->send(
					address,
					RemoteProperty::RET_GET_TYPE,
					(const unsigned char*)&type, 1);
			break;
		}
	case RemoteProperty::CMD_GET_NAME:
		{
			const char* name;
			char size;
			if (p) {
				name = p->getName();
				size = strlen(name);
			} else {
				name = 0;
				size = 0;
			}
			mBridge->send(
					address,
					RemoteProperty::RET_GET_NAME,
					(const unsigned char*)name, size);
			break;
		}
	case RemoteProperty::CMD_GET_DESCRIPTION:
		{
			const char* description;
			char size;
			if (p) {
				description = p->getDescription();
				size = strlen(description);
			} else {
				description = 0;
				size = 0;
			}
			mBridge->send(
					address,
					RemoteProperty::RET_GET_DESCRIPTION,
					(const unsigned char*)description, size);
			break;
		}
	case RemoteProperty::CMD_GET_VALUE:
		{
			PROPERTY_VALUE value;
			char size;
			if (p) {
                p->getValue(value);
                size = p->getSize();
			} else {
				size = 0;
			}
			mBridge->send(
					address,
					RemoteProperty::RET_GET_VALUE,
					(unsigned char*)&value, size);
			break;
		}
	case RemoteProperty::CMD_SET_VALUE:
		{
			if (p) {
                p->setValue(*(const PROPERTY_VALUE*)data);
			}
			break;
		}
	}
}
