/*
 * Copyright 2010 Cedric Priscal
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

#ifndef USARTBUFFER_H_
#define USARTBUFFER_H_

#ifdef AVR
#define USART_BUFFER_CAPACITY 64
#else
#define USART_BUFFER_CAPACITY 256
#endif

/**
 * @brief Simple buffer.
 */
class UsartBuffer {
    unsigned char mBuffer[USART_BUFFER_CAPACITY];
    int mPutIndex;
    int mGetIndex;
public:
	/**
	 * \brief Constructor.
	 */
    UsartBuffer();

	/**
	 * \brief Clear buffer content
	 */
	void reset(void);

	/**
	 * \brief Number of bytes stored in the buffer
	 */
    unsigned char mCount;

	/**
	 * \brief Append a byte to the buffer
	 * \param[in] b Byte to append to the buffer
	 * \return Returns \a true if successful, \a false otherwise.
	 */
    bool PutChar(unsigned char b);

	/**
	 * \brief Returns 
	 */
    unsigned char GetChar();

	/**
	 * \brief Buffer full threshold for software flow-control
	 * Defines the threshold at which an XOFF should be send to suspend transmission
	 */
	static const unsigned char USARTBUFFER_HIGH_THRESHOLD = 48;

	/**
	 * \brief Buffer ready threshold for software flow-control
	 * Defines the threshold at which an XON should be send to resume transmission
	 */
	static const unsigned char USARTBUFFER_LOW_THRESHOLD = 32;
};

#endif /* USARTBUFFER_H_ */
