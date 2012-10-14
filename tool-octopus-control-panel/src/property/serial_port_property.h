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

#ifndef SERIALPORTPROPERTY_H
#define SERIALPORTPROPERTY_H

#include "octopus/prop/property_record.h"
#include "octopus/dev/usart/boost_serial_port.h"
#include "octopus/prop/packet.h"
#include "octopus/prop/property_address.h"
#include "octopus/prop/remote_property.h"
#include <string>
#include "octopus/prop/property_listener.h"

class SerialPortProperty : public PropertyRecord
{
private:
	std::string		    mDevicePath;
	BoostSerialPort     mSerialPort;
	Packet 			    mPacket;
	PropertyAddress     mRootAddress;
	RemoteProperty      mRootProperty;

public:
	SerialPortProperty(const std::string & devicepath);
	~SerialPortProperty();

	const char* getName() const;
	const char* getDescription();
	Property* getChild(unsigned char index);
	virtual void refresh();
};

#endif // SERIALPORTPROPERTY_H
