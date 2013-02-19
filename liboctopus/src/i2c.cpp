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

#include "octopus/i2c.h"
#include "octopus/lock.h"

namespace octopus {

void I2C::Operation::onFinished()
{
    if (callback) {
        callback->onFinished(this);
    }
}

I2C::I2C()
{
    for (int i = 0; i < CONFIG_I2C_POOL_SIZE; i++) {
        pool.insert(&pool_array[i]);
    }
}

I2C::Operation* I2C::read(uint8_t address,
                          uint8_t *ptr,
                          size_t size,
                          Callback *callback)
{
    // Pick an available operation
    Operation* operation;
    {
        Lock l;
        operation = pool.front();
        if (!operation) {
            // No more available operations
            return 0;
        } else {
            // Remove this operation
            pool.remove(operation);
        }
    }

    // Set operation attributes
    operation->address = address;
    operation->ptr = ptr;
    operation->size = size;
    operation->callback = callback;

    // Post this operation
    read(operation);

    return operation;
}

void I2C::read(Operation* operation)
{
    // Set operation attributes
    operation->type = Operation::TYPE_READ;
    operation->result = Operation::RESULT_NOT_AVAILABLE;
    operation->status = AsyncOperation::STATUS_PENDING;

    // Insert this operation in the execution queue
    {
        Lock l;
        bool should_resume = execution_queue.isEmpty();
        execution_queue.insert(operation);
        // Resume the operations
        if (should_resume) {
            resume();
        }
    }
}

I2C::Operation* I2C::write(uint8_t address,
           const uint8_t* ptr,
           size_t size,
           Callback* callback)
{
    // Pick an available operation
    Operation* operation;
    {
        Lock l;
        operation = pool.front();
        if (!operation) {
            // No more available operations
            return 0;
        } else {
            // Remove this operation
            pool.remove(operation);
        }
    }

    // Set operation attributes
    operation->address = address;
    operation->ptr = (uint8_t*)ptr;
    operation->size = size;
    operation->callback = callback;

    // Post this operation
    write(operation);

    return operation;
}

void I2C::write(Operation* operation)
{
    // Set operation attributes
    operation->type = Operation::TYPE_WRITE;
    operation->result = Operation::RESULT_NOT_AVAILABLE;
    operation->status = AsyncOperation::STATUS_PENDING;

    // Insert this operation in the execution queue
    {
        Lock l;
        bool should_resume = execution_queue.isEmpty();
        execution_queue.insert(operation);
        // Resume the operations
        if (should_resume) {
            resume();
        }
    }
}

void I2C::abort(Operation* operation)
{
    {
        Lock l;

        // We can abort an operation only if it is in pending status
        if (operation->status != AsyncOperation::STATUS_PENDING) {
            return;
        }

        // Remove the operation
        execution_queue.remove(operation);

        // Update operation status
        operation->result = Operation::RESULT_ABORTED;
        operation->status = AsyncOperation::STATUS_IDLE;
    }

    // Call user callback
    if (operation->callback) {
        operation->callback->onFinished(operation);
    }
}

} /* namespace octopus */
