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

#ifndef USART_H_
#define USART_H_

#include "UsartListener.h"

/**
 * @brief Physical layer of the Octopus Communication Stack
 *
 * Abstract base class for all serial communication channels (serial ports, sockets, pipes, etc).
 *
 * This class is an abstract class for all asynchronous serial communication channels. In order to send data,
 * you can use one the following methods:
 * - Usart#sendByte()
 * - Usart#sendBuffer()
 * - Usart#sendHexByte()
 * - Usart#sendHexShort()
 * - Usart#sendString()
 *
 * In order to receive data, you have to implement an UsartListener and register it using registerListener().
 *
 * The data link layer is the layer 1 of the seven-layer OSI model of computer networking.
 * <a href="http://en.wikipedia.org/wiki/Physical_layer">Read more on Wikipedia...</a>
 *
 * @ingroup COM_STACK
 */
class Usart {
protected:
    UsartListener *mListener;
public:
	/**
	 * @brief Constuctor
	 */
    Usart();

	/**
	 * @brief Registers a listener
	 *
	 * @param[in] listener Listener
	 *
	 * This methods register the listener to be called when an incoming byte is available.
	 */
    void registerListener(UsartListener *listener);

	/**
	 * @brief Sends a single byte
	 *
	 * @param[in] c Byte to send
	 *
	 * This methods sends a single byte to the communication channel.
	 */
    virtual void sendByte(unsigned char c) = 0;

	/**
	 * @brief Sends a fixed-sized array of bytes
	 *
	 * @param[in] buffer Pointer to the first byte to send
	 * @param[in] size   Number of bytes to send
	 *
	 * This methods sends \a size bytes from address \a buffer to the communication channel.
	 */
    void sendBuffer(const unsigned char *buffer, char size);

	/**
	 * @brief Sends two ASCII chars representing the hexadecimal value of an 8 bits value
	 *
	 * @param[in] c Value to convert to hexadecimal and to send
	 *
	 * This methods converts \a c into an hexadecimal value encoded in ASCII format, and
	 * sends it to the serial port, without NULL terminating character.
	 */
    void sendHexByte(unsigned char c);

	/**
	 * @brief Sends four ASCII characters representing the hexadecimal value of a 16 bits value
	 * 
	 * @param[in] s Value to convert to hexadecimal and to send
	 * 
	 * This methods converts \a c into an hexadecimal value encoded in ASCII format, and
	 * sends it to the serial port, without NULL terminating character.
	 */
    void sendHexShort(unsigned short s);

	/**
	 * @brief Sends a NULL-terminated char string
	 *
	 * @param[in] txt Pointer to a NULL-terminated char string
	 *
	 * This methods sends a NULL-terminated char string. The NULL character is not send.
	 */
    void sendString(const char *txt);

	/**
	 * @brief Returns whether or not the output buffer is empty
	 *
	 * This method returns the status of the output buffer.
	 *
	 * @return @a true if buffer is empty, @a false otherwise.
	 */
	virtual bool isUsartBufferEmpty() = 0;

	/**
	 * \brief Enquiry
	 * Signal intended to trigger a response at the receiving end, to see if it is still present.
	 */
	static const unsigned char ENQ = 0x5;

	/**
	 * \brief Software flow control XON
	 * Sent to suspend transmission.
	 */
	static const unsigned char XON = 0x11;

	/**
	 * \brief Software flow control XON
	 * Sent to resume transmission.
	 */
	static const unsigned char XOFF = 0x13;

	/**
	 * \brief Negative Acknowledge
	 * Sent by a station as a negative response to the station with which the connection has been set up.
	 * In binary synchronous communication protocol, the NAK is used to indicate that an error was detected
	 * in the previously received block and that the receiver is ready to accept retransmission of that block.
	 * In multipoint systems, the NAK is used as the not-ready reply to a poll.
	 */
	static const unsigned char NAK = 0x15;

	/**
	 * \brief Data link escape
	 */
	static const unsigned char ESC = 0x1b;

	/**
	 * \brief AVRDUDE synchronization
	 * 0x30 is the first byte sent by avrdude to flash a new firmware.
	 */
	static const unsigned char AVRDUDE = 0x30;

	/**
	 * \brief Minimum data byte value
	 * All non-escaped bytes less than this value are considered as control bytes,
	 * whereas all bytes equal or higher than this value are considered as data bytes.
	 * A data byte less than this value should be escaped with \ref Usart#ESC.
	 */
	static const unsigned char DATA_MIN_VALUE = 32;

	/**
	 * \brief XOR mask for escaped bytes
	 */
	static const unsigned char ESC_XOR_MASK = 0x80;
};

#endif /* USART_H_ */
