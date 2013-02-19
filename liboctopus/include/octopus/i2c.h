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

#ifndef I2C_H
#define I2C_H

#include "octopus/async_operation.h"
#include "octopus/list.h"
#include <stdint.h>
#include <stddef.h>

#ifndef CONFIG_I2C_POOL_SIZE
# define CONFIG_I2C_POOL_SIZE 8
#endif

namespace octopus {

/**
 * @brief Abstract base class for all I2C bus drivers.
 */
class I2C
{
public:
    // Early definition
    class Callback;

    /**
     * @brief I2C asynchronous operation description
     */
    class Operation: public AsyncOperation
    {
    public:
        /**
         * @brief I2C operation type.
         */
        typedef enum {
            TYPE_READ, ///< Read operation
            TYPE_WRITE ///< Write operation
        } Type;

        /**
         * @brief I2C operation result.
         */
        typedef enum {
            RESULT_NOT_AVAILABLE, ///< The operation is not finished
            RESULT_OK, ///< The operation terminated successfuly
            RESULT_ABORTED, ///< The abort method has been called
            RESULT_DEVICE_NOT_PRESENT, ///< The device did not respond to its address
            RESULT_DEVICE_NACK, ///< The device sent a NACK
            RESULT_BUS_ERROR, ///< I2C bus error
            RESULT_BUS_BUSY ///< I2C bus busy
        } Result;

        /**
         * @brief Operation type
         */
        Type type;

        /**
         * @brief I2C device address
         */
        uint8_t address;

        /**
         * @brief Pointer to data to read or write
         */
        uint8_t* ptr;

        /**
         * @brief Number of bytes to read or write
         */
        size_t size;

        /**
         * @brief Operation result
         *
         * This field should be only used in Callback::onFinished().
         */
        Result result;

        /**
         * @brief callback
         */
        Callback* callback;

    private:
        virtual void onFinished();
    };

    /**
     * @brief Callback for end of I2C asynchronous operation.
     */
    class Callback
    {
    public:
        virtual void onFinished(Operation* operation) = 0;
    };

    /**
     * @brief Deactivate fast I2C mode
     *
     * This method deactivate the 400kHz fast I2C mode and switch to normal 100 kHz mode.
     */
    virtual void deactivateFastI2C() = 0;

    /**
     * @brief Performs an asynchronous read.
     *
     * This method programs a new asynchronous read.
     *
     * @param address   I2C device address
     * @param ptr       Where to save the read data
     * @param size      Number of bytes to read
     * @param callback  End of operation callback
     *
     * @return This function returns the Operation instance that has been created for
     *         this operation if successful, @a 0 otherwise. You may use this instance
     *         to abort the operation.
     */
    Operation* read(uint8_t address,
              uint8_t* ptr,
              size_t size,
              Callback* callback);

    /**
     * @brief Performs an asynchronous read.
     *
     * This method programs a new asynchronous read.
     *
     * @param operation  AsyncRead instance describing the read parameters.
     */
    void read(Operation* operation);

    /**
     * @brief Performs an asynchronous write.
     *
     * @param address   I2C device address
     * @param ptr       Pointer to the data to write
     * @param size      Number of bytes to write
     * @param callback  End of operation callback
     *
     * @return
     *  This function returns the Operation instance that will be used
     *  for the asynchronous write. You can use this operation pointer with
     *  abort() to abort the operation.
     */
    Operation* write(uint8_t address,
               const uint8_t* ptr,
               size_t size,
               Callback* callback);

    /**
     * @brief Performs an asynchronous write.
     *
     * @param operation  AsyncWrite instance describing the write parameters.
     */
    void write(Operation* operation);

    /**
     * @brief Abort a pending operation.
     *
     * Call this method to abort an asynchronous I2C operation. The user callback will
     * be called with @a Operation::result equal to RESULT_ABORTED.
     *
     * @param operation  I2C operation to abort.
     */
    void abort(Operation* operation);

protected:
    // Constructor.
    I2C();

    // Virtual resume operations
    // The I2C controller drivers must implement this method
    virtual void resume() = 0;

    // Queue of pending operations
    List<Operation> execution_queue;

    // Pool of available operations
    Operation pool_array[CONFIG_I2C_POOL_SIZE];
    List<Operation> pool;
};

} /* namespace octopus */

#endif // I2C_H
