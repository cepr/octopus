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

#ifndef BUFFER_POOL_H
#define BUFFER_POOL_H

#include "octopus/list.h"
#include "octopus/buffer.h"

#define POOL_BUFFER_SIZE 32
#define POOL_BUFFER_COUNT 4

namespace octopus {

/**
 * @brief Buffer pool
 *
 * This singleton class is holding a pool of @a Buffer. Anytime you need a buffer
 * to read or write data on a serial port, you can use this class to obtain one by
 * calling #acquire(). Once you do not need that buffer anymore, you should call
 * release() in order to make the buffer available again.
 */
class BufferPool
{
public:
    /**
     * @brief instance
     */
    static BufferPool instance;

    /**
     * @brief Acquires a buffer
     *
     * Call this function to get a new buffer. This size of the buffer will be
     * set to its maximum size. You can shrink it as much as you need, and even
     * modify its starting address.
     *
     * You must call release() when you do not need the buffer anymore.
     *
     * @return A buffer
     *
     * @see release()
     */
    Buffer* acquire();

    /**
     * @brief Releases a buffer
     *
     * Call this function to release a buffer previously obtained with acquire().
     *
     * @param buf A buffer previously obtained with acquire()
     *
     * @see acquire()
     */
    void release(Buffer* buf);

private:
    // Private constructor
    BufferPool();

    // List of available buffers
    List<Buffer> available;

    // Buffer descriptors
    Buffer buffers[POOL_BUFFER_COUNT];

    // Pool
    char data[POOL_BUFFER_COUNT][POOL_BUFFER_SIZE];
};

} /* namespace octopus */

#endif // BUFFER_POOL_H
