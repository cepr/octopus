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

#ifndef PACKET_H
#define PACKET_H

#include "buffer.h"
#include "octopus/async_operation.h"
#include "octopus/util/list.h"
#include "usart.h"

namespace octopus {

class Packet: private Buffer::Callback, private AsyncOperation
{
public:
    /**
     * @brief Callback class for packet read or write completion.
     */
    class Callback
    {
    public:
        /**
         * @brief A packet has been read
         */
        virtual void onReadPacketComplete() {}

        /**
         * @brief A packet has been written
         */
        virtual void onWritePacketComplete() {}
    };

    /**
     * @brief Constructor
     *
     * Construct a new Packet instance. This instance will use
     * @a usart to read and write packets, and will call @a
     * callback with argument @a what equal to @a EVENT_READ_FINISHED
     * when a read is finished or @a EVENT_WRITE_FINISHED when a
     * write is finished.
     *
     * @param usart     Usart to use for reading and writing
     * @param callback  Object to call when the methods read() or
     *                  write() have completed.
     */
    Packet(Usart* usart, Callback* callback);

    /**
     * @brief Read a complete packet
     *
     * This function reads a complete packet and store the packet message
     * in @arg message.
     */
    void read(Buffer* message);

    /**
     * @brief Write a complete packet
     */
    void write(List<Buffer> & message);

    typedef enum {
        STATE_IDLE,
        STATE_READING,
        STATE_WRITING
    } State;

    /**
     * @brief Returns the current status of this instance.
     */
    State getState();

private:
    size_t computeSize(const List<Buffer>& message);
    char computeChecksum(const Buffer& message);
    char computeChecksum(const List<Buffer>& message);

    // from Buffer::Callback
    void onReadFinished(Buffer* buffer);
    void onWriteFinished(Buffer* buffer);

    // from AsyncOperation
    void onFinished();

    // private attributes
    Usart* usart;
    Callback* callback;
    char header;
    size_t size;
    char checksum;
    Buffer bheader, bsize, *bmessage, bchecksum;
    State state;
};

} /* namespace octopus */

#endif // PACKET_H
