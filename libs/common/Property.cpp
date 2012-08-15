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

#include "Property.h"

const PROPERTY_INFO Property::PROPERTY_INFO_NAME;
const PROPERTY_INFO Property::PROPERTY_INFO_DESCRIPTION;
const PROPERTY_INFO Property::PROPERTY_INFO_TYPE;
const PROPERTY_INFO Property::PROPERTY_INFO_VALUE;
const PROPERTY_INFO Property::PROPERTY_INFO_CHILDREN;

Property::Property(Packet* packet) :
		mPacket(packet)
#ifdef AVR
        ,mListener(0)
#endif
{
}

void Property::registerListener(PropertyListener* listener)
{
	// Register the listener
#ifdef AVR
	mListener = listener;
#else
    mListeners.push_back(listener);
#endif

	// Report type, value, name and description
	PROPERTY_INFO infos = PROPERTY_INFO_TYPE | PROPERTY_INFO_VALUE;
	if (getName()) {
		infos |= PROPERTY_INFO_NAME;
	}
	if (getDescription()) {
		infos |= PROPERTY_INFO_DESCRIPTION;
	}
	listener->onPropertyChanged(this, infos);

	// Report children (if any)
	unsigned char i;
	Property* child;
	for (i=0; (child = getChild(i)) != 0; i++) {
		listener->onNewChild(this, child, i);
	}
}

void Property::unregisterListener(PropertyListener* listener)
{
#ifdef AVR
	mListener = 0;
#else
    mListeners.remove(listener);
#endif
}
