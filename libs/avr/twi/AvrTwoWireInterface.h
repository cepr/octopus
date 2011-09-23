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

/**
 * \file AvrTwoWireInterface.h
 * \brief Header file for \ref AvrTwoWireInterface class
 */

#ifndef AVRTWOWIREINTERFACE_H_
#define AVRTWOWIREINTERFACE_H_

#include "i2c_driver.h"
#include "Handler.h"
#include "i2c_device.h"

/**
 * \brief Accessing I2C bus of AVR microcontrollers.
 *
 * This class gives access to the I2C bus of AVR microcontrollers.
 *
 * \ingroup AVR_TWI
 */
class AvrTwoWireInterface: public I2CDriver, private Handler {

public:
    /**
     * \brief Returns the unique instance of \ref AvrTwoWireInterface
     *
     * \return The \ref AvrTwoWireInterface class
     */
    static inline AvrTwoWireInterface & getInstance() {
        return mInstance;
    }

    /*
     * I2CDriver::commit()
     */
    void commit(I2CTransfer *transfer);

    /*
     * I2CDriver::removeDevice()
     */
    void removeDevice(I2CDevice *device);

private:

    /**
     * \brief Private constructor
     *
     * \ref AvrTwoWireInterface is a singleton, use getInstance() to
     * get the reference to the \ref AvrTwoWireInterface object.
     */
    AvrTwoWireInterface();
    static AvrTwoWireInterface mInstance;

    /**
     * \brief TWI State machine entry point
     *
     * Called by the TWI interrupt vector in IRQ context.
     */
    friend void onTwiInterrupt(void);

    /**
     * \brief Initializes state machine variables.
     */
    void StartTransfer(void);

    /**
     * \brief High-level interrupt service routine
     *
     * \param[in] what Type of event, see \ref I2C_EVENTS.
     */
    void onEvent(char what);

    /**
     * \internal
     * \ingroup AVR_TWI
     * \defgroup I2C_EVENTS AVR AvrTwoWireInterface events
     * Events sent from onInterrupt() to onEvent().
     * \{
     */
    static const char EVENT_TRANSMIT_COMPLETE = 0;      /**< Transmit finished successfuly. */
    static const char EVENT_RECEIVE_COMPLETE = 1;       /**< Receive finished successfuly. */
    static const char EVENT_DEVICE_NOT_RESPONDING = 2;  /**< Device did not respond to a transmit or receive. */
    static const char EVENT_ARBITRATION_LOST = 3;       /**< I2C bus arbitration lost. */
    static const char EVENT_DEVICE_NACK = 4;            /**< The I2C device sent a NOT ACK. */
    /**
     * \}
     */

    I2CTransfer* mCurrentTransfer;
    I2CTransfer* mLastTransfer;
    unsigned char mSlaveAddress;
    unsigned char *mDataPtr;
    unsigned char mRemaining;
    unsigned char mTransmited;
};

#endif /* AVRTWOWIREINTERFACE_H_ */
