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

#ifndef PIPETRANSMISSIONTHREAD_H
#define PIPETRANSMISSIONTHREAD_H

#ifndef AVR

class PipeTransmissionThread;

#include <wx/thread.h> // Base class: wxThread
#include <wx/event.h>
#include <wx/file.h>
#include "UsartBuffer.h"
#include "UsartListener.h"
#include "LinuxSerialPort.h"

/**
 * @brief Serial port transmission thread
 */
class PipeTransmissionThread : public wxThread, private wxEvtHandler {

public:
	/**
	 * @brief Construct a new transmission thread
	 *
	 * @param[in,out] parent Parent
	 */
	PipeTransmissionThread(LinuxSerialPort & parent);

	/**
	 * @brief Sends a single byte
	 *
	 * @param[in] c Byte to send
	 *
	 * This methods append a single byte to the output buffer.
	 *
	 * @return @a true if successful, @a false otherwise
	 */
    bool sendByte(unsigned char c);

	/**
	 * @brief Returns whether or not the output buffer is empty
	 *
	 * This method returns the status of the output buffer.
	 *
	 * @return @a true if buffer is empty, @a false otherwise.
	 */
	bool isUsartBufferEmpty();

	/**
	 * @brief Terminate the thread
	 */
	void Terminate();

private:
	/**
	 * @brief Event entry point
	 *
	 * This method is called by the event handler running on UI thread.
	 */
	void OnEvent( wxCommandEvent &event );

	/**
	 * @Brief Destructor
	 */
	~PipeTransmissionThread();

	LinuxSerialPort* mParent;
	virtual void* Entry();
	wxFile mFile;
	UsartBuffer mBuffer;
	wxMutex mMutex;
	wxCondition mBufferNotEmptyCondition;
};

#endif /* AVR */

#endif // PIPETRANSMISSIONTHREAD_H
