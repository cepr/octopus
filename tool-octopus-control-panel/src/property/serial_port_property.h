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

/**
 * Property that serve as proxy for a remote property and its children.
 *
 * This property has a single child which corresponds to the root
 * remote property of the device connected to the specified serial port.
 */
class SerialPortProperty: public PropertyRecord {
private:
	std::string mDevicePath;
	BoostSerialPort mSerialPort;
	Packet mPacket;
	PropertyAddress mRootAddress;
	RemoteProperty mRootProperty;

public:
	/**
	 * Constructor.
	 *
	 * @param[in] devicepath   Serial port device path, like "/dev/ttyS0" for Linux.
	 *
	 * Use this constructor to create a SerialPortProperty instance.
	 */
	SerialPortProperty(const std::string & devicepath);

	/**
	 * Destructor.
	 */
	virtual ~SerialPortProperty();

	/**
	 * Returns the serial port device path.
	 *
	 * @return This function returns the serial port device path that was specified in @see #SerialPortProperty.
	 */
	const char* getName() const;

	/**
	 * Returns "Serial port".
	 *
	 * @return This function returns a description of the property.
	 */
	const char* getDescription();

	/**
	 * Returns the remote property.
	 *
	 * @param[in] index  Child index, only 0 is supported.
	 *
	 * This property has only one child with index 0. This child correspond to
	 * the remote property of the device which is connected to the serial port.
	 *
	 * @return This function returns the remote property if index is zero, 0 otherwise.
	 */
	Property* getChild(unsigned char index);

	/**
	 * Requests a refresh of the tracked remote property and all its children.
	 *
	 * This function triggers a refresh of the remote property and all its children.
	 */
	virtual void refresh();
};

#endif // SERIALPORTPROPERTY_H
