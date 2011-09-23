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

#include "LinuxRemoteProperty.h"
#include <string.h>
#include <stdio.h>

#define TIMEOUT 5000

LinuxRemoteProperty::LinuxRemoteProperty(PropertyAddress* address, PropertyPacket* bridge) {
	mAddress = address;
	mBridge = bridge;
	mBridge->registerClient(this);
	mType = PROPERTY_TYPE_INVALID;
	mName = 0;
	mDescription = 0;
	mValue = 0;
	mSize = -1;
}

PROPERTY_TYPE LinuxRemoteProperty::getType() {
	while (mType == PROPERTY_TYPE_INVALID) {
		mBridge->registerClient(this);
		mBridge->send(mAddress, CMD_GET_TYPE, (const unsigned char*)0, 0);
		wait(TIMEOUT);
	}
	return mType;
}

const char* LinuxRemoteProperty::getName() {
	while (mName == 0) {
		mBridge->registerClient(this);
		mBridge->send(mAddress, CMD_GET_NAME, (const unsigned char*)0, 0);
		wait(TIMEOUT);
	}
	return mName;
}

const char* LinuxRemoteProperty::getDescription() {
	while (!mDescription) {
		mBridge->registerClient(this);
		mBridge->send(mAddress, CMD_GET_DESCRIPTION, (const unsigned char*)0, 0);
		wait(TIMEOUT);
	}
	return mDescription;
}

void LinuxRemoteProperty::getValue(PROPERTY_VALUE & value)
{
	if (mValue) {
		delete mValue;
		mValue = 0;
	}
	mSize = -1;
	while(mSize == -1) {
		mBridge->registerClient(this);
		mBridge->send(mAddress, CMD_GET_VALUE, (const unsigned char*)0, 0);
		wait(TIMEOUT);
	}
	if (mSize > 0) {
        if (mSize > (char)sizeof(PROPERTY_VALUE)) {
            mSize = (char)sizeof(PROPERTY_VALUE);
        }
        memcpy(&value, mValue, mSize);
	} else {
		memset(&value, 0, sizeof(PROPERTY_VALUE));
	}
}

void LinuxRemoteProperty::setValue(const PROPERTY_VALUE & value)
{
    char size = getSize();
    if (size > 0) {
        mBridge->send(mAddress, CMD_SET_VALUE, (const unsigned char*)&value, size);
    }
}

Property* LinuxRemoteProperty::getChild(unsigned char index) {
	PropertyAddress* child_address = mAddress->getChild(index);
	LinuxRemoteProperty* child = new LinuxRemoteProperty(child_address, mBridge);
	if (child->getType() != PROPERTY_TYPE_UNKNOWN) {
		// Child is valid !
		return child;
	} else {
		//delete child;
		return 0;
	}
}

// Called from UART reception thread
void LinuxRemoteProperty::onPropertyPacketReceived(
		PropertyAddress* address,
		unsigned char command,
		const unsigned char *data, char size) {

	if (mAddress->isEqual(address)) {
		// Good, the packet is for us
		switch(command) {
		case RET_GET_TYPE:
			if (size != 1) {
				return;
			}
			mType = (PROPERTY_TYPE)*data;
			break;
		case RET_GET_NAME:
			mName = new char[size + 1];
			memcpy(mName, data, size);
			mName[(int)size] = '\0';
			break;
		case RET_GET_DESCRIPTION:
			mDescription = new char[size + 1];
			memcpy(mDescription, data, size);
			mDescription[(int)size] = '\0';
			break;
		case RET_GET_VALUE:
			mValue = new unsigned char[(int)size];
			memcpy(mValue, data, size);
			mSize = size;
			break;
		}
		// Awake the waiting main thread.
		notify();
	}
}

char LinuxRemoteProperty::getSize()
{
    switch(getType()){
        case PROPERTY_TYPE_BOOL:
        case PROPERTY_TYPE_U8:
        case PROPERTY_TYPE_S8:
            return 1;
        
        case PROPERTY_TYPE_U16:
        case PROPERTY_TYPE_S16:
            return 2;
        
        default:
            return 0;
    }
}

