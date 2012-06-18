/*
 * Copyright 2012 Cedric Priscal
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

#ifndef LOCALPROPERTY_H
#define LOCALPROPERTY_H

#include "Property.h"

/**
 * @brief Class representing a local property
 *
 * @ingroup COM_STACK
 */
class LocalProperty: public Property
{

public:
	/**
	 * @brief Construct a local property
	 */
	LocalProperty(Packet* packet);

	/**
	 * @copydoc PacketListener::onPacketReceived()
	 */
	virtual void onPacketReceived(const unsigned char* data, unsigned char size);

	/**
	 * @copydoc PacketListener::onReadyToSend()
	 */
	virtual bool onReadyToSend(unsigned char* data, unsigned char & size, unsigned char capacity);

	/**
	 * @copydoc Property::refresh();
	 */
	virtual void refresh();

protected:
	PROPERTY_INFO mInfoToReport;
};

#endif // LOCALPROPERTY_H
