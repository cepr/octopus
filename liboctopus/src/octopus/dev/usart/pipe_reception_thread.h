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

#ifndef AVR

class PipeReceptionThread;

#include <wx/thread.h> // Base class: wxThread
#include <wx/event.h>
#include <wx/file.h>
#include "UsartBuffer.h"
#include "UsartListener.h"
#include "LinuxSerialPort.h"

/**
 * @brief Serial port reception thread
 */
class PipeReceptionThread : public wxThread, private wxEvtHandler {

public:
	/**
	 * @brief Construct a new reception thread
	 *
	 * @param[in,out] parent Parent
	 */
	PipeReceptionThread(LinuxSerialPort & parent);

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
	 * @brief Destructor
	 */
	~PipeReceptionThread();

	LinuxSerialPort *mParent;
	virtual void* Entry();
	wxFile mFile;
	UsartBuffer mBuffer;
	wxMutex mMutex;
};

#endif /* AVR */

#endif // PIPERECEPTIONTHREAD_H
