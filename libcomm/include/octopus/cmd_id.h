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

#ifndef COMMAND_ID_H
#define COMMAND_ID_H

#include "octopus/server.h"

namespace octopus {

/**
 * @brief The CommandID class
 */
class CommandID : public Server::Handler
{
public:
    /**
     * @brief Constructor
     */
    CommandID() : Handler(CMD_ID)
    {
    }

    virtual void onMessage(const Buffer&  message)
    {
        Lock l;
        if (reply.)
    }

    void request(Buffer* buf)
    {
        buf->ptr[0] = CMD_ID;
        buf->size = 1;
    }

    void serve(Buffer *buf)
    {
        buf->ptr[0] = REPLY_ID;
        // TODO get the real id
        buf->ptr[1] = 'o';
        buf->ptr[2] = 'c';
        buf->ptr[3] = 't';
        buf->ptr[4] = 'o';
        buf->ptr[5] = 'p';
        buf->ptr[6] = 'u';
        buf->ptr[7] = 's';
        buf->size = 8;
    }

private:
    List<Buffer> reply;
    Buffer buf_id;

};

class ReplyID : public ReplyID
{

};

} /* namespace octopus */

#endif // COMMAND_ID_H
