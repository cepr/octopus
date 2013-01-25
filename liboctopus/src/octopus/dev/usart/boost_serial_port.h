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

#ifndef BOOST_SERIAL_PORT_H_
#define BOOST_SERIAL_PORT_H_

#ifndef __AVR__

#include "usart.h"
#include <wx/timer.h>
#include <wx/thread.h>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/io_service.hpp>
#include <string>

class BoostSerialPort: public Usart, private wxTimer {
public:
	/**
	 * @brief Constructor
	 *
	 * @param[in] devicepath Device file path
	 */
	BoostSerialPort(const char* devicepath);
	virtual ~BoostSerialPort();
	virtual void sendByte(unsigned char c);
	virtual bool isUsartBufferEmpty();

private:
	// wxTimer notification
	virtual void Notify();

	// Reset serial port status
	void reset();

	// Attributes
	std::string mDevicePath;
	boost::asio::io_service mIoService;
	boost::asio::serial_port mSerialPort;
	class PipeReceptionThread *mReceptionThread;
	friend class PipeReceptionThread;
};

#endif /* __AVR__ */

#endif /* BOOST_SERIAL_PORT_H_ */
