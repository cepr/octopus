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

#include "pipe_reception_thread.h"
#include <wx/log.h>
#include <string.h>
#include <wx/file.h>
#include "Usart.h"

DEFINE_EVENT_TYPE(wxEVT_SERIAL_PORT_RX_EVENT)

PipeReceptionThread::PipeReceptionThread(LinuxSerialPort & parent) :
		mParent(&parent)
{
	// Connect event to this class
	Connect(wxEVT_SERIAL_PORT_RX_EVENT, wxCommandEventHandler(PipeReceptionThread::OnEvent));
	// Self construct and run the thread
	Create();
	Run();
}

PipeReceptionThread::~PipeReceptionThread()
{
	Disconnect(wxEVT_SERIAL_PORT_RX_EVENT, wxCommandEventHandler(PipeReceptionThread::OnEvent));
}

void* PipeReceptionThread::Entry()
{
	bool escaping = false;
	while(!TestDestroy()) {

		// Try to open the device for read only access
		if (!mFile.IsOpened()) {
			if (!mParent->openDevice(mFile, wxFile::read))
			{
				// Open failed, retry every 500 ms
				Sleep(500);
				continue;
			}
		}

		// Start reading
		unsigned char b;
		while(mFile.Read(&b, 1) == 1) {

			//wxLogDebug("\033[0;32m%02x \033[0m", (int)b);

			if (escaping) {
				// this byte has been escaped
				b ^= Usart::ESC_XOR_MASK;
				escaping = false;
			} else if (b == Usart::ESC) {
				escaping = true;
				continue;
			} else if (b < Usart::DATA_MIN_VALUE) {
				// Unknown special byte
				continue;
			}

			mMutex.Lock();
			bool ret = mBuffer.PutChar(b);
			mMutex.Unlock();
			if (ret) {
				// TODO Sending an event for each received byte may be too CPU expensive
				wxCommandEvent event( wxEVT_SERIAL_PORT_RX_EVENT );
				AddPendingEvent(event);
			} else {
				// Buffer overflow !
				wxLogWarning("Serial port reception overflow");
				// TODO notify listener about the overflow
			}
		}

		// In case of error or end of file, we close everything and restart
		mFile.Close();
		escaping = false;
	}
	return 0;
}

void PipeReceptionThread::OnEvent( wxCommandEvent &event )
{
	mMutex.Lock();
	while(mBuffer.mCount > 0) {
		unsigned char c = mBuffer.GetChar();
		if (mParent->mListener) {
			mMutex.Unlock();
			mParent->mListener->onUsartReceived(c);
			mMutex.Lock();
		}
	}
	mMutex.Unlock();
}

void PipeReceptionThread::Terminate()
{
	mFile.Close();
	Delete();
}
