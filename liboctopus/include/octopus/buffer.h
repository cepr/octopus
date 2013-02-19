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

#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

namespace octopus {

/**
 * @brief Buffer descriptor for asynchronous operations.
 *
 * This class describes a buffer used for read or write asyncronous
 * operations. This class does not provide the actual buffer data, it
 * only holds a pointer to it. This class can be used as an element of
 * a List so that you can trigger a list of asynchronous operation
 * in a single call.
 *
 * @see Usart
 */
class Buffer
{
public:
    /**
     * @brief Buffer callback interface.
     *
     * @see #callback
     */
    class Callback {
    public:
        /**
         * @brief Asynchronous read finished callback.
         *
         * Associate a class implementing this method to a buffer
         * and it will get called as soon as an asynchronous read
         * is finished on this buffer. The argument @a buffer
         * holds a pointer to the Buffer which was used for
         * the asynchronous operation.
         *
         * @param buffer  The buffer containing the read data.
         */
        virtual void onReadFinished(Buffer* buffer) {}

        /**
         * @brief Asynchronous write finished callback.
         *
         * Associate a class implementing this method to a buffer
         * and it will get called as soon as an asynchronous write
         * is finished on this buffer. The argument @a buffer
         * holds a pointer to the Buffer which was used for
         * the asynchronous operation.
         *
         * @param buffer  The buffer containing the written data.
         */
        virtual void onWriteFinished(Buffer* buffer) {}
    };

    /**
     * @brief Constructor.
     *
     * @param[in] ptr       Pointer to the buffer data
     * @param[in] capacity  Buffer capacity
     * @param[in] size      Buffer initial size
     * @param[in] callback  Optional callback for asynchronous operations
     */
    Buffer(char *ptr = 0,
           size_t capacity = 0,
           size_t size = 0,
           Callback* callback = 0) :
        ptr(ptr),
        size(size),
        capacity(capacity),
        callback(callback),
        prev(0),
        next(0)
    {
    }

    /**
     * @brief Pointer to the buffer data.
     */
    char* ptr;

    /**
     * @brief Buffer size.
     *
     * The size of the buffer is the number of bytes stored in the buffer.
     */
    size_t size;

    /**
     * @brief Buffer capacity.
     *
     * The capacity of the buffer is the maximum possible @a size of the buffer.
     */
    size_t capacity;

    /**
     * @brief Optional callback for buffer state change.
     *
     * If not zero, this callback will be called at the end of the
     * asynchronous operation using this buffer.
     */
    Callback* callback;

    // For List<Buffer>
    Buffer* prev; // Pointer to the previous buffer
    Buffer* next; // Pointer to the next buffer
};

template <class T>
class TBuffer : public Buffer
{
public:
    TBuffer(Callback* callback = 0) :
        Buffer((char*)&data,
               sizeof(T),
               sizeof(T),
               callback)
    {
    }

    T data;
};

} /* namespace octopus */

#endif // BUFFER_H
