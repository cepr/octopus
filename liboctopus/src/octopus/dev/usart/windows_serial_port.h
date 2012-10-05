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

#ifndef WINDOWS_SERIAL_PORT_H_
#define WINDOWS_SERIAL_PORT_H_

#ifdef __WIN32

#include "octopus/dev/usart/usart.h"
#include <wx/string.h>

class WindowsSerialPort : public Usart {
public:
	/**
	 * @brief Constructor
	 *
	 * @param[in]      devicepath Device file path, or 0 for STDIN/STDOUT
	 */
	WindowsSerialPort(const wxString & devicepath);
	virtual ~WindowsSerialPort();
	virtual void sendByte(unsigned char c);
	virtual bool isUsartBufferEmpty();
};

#endif /* __WIN32 */

#endif /* WINDOWS_SERIAL_PORT_H_ */
