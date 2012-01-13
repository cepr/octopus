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

#ifndef PROPERTYPACKETLISTENER_H_
#define PROPERTYPACKETLISTENER_H_

#include "Listener.h"
#include "Property.h"
#include "PropertyAddress.h"

class PropertyPacketListener : public Listener {
public:
	virtual void onPropertyPacketReceived(
			PropertyAddress *address,
			unsigned char command,
			const unsigned char *data, char size)=0;
};

#endif /* PROPERTYPACKETLISTENER_H_ */