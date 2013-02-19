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

#include "message_transmitter.h"

namespace octopus {

MessageTransmitter::MessageTransmitter(Usart* usart) :
    packet(usart, this)
{
}

void MessageTransmitter::write(Message &message)
{
    if (packet.getState() == Packet::STATE_IDLE) {
        // packet is idle, we can send the message right now
        packet.write(message);
    } else {
        // packet is busy, we save this message for later
        queue.insert(&message);
    }
}

void MessageTransmitter::onWritePacketComplete()
{
    Message *message = queue.front();
    if (message) {
        queue.remove(message);
        packet.write(*message);
    }
}

} /* namespace octopus */
