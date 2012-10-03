/*
 * Copyright 2010-2011 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * \file i2c_driver.h
 * \brief Header file for \ref I2CDriver interface
 */

#ifndef I2CDRIVER_H_
#define I2CDRIVER_H_

#include "i2c_device.h"

/**
 * \brief I2C transfert type
 */
typedef enum {
    I2C_TRANSMIT,   /**< I2C Master Transmitter Mode */
    I2C_RECEIVE     /**< I2C Master Receiver Mode */
} I2CTransferType;

/**
 * \brief Linked-list of I2C transfers
 *
 * This structure defines a linked list of I2C transfers.
 * In order to perform one or more I2C transfers, you should construct a list of this type and pass it to I2CDriver::commit().
 */
typedef struct _I2CTransfer {
    I2CDevice* device;          /**< I2C slave device */
    I2CTransferType type;       /**< Transmit or receive */
    unsigned char* buffer;      /**< Pointer to the data to transmit or receive */
    unsigned char size;         /**< Number of bytes to transmit or receive */
    struct _I2CTransfer* next;  /**< Pointer to the next transfer, or 0 if only one transfert */
} I2CTransfer;

/**
 * \brief I2C driver interface
 *
 * All I2C drivers are inherited from this class.
 *
 * \ingroup INTERFACES
 */
class I2CDriver {

public:
    /**
     * \brief Appends one or more I2C transfers to the list of waiting I2C transfers
     *
     * \param[in] transfer The first element of a list of transfer commands.
     */
    virtual void commit(I2CTransfer *transfer) = 0;

    /**
     * \brief Removes all tranfers from/to a specified I2C devices
     *
     * \param[in] device The I2C device to remove.
     */
    virtual void removeDevice(I2CDevice *device) = 0;
};

#endif /* I2CDRIVER_H_ */
