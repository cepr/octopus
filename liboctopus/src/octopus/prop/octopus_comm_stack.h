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

#ifndef OCTOPUSCOMMSTACK_H
#define OCTOPUSCOMMSTACK_H

#include "property.h"
#include "packet.h"

/**
 * @brief Octopus Communication Stack template
 *
 * In order to instantiate this template, U has to implement Usart class and
 * P has to implement Property class.
 *
 * Here are some valid instantiations:
 * @code
 * typedef OctopusCommStack<AvrUsart, PropertyRecord> OctopusAvrCommStack;
 * typedef OctopusCommStack<LinuxSerialPort, RemoteProperty> OctopusLinuxCommStack;
 * @endcode 
 *
 * @ingroup COM_STACK
 */
template <class U, class P>
class OctopusCommStack : public P {

public:
	/**
	 * @brief Constructor
	 */
	OctopusCommStack() :
			P(&mPacket),
			mPacket(&mUsart)
	{
		mPacket.registerListener(this);
	}

protected:
	U mUsart;
	Packet mPacket;

};

#endif // OCTOPUSCOMMSTACK_H
