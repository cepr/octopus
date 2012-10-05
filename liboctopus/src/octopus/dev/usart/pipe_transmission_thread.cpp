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

#ifdef __linux

#include "pipe_transmission_thread.h"
#include "usart.h"
#include <wx/log.h>

DEFINE_EVENT_TYPE(wxEVT_SERIAL_PORT_TX_EVENT)

PipeTransmissionThread::PipeTransmissionThread(LinuxSerialPort & parent) :
		mParent(&parent),
		mBufferNotEmptyCondition(mMutex)
{
	// Connect out event to this class
	Connect(wxEVT_SERIAL_PORT_TX_EVENT, wxCommandEventHandler(PipeTransmissionThread::OnEvent));
	// Self construct and run the thread
	Create();
	Run();
}

PipeTransmissionThread::~PipeTransmissionThread()
{
	Disconnect(wxEVT_SERIAL_PORT_TX_EVENT, wxCommandEventHandler(PipeTransmissionThread::OnEvent));
}

bool PipeTransmissionThread::sendByte(unsigned char c)
{
	wxMutexLocker lock(mMutex);
	bool ret = mBuffer.PutChar(c);
	if (ret && (mBuffer.mCount == 1)) {
		mBufferNotEmptyCondition.Signal();
	}
	return ret;
}

bool PipeTransmissionThread::isUsartBufferEmpty()
{
	wxMutexLocker lock(mMutex);
	return (mBuffer.mCount == 0);
}

void* PipeTransmissionThread::Entry()
{
	while(!TestDestroy()) {

		if (!mFile.IsOpened()) {
			// Try to open the device for write only access
			if (!mParent->openDevice(mFile, wxFile::write))
			{
				// Opening failed, retry every 500 ms
				Sleep(500);
				continue;
			}
		}

		mMutex.Lock();
		if (mBuffer.mCount > 0) {
			unsigned char b = mBuffer.GetChar();
			unsigned char buffer[2];
			size_t size;
			mMutex.Unlock();

			if ((b < Usart::DATA_MIN_VALUE) || (b == Usart::AVRDUDE)) {
				// Special byte that must be escaped
				buffer[0] = Usart::ESC;
				buffer[1] = b ^ Usart::ESC_XOR_MASK;
				size = 2;
				//wxLogDebug("\033[0;34m%02x.%02x \033[0m", (int)buffer[0], (int)buffer[1]);
			} else {
				// Normal byte
				buffer[0] = b;
				size = 1;
				//wxLogDebug("\033[0;34m%02x \033[0m", (int)buffer[0]);
			}

			if(mFile.Write(buffer, size) != size) {
				// On error, close the device
				mFile.Close();
			}
		} else {
			// No more data to send, request for more data
			wxCommandEvent event( wxEVT_SERIAL_PORT_TX_EVENT );
			AddPendingEvent(event);

			// Wait for more data
			mBufferNotEmptyCondition.WaitTimeout(500);
			mMutex.Unlock();
		}
	}
	return 0;
}

void PipeTransmissionThread::OnEvent(wxCommandEvent& event)
{
	if (mParent->mListener) {
		mParent->mListener->onUsartBufferEmpty();
	}
}

void PipeTransmissionThread::Terminate()
{
	mFile.Close();
	Delete();
}

#endif /* __linux */
