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

#include "message_receiver.h"

namespace octopus {

MessageReceiver::MessageReceiver(Usart* usart) :
    packet(usart, this),
    message(buffer, sizeof(buffer))
{
    packet.read(&message);
}

void MessageReceiver::registerHandler(Handler* handler)
{
    handlers.insert(handler);
}

// Called when a complete message has been received
void MessageReceiver::onReadPacketComplete()
{
    // A packet has been read, execute it
    char id = message.ptr[0];

    List<Handler>::Iterator it;
    for (it = handlers.begin(); it.is_valid(); ++it) {
        if (id == (*it)->getID()) {
            // Command found, execute it
            (*it)->onMessage(message);
            break;
        }
    }

    packet.read(&message);
}

} /* namespace octopus */
