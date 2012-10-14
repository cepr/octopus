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

#ifndef PIPERECEPTIONTHREAD_H
#define PIPERECEPTIONTHREAD_H

#ifndef __AVR

#include <wx/thread.h> // Base class: wxThread
#include <wx/event.h>
#include <wx/file.h>
#include <boost/system/error_code.hpp>
#include "usart_buffer.h"
#include "usart_listener.h"

/**
 * @brief Serial port reception thread
 */
class PipeReceptionThread: public wxThread, private wxEvtHandler {

public:
	/**
	 * @brief Construct a new reception thread
	 *
	 * @param[in,out] parent Parent
	 */
	PipeReceptionThread(class BoostSerialPort* parent);

	/**
	 * @brief Terminate the thread
	 */
	void Terminate();

private:
	/**
	 * @brief Boost::asio asynchronous read handler
	 *
	 * @param[in] error              Result of operation.
	 * @param[in] bytes_transferred  Number od bytes read.
	 */
	void handler(const boost::system::error_code& error, std::size_t bytes_transferred);

	/**
	 * @brief Event entry point
	 *
	 * This method is called by the event handler running on UI thread.
	 */
	void OnEvent(wxCommandEvent &event);

	/**
	 * @brief Destructor
	 */
	~PipeReceptionThread();

	/**
	 * wxThread entry point.
	 */
	virtual void* Entry();

	class BoostSerialPort *mParent;
	UsartBuffer mBuffer;
	wxMutex mMutex;
	bool mEscaping;
	unsigned char mBoostBuffer[32];
};

#endif /* __AVR */

#endif // PIPERECEPTIONTHREAD_H
