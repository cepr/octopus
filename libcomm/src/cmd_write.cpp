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

#include "write.h"
#include <string.h>

namespace octopus {

CommandWrite::CommandWrite(MessageTransmitter *transmitter) :
    Handler(CMD_WRITE),
    transmitter(transmitter)
{
    reply_header.data = CMD_WRITE;
}

void CommandWrite::onMessage(const Buffer &message)
{
    if (message.size == sizeof(struct Request)) {
        const struct Request & args = *(const struct Request*)message.ptr;

        // Write into memory
        memcpy((void*)args.offset,
               message.ptr + sizeof(struct Request),
               message.size - sizeof(struct Request));

        // Write reply
        MessageTransmitter::Message reply;
        reply.insert(&reply_header);
        transmitter->write(reply);
    }
}

} /* namespace octopus */
