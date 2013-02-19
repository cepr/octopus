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

#include "packet.h"
#include "octopus/util/lock.h"
#include "octopus/util/fatal.h"

namespace octopus {

Packet::Packet(Usart* usart, Callback* callback) :
    usart(usart),
    callback(callback),
    header('$'),
    size(0),
    checksum(0),
    bheader(&header, sizeof(header), sizeof(header), this),
    bsize((char*)&size, sizeof(size), sizeof(size), this),
    bmessage(0),
    bchecksum(&checksum, sizeof(checksum), sizeof(checksum), this),
    state(STATE_IDLE)
{
}

void Packet::read(Buffer* message)
{
    if (state != STATE_IDLE) {
        fatal(FATAL_PACKET_IN_USE);
    }
    state = STATE_READING;
    bmessage = message;
    usart->read(&bheader);
}

void Packet::write(List<Buffer> & message)
{
    if (state != STATE_IDLE) {
        fatal(FATAL_PACKET_IN_USE);
    }
    state = STATE_WRITING;

    // Compute size and checksum
    size = computeSize(message);
    checksum = computeChecksum(message);

    // Construct packet
    List<Buffer> list;
    list.insert(&bheader);
    list.insert(&bsize);
    list.insert(&message);
    list.insert(&bchecksum);

    // Send packet
    usart->write(&list);
}

Packet::State Packet::getState()
{
    return state;
}

size_t Packet::computeSize(const List<Buffer> &message)
{
    size_t size = 0;
    List<Buffer>::Iterator it;
    for (it = message.begin(); it.is_valid(); ++it) {
        size += (*it)->size;
    }
    return size;
}

char Packet::computeChecksum(const Buffer &message)
{
    char checksum = 0;
    for (size_t i = 0; i < message.size; i++) {
        checksum += message.ptr[i];
    }
    return checksum;
}

char Packet::computeChecksum(const List<Buffer> &message)
{
    char checksum = 0;
    List<Buffer>::Iterator it;
    for (it = message.begin(); it.is_valid(); ++it) {
        checksum += computeChecksum(**it);
    }
    return checksum;
}

void Packet::onReadFinished(Buffer* buffer)
{
    if (buffer == &bheader) {

        if (header == '$') {
            // Header has been read
            usart->read(&bsize);
        }

    } else if (buffer == &bsize) {

        // Message size has been read
        if (size <= bmessage->capacity) {
            bmessage->size = size;
            if (size) {
                usart->read(bmessage);
            }
            usart->read(&bchecksum);
        } else {
            // Message is too long, wait for next packet
            usart->read(&bheader);
        }

    } else if (buffer == &bchecksum) {

        // Continue execution in application context
        post();

    }
}

void Packet::onWriteFinished(Buffer *buffer)
{
    if (buffer == &bchecksum) {
        // Continue execution in application context
        post();
    }
}

void Packet::onFinished()
{
    State s = state;
    state = STATE_IDLE;
    if (callback) {
        if (s == STATE_READING) {
            // Read finished, we have to verify the checksum
            char sum = computeChecksum(*bmessage);
            if (sum == checksum) {
                callback->onReadPacketComplete();
            }
        } else {
            // Write finished
            callback->onWritePacketComplete();
        }
    }
}

} /* namespace octopus */
