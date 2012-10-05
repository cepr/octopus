/*
 * Copyright 2010-2012 Cedric Priscal
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

#ifndef LINUXSERIALPORT_H_
#define LINUXSERIALPORT_H_

#ifdef __linux

class LinuxSerialPort;

#include "usart.h"
#include "pipe_reception_thread.h"
#include "pipe_transmission_thread.h"

/**
 * @brief Implementation of the Usart class for a Linux serial port.
 *
 * @ingroup COM_STACK
 */
class LinuxSerialPort : public Usart
{
public:
	/**
	 * @brief Constructor
	 *
	 * @param[in]      devicepath Device file path, or 0 for STDIN/STDOUT
	 */
	LinuxSerialPort(const wxString & devicepath);

	/**
	 * @brief Destructor
	 */
	~LinuxSerialPort();

	/**
	 * @copydoc Usart::isUsartBufferEmpty()
	 */
	bool isUsartBufferEmpty();

	/**
	 * @copydoc Usart::sendByte()
	 */
	void sendByte(unsigned char c);

private:
	/**
	 * @brief Get device descriptor
	 *
	 * @param[int,out] file wxFile object to use
	 * @param[in]      mode Port access mode (wxFile::read or wxFile::write)
	 *
	 * @return @a true if successful, @a false otherwise
	 *
	 * This method is called by ::mTxThread and ::mRxThread
	 */
	bool openDevice(wxFile & file, wxFile::OpenMode mode);

private:
	wxString                mDevicePath;
	PipeTransmissionThread *mTxThread;
	PipeReceptionThread    *mRxThread;

	friend class PipeTransmissionThread;
	friend class PipeReceptionThread;
};

#endif /* __linux */

#endif /* LINUXSERIALPORT_H_ */
