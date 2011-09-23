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

#ifndef REMOTEPROPERTY_H_
#define REMOTEPROPERTY_H_

#include "Property.h"

class RemoteProperty : public Property {

public:
	static const unsigned char CMD_GET_TYPE         = 247;  // 0xf7
	static const unsigned char RET_GET_TYPE         = 248;  // 0xf8
	static const unsigned char CMD_GET_NAME 		= 249;	// 0xf9
	static const unsigned char RET_GET_NAME         = 250;  // 0xfa
	static const unsigned char CMD_GET_DESCRIPTION	= 251;  // 0xfb
	static const unsigned char RET_GET_DESCRIPTION	= 252;  // 0xfc
	static const unsigned char CMD_GET_VALUE 		= 253;  // 0xfd
	static const unsigned char RET_GET_VALUE 		= 254;  // 0xfe
	static const unsigned char CMD_SET_VALUE 		= 255;  // 0xff

};

#endif /* REMOTEPROPERTY_H_ */
