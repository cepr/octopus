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

#ifndef COMMAND_READ_H
#define COMMAND_READ_H

#include "octopus/message_receiver.h"
#include "octopus/message_transmitter.h"
#include "octopus/commands.h"
#include "octopus/buffer.h"
#include <stdint.h>

namespace octopus {

class CommandRead : public MessageReceiver::Handler
{
public:

    CommandRead(MessageTransmitter* transmitter);
    void onMessage(const Buffer &message);

private:
    struct Request {
        uint8_t id;
        uint16_t offset;
        uint16_t size;
    } __attribute__((packed));

    struct Reply {
        uint8_t id;
        uint16_t offset;
    } __attribute__((packed));

    MessageTransmitter* transmitter;
    TBuffer<struct Reply> reply_header;
    Buffer reply_data;
};

} /* namespace octopus */

#endif // COMMAND_READ_H
