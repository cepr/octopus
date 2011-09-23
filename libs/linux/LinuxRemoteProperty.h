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

#ifndef LINUXREMOTEPROPERTY_H_
#define LINUXREMOTEPROPERTY_H_

class LinuxRemoteProperty;

#include "RemoteProperty.h"
#include "PropertyAddress.h"
#include "PropertyPacket.h"
#include "PropertyPacketListener.h"
#include "LinuxObject.h"

class LinuxRemoteProperty : public RemoteProperty, public PropertyPacketListener, private LinuxObject {

private:
	PropertyAddress* 	mAddress;
	PropertyPacket*		mBridge;
	PROPERTY_TYPE		mType;
	char* 				mName;
	char*             	mDescription;
	Property*           mChildren;
	unsigned char*      mValue;
	char                mSize;

public:
	LinuxRemoteProperty(PropertyAddress* address, PropertyPacket* bridge);

	PROPERTY_TYPE getType();
	const char* getName();
	const char* getDescription();
    void getValue(PROPERTY_VALUE & value);
    void setValue(const PROPERTY_VALUE & value);
    char getSize();
	Property* getChild(unsigned char index);

	void onPropertyPacketReceived(PropertyAddress *address,
								  unsigned char command,
								  const unsigned char *data, char size);
};

#endif /* LINUXREMOTEPROPERTY_H_ */
