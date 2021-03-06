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

#include "serial_port_property.h"

using std::string;

// constructor
SerialPortProperty::SerialPortProperty(const std::string & devicepath) :
	PropertyRecord(0),
    mDevicePath(devicepath),
	mSerialPort(devicepath.c_str()),
	mPacket(&mSerialPort),
    mRootProperty(&mPacket)
{
    mPacket.registerListener(&mRootProperty);
}

// destructor
SerialPortProperty::~SerialPortProperty()
{
}

// Property inherited virtual functions

const char* SerialPortProperty::getName() const
{
	return mDevicePath.c_str();
}

const char* SerialPortProperty::getDescription()
{
	return "Serial port";
}

Property* SerialPortProperty::getChild(unsigned char index)
{
	if (index == 0) {
		return &mRootProperty;
	} else {
		return NULL;
	}
}

void SerialPortProperty::refresh()
{
	mRootProperty.refresh();
}
