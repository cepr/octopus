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

#include "read.h"
#include <string.h>

namespace octopus {

// Constructor
CommandRead::CommandRead(MessageTransmitter* transmitter) :
    Handler(CMD_READ),
    transmitter(transmitter)
{
    reply_header.data.id = CMD_READ;
}

void CommandRead::onMessage(const Buffer &message)
{
    if (message.size == sizeof(struct Request) ) {
        // Read arguments
        const struct Request & args = *(const struct Request*)message.ptr;

        // Write reply
        MessageTransmitter::Message reply;
        reply_header.data.offset = args.offset;
        reply_data.ptr = (char*)args.offset;
        reply_data.size = args.size;
        reply.insert(&reply_header);
        reply.insert(&reply_data);
        transmitter->write(reply);
    }
}

} /* namespace octopus */
