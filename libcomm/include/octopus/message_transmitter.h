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

#ifndef MESSAGE_TRANSMITTER_H
#define MESSAGE_TRANSMITTER_H

#include "packet.h"
#include "usart.h"
#include "octopus/util/list.h"
#include "buffer.h"

namespace octopus {

class MessageTransmitter: public Packet::Callback
{
public:
    class Message: public List<Buffer> {
    public:
        // For List<Message>
        Message* prev;
        Message* next;
    };

    MessageTransmitter(Usart* usart);

    /**
     * @brief Write a message
     *
     * @param message  Message content
     */
    void write(Message &message);

protected:
    // From Packet::Callback
    void onWritePacketComplete();

    Packet packet;
    List<Message> queue;
};

} /* namespace octopus */

#endif // MESSAGE_TRANSMITTER_H
