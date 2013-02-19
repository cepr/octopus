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

#include "octopus/buffer_pool.h"
#include "octopus/lock.h"

namespace octopus {

namespace
{
    class BufferReleaseCallback: public Buffer::Callback {
        void onReadFinished(Buffer *buffer)
        {
            BufferPool::instance.release(buffer);
        }
        void onWriteFinished(Buffer *buffer)
        {
            BufferPool::instance.release(buffer);
        }
    } buffer_release_callback;
}

BufferPool::BufferPool()
{
    for (int i=0; i<POOL_BUFFER_COUNT; i++) {
        available.insert(&buffers[i]);
    }
}

Buffer* BufferPool::acquire()
{
    Lock l;
    Buffer* buf = available.front();
    if (buf) {
        buf->ptr = data[buf - buffers];
        buf->size = POOL_BUFFER_SIZE;
        buf->callback = &buffer_release_callback;
        available.remove(buf);
    }
    return buf;
}

void BufferPool::release(Buffer *buf)
{
    available.insert(buf);
}

} /* namespace octopus */
