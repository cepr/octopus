/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef USART_H_
#define USART_H_

#include "buffer.h"
#include "octopus/list.h"
#include "octopus/lock.h"

namespace octopus {

/**
 * @brief Abstract base class for all serial communication channels.
 *
 * This class is an abstract class for all asynchronous serial communication channels
 * (serial ports, sockets, pipes, etc).
 *
 * The reading and writing channels of this class are asynchronous in order to support
 * microcontrollers without multi-threading support.
 *
 * In order to receive data, you have to provide your own buffer which will be filled
 * with the read data. You may also implement the Buffer::Callback interface and associate
 * it to your buffer in order to be notified when the read has finished.
 *
 * In order to send data, you have to prepare one or more instances of Buffer and post
 * them to the Usart write queue using write(Buffer*) or write(List<Buffer*>).
 *
 * @par Example
 * @include usart-sample.cpp
 */
class Usart {

public:

    /**
     * @brief Reads data from the USART.
     *
     * This function starts an asynchronous read operation. The number of
     * bytes to read is specified by the size of @a buffer.
     *
     * You can be notified of the end of the operation by registering a
     * buffer callback to @a buffer.
     *
     * @param buffer Buffer to fill with read data.
     *
     * @see read(List<Buffer>*)
     */
    void read(Buffer* buffer) {
        Lock l;
        bool resume_read = read_list.isEmpty();
        read_list.insert(buffer);
        if (resume_read) {
            // Call underlying implementation to resume reception
            resumeRX();
        }
    }

    /**
     * @brief Reads data from the USART.
     *
     * This function starts an asynchronous read operation. The operation
     * will stop when all the provided @a buffers will have been filled
     * with read data.
     *
     * You can be notified of the end of the operation by registering a
     * buffer callback to the last buffer of @a buffers. You can also
     * be notified of intermediate status by registering a callback to
     * any other buffer of @a buffers.
     *
     * @param buffers Buffer List to fill with read data.
     *
     * @see read(Buffer*)
     */
    void read(List<Buffer>* buffers) {
        Lock l;
        bool resume_read = read_list.isEmpty();
        read_list.insert(buffers);
        if (resume_read) {
            // Call underlying implementation to resume reception
            resumeRX();
        }
    }

    /**
     * @brief Writes data to the USART.
     *
     * This function starts an asynchronous write operation. The data to
     * write is taken from @a buffer.
     *
     * You can be notified of the end of the operation by registering a
     * buffer callback to the @a buffer.
     *
     * @param buffer Buffer pointing to the data to write.
     *
     * @see write(List<Buffer*>)
     */
    void write(Buffer* buffer) {
        Lock l;
        bool resume_write = write_list.isEmpty();
        write_list.insert(buffer);
        if (resume_write) {
            // Call underlying implementation to resume transmission
            resumeTX();
        }
    }

    /**
     * @brief Writes data to the USART.
     *
     * This function starts an asynchronous write operation. The data to
     * write is taken from the list @a buffers.
     *
     * You can be notified of the end of the operation by registering a
     * buffer callback to the last buffer of @a buffers. You can also
     * be notified of intermediate status by registering a callback to
     * any other buffer of @a buffers.
     *
     * @param buffers Buffer List pointing to the data to write.
     *
     * @see write(Buffer*)
     */
    void write(List<Buffer>* buffers) {
        Lock l;
        bool resume_write = write_list.isEmpty();
        write_list.insert(buffers);
        if (resume_write) {
            // Call underlying implementation to resume transmission
            resumeTX();
        }
    }

protected:

    // Read buffer list
    List<Buffer> read_list;

    // Write buffer list
    List<Buffer> write_list;

private:

    // Child classes must implement this method to activate the reception.
    virtual void resumeRX() = 0;

    // Child classes must implement this method to activate the transmission.
    virtual void resumeTX() = 0;
};

/**
 * @example usart-sample.cpp
 * This is an example of how to use the octopus::Usart class.
 */

} /* namespace octopus */

#endif /* USART_H_ */
