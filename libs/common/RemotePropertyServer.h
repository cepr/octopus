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

#ifndef REMOTEPROPERTYSERVER_H_
#define REMOTEPROPERTYSERVER_H_

#include "Property.h"
#include "PropertyPacket.h"
#include "PropertyPacketListener.h"
#include "PropertyAddress.h"

class PropertyPacket;

// TODO rename RemotePropertyServer to PropertyServer
/**
 * @brief Class used to share local properties to a remote client over a serial link.
 */
class RemotePropertyServer : public PropertyPacketListener {

private:
	Property*		mRoot;
	PropertyPacket*	mBridge;

protected:

public:
	/**
	 * @brief Constructor.
	 * @param[in] root   Local root property to share.
	 * @param[in] bridge Bridge to use to share property.
	 */
	RemotePropertyServer(Property* root, PropertyPacket* bridge);

	void onPropertyPacketReceived(
			PropertyAddress* address,
			unsigned char command,
			const unsigned char *data, char size);
};

#endif /* REMOTEPROPERTYSERVER_H_ */
