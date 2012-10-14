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

#include "pipe_reception_thread.h"
#include <wx/log.h>
#include <string.h>
#include <wx/file.h>
#include "usart.h"
#include "boost_serial_port.h"
#include <boost/bind.hpp>
#include <boost/asio/buffer.hpp>

DEFINE_EVENT_TYPE(wxEVT_SERIAL_PORT_RX_EVENT)

PipeReceptionThread::PipeReceptionThread(BoostSerialPort* parent) :
		mParent(parent), mEscaping(false) {
	// Connect event to this class
	Connect(wxEVT_SERIAL_PORT_RX_EVENT, wxCommandEventHandler(PipeReceptionThread::OnEvent));
	// Self construct and run the thread
	Create();
	Run();
}

PipeReceptionThread::~PipeReceptionThread() {
	Disconnect(wxEVT_SERIAL_PORT_RX_EVENT, wxCommandEventHandler(PipeReceptionThread::OnEvent));
}

void* PipeReceptionThread::Entry() {
	wxLogDebug("PipeReceptionThread::Entry begin");
	try {
		// Trigger an initial asynchronous reading, the next readings will be launched from ::handler directly
		mParent->mSerialPort.async_read_some(boost::asio::buffer((void*) mBoostBuffer, sizeof(mBoostBuffer)),
				boost::bind(&PipeReceptionThread::handler, this, _1, _2));
		mParent->mIoService.run();
	} catch (boost::system::system_error & e) {
		wxLogDebug(e.what());
		mParent->reset();
	}
	wxLogDebug("PipeReceptionThread::Entry end");
	return 0;
}

void PipeReceptionThread::handler(const boost::system::error_code& error, std::size_t bytes_transferred) {
	unsigned char b;
	std::size_t i;

	// Throw an exception in case of error
	boost::asio::detail::throw_error(error, "handler");

	for (i = 0; i < bytes_transferred; i++) {

		b = mBoostBuffer[i];

		if (mEscaping) {
			// this byte has been escaped
			b ^= Usart::ESC_XOR_MASK;
			mEscaping = false;
		} else if (b == Usart::ESC) {
			mEscaping = true;
			continue;
		} else if (b == Usart::NAK) {
			// Buffer overflow from remote device !
			wxLogWarning("NAK received from remote device");
			// TODO: reset receive buffer
			continue;
		} else if (b < Usart::DATA_MIN_VALUE) {
			// Unknown special byte
			continue;
		}

		mMutex.Lock();
		bool ret = mBuffer.PutChar(b);
		mMutex.Unlock();
		if (!ret) {
			// Buffer overflow !
			wxLogWarning("Serial port reception overflow");
			// TODO notify listener about the overflow
		}
	}

	wxCommandEvent event(wxEVT_SERIAL_PORT_RX_EVENT);
	AddPendingEvent(event);

	mParent->mSerialPort.async_read_some(boost::asio::buffer((void*) mBoostBuffer, sizeof(mBoostBuffer)),
			boost::bind(&PipeReceptionThread::handler, this, _1, _2));
}

void PipeReceptionThread::OnEvent(wxCommandEvent &event) {
	mMutex.Lock();
	while (mBuffer.mCount > 0) {
		unsigned char c = mBuffer.GetChar();
		if (mParent->mListener) {
			mMutex.Unlock();
			mParent->mListener->onUsartReceived(c);
			mMutex.Lock();
		}
	}
	mMutex.Unlock();
}

void PipeReceptionThread::Terminate() {
	// TODO Abort asynchronous task
	Delete();
}

#endif /* __AVR */
