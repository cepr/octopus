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

#ifndef __AVR

#include "boost_serial_port.h"
#include <boost/asio/serial_port.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include <wx/log.h>
#include "pipe_reception_thread.h"

using boost::asio::serial_port;
using boost::asio::io_service;
using boost::asio::serial_port_base;
using boost::asio::buffer;

BoostSerialPort::BoostSerialPort(const char* devicepath) :
		mDevicePath(devicepath), mIoService(), mSerialPort(mIoService), mReceptionThread(0) {
	// Start a periodic serial port monitoring task
	Notify();
}

BoostSerialPort::~BoostSerialPort() {
	try {
		mSerialPort.close();
	} catch (boost::system::system_error & e) {
		// Ignore the error
	}
}

// This periodic timer check that serial port is still opened, and tries to reopen it if necessary
void BoostSerialPort::Notify() {

	try {
		if (!mSerialPort.is_open()) {
			mSerialPort.open(mDevicePath);
			mSerialPort.set_option(serial_port_base::baud_rate(57600));
			mSerialPort.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
			mSerialPort.set_option(serial_port_base::parity(serial_port_base::parity::none));
			mSerialPort.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
			mSerialPort.set_option(serial_port_base::character_size(8));
			mReceptionThread = new PipeReceptionThread(this);
		}
		wxLogDebug("Serial port ready");
	} catch (boost::system::system_error & e) {
		wxLogDebug(e.what());
		reset();
	}

	// Check serial port status again in 2 seconds
	Start(2000, true);

}

void BoostSerialPort::reset() {
	boost::system::error_code ec;
	mSerialPort.close(ec);
}

void BoostSerialPort::sendByte(unsigned char c) {
	try {
		unsigned char buffer[2];
		size_t size;
		if ((c < DATA_MIN_VALUE) || (c == AVRDUDE)) {
			// Special byte that must be escaped
			buffer[0] = ESC;
			buffer[1] = c ^ ESC_XOR_MASK;
			size = 2;
			//wxLogDebug("\033[0;34m%02x.%02x \033[0m", (int)buffer[0], (int)buffer[1]);
		} else {
			// Normal byte
			buffer[0] = c;
			size = 1;
			//wxLogDebug("\033[0;34m%02x \033[0m", (int)buffer[0]);
		}
		mSerialPort.write_some(boost::asio::buffer((const void*) buffer, size));
	} catch (boost::system::system_error & e) {
		wxLogDebug(e.what());
		reset();
	}
}

bool BoostSerialPort::isUsartBufferEmpty() {
	return true;
}

#endif /* __AVR */
