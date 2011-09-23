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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "AvrTwoWireInterface.h"
#include "Looper.h"
#include "fatal.h"

AvrTwoWireInterface AvrTwoWireInterface::mInstance;

AvrTwoWireInterface::AvrTwoWireInterface() {
    // set PC4 as SDA and PC5 as SCL, both with pull-up
    DDRC &= ~(_BV(PORTC4) | _BV(PORTC5));   // input
    PORTC |= _BV(PORTC4) | _BV(PORTC5);     // pull-up

#ifdef FAST_I2C
    // set bit rate to 400kHz
# if (F_CPU == 8000000L)
    TWSR = 0;
    TWBR = 2;
# elif (F_CPU == 16000000L)
    TWSR = 0;
    TWBR = 12;
# else /* F_CPU */
#  error Unknown CPU frequency
# endif /* F_CPU */
#else /* FAST_I2C */
    // set bit rate to 100kHz
# if (F_CPU == 8000000L)
    TWSR = 0;
    TWBR = 32;
# elif (F_CPU == 16000000L)
    TWSR = 0;
    TWBR = 72;
# else /* F_CPU */
#  error Unknown CPU frequency
# endif /* F_CPU */
#endif /* FAST_I2C */

}

static inline void _start(void) {
    TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
           _BV(TWSTA) | // TWSTA must be written to one to transmit a START condition
           _BV(TWEN)  | // TWEN must be set to enable the 2-wire Serial Interface
           _BV(TWIE);   // the TWI interrupt request will be activated for as long as the TWINT Flag is high
}

static inline void _stop(void) {
    TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
           _BV(TWSTO) | // Generate a STOP condition
           _BV(TWEN)  | // TWEN must be set to enable the 2-wire Serial Interface
           _BV(TWIE);   // the TWI interrupt request will be activated for as long as the TWINT Flag is high
}

static inline void _nextdata(void) {
    TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
           _BV(TWEN)  | // TWEN must be set to enable the 2-wire Serial Interface
           _BV(TWIE);   // the TWI interrupt request will be activated for as long as the TWINT Flag is high
}

static inline void _ack(void) {
    TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
           _BV(TWEA)  | // Data byte will be received and ACK will be returned
           _BV(TWEN)  | // TWEN must be set to enable the 2-wire Serial Interface
           _BV(TWIE);   // the TWI interrupt request will be activated for as long as the TWINT Flag is high)
}

static inline void _nack(void) {
    TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
           _BV(TWEN)  | // TWEN must be set to enable the 2-wire Serial Interface
           _BV(TWIE);   // the TWI interrupt request will be activated for as long as the TWINT Flag is high)
}

void AvrTwoWireInterface::commit(I2CTransfer *transfer) {
    if (!mCurrentTransfer) {
        // No running I2C transfer, register this new one and start the TWI state machine.
        mLastTransfer = mCurrentTransfer = transfer;
        StartTransfer();
    } else {
        // Already one or more pending transfers, append the new transfer to the tail of the list.
        mLastTransfer = mLastTransfer->next = transfer;
    }
}

void AvrTwoWireInterface::removeDevice(I2CDevice* device)
{
    I2CTransfer *previous = 0;
    for (I2CTransfer* t = mCurrentTransfer; t != 0; t = t->next) {
        if (t->device == device) {
            // We must remove this device
            if (previous) {
                previous->next = t->next;
            } else {
                mCurrentTransfer = t->next;
            }
        }
    }
}

void AvrTwoWireInterface::StartTransfer(void)
{
    if (mCurrentTransfer->type == I2C_TRANSMIT) {
        mSlaveAddress = mCurrentTransfer->device->getAddress() & ~1;
    } else {
        mSlaveAddress = mCurrentTransfer->device->getAddress() | 1;
    }
    mDataPtr = mCurrentTransfer->buffer;
    mRemaining = mCurrentTransfer->size;
    mTransmited = 0;
    _start();
}

inline void onTwiInterrupt(void)
{
    unsigned char status = TWSR & (~(_BV(TWPS0) | _BV(TWPS1)));

    switch(status) {

        case 0x08:
            // A START condition has been transmitted.
        case 0x10:
            // A repeated START condition has been transmitted.
            TWDR = AvrTwoWireInterface::mInstance.mSlaveAddress;   // Send SLA+R or SLA+W
            _nextdata();
            break;

        case 0x18:
            // SLA+W has been transmitted; ACK has been received
        case 0x28:
            // Data byte has been transmitted; ACK has been received
            if (AvrTwoWireInterface::mInstance.mRemaining) {
                // Let's send one more byte
                TWDR = *AvrTwoWireInterface::mInstance.mDataPtr++;
                AvrTwoWireInterface::mInstance.mTransmited++;
                AvrTwoWireInterface::mInstance.mRemaining--;
                _nextdata();
            } else {
                // No more data to write, send STOP condition
                _stop();
                // Note: no interrupt is generated after a STOP condition, we can notify listener transfert is finished
                PostEvent(&AvrTwoWireInterface::mInstance, AvrTwoWireInterface::EVENT_TRANSMIT_COMPLETE);
            }
            break;

        case 0x30:
            // Data byte has been transmitted; NOT ACK has been received
            // The I2C device does not accept any more bytes, send STOP condition
            _stop();
            // Note: no interrupt is generated after a STOP condition, we can notify listener transfert is finished
            PostEvent(&AvrTwoWireInterface::mInstance, AvrTwoWireInterface::EVENT_TRANSMIT_COMPLETE);
            break;

        case 0x20:
            // SLA+W has been transmitted; NOT ACK has been received
        case 0x48:
            // SLA+R has been transmitted; NOT ACK has been received
            // send STOP condition
            _stop();
            // Note: no interrupt is generated after a STOP condition, we can notify listener transfert is finished
            PostEvent(&AvrTwoWireInterface::mInstance, AvrTwoWireInterface::EVENT_DEVICE_NACK);
            break;

        case 0x38:
            // Arbitration lost
            TWCR = _BV(TWINT); // TWINT must be written to one to clear the TWINT Flag
            PostEvent(&AvrTwoWireInterface::mInstance, AvrTwoWireInterface::EVENT_ARBITRATION_LOST);
            break;

        case 0x50:
            // Data byte has been received, ACK has been returned
        case 0x58:
            // Data byte has been received; NOT ACK has been returned
            *AvrTwoWireInterface::mInstance.mDataPtr++ = TWDR;
            AvrTwoWireInterface::mInstance.mTransmited++;
            AvrTwoWireInterface::mInstance.mRemaining--;
            /* no break */
        case 0x40:
            // SLA+R has been transmitted; ACK has been received
            if (AvrTwoWireInterface::mInstance.mRemaining > 0) {
                // at least one more byte to receive
                if (AvrTwoWireInterface::mInstance.mRemaining > 1) {
                    // The byte we are going to receive is not the last one, prepare an ACK
                    _ack();
                } else {
                    // we are going to receive the last byte, prepare an NACK
                    _nack();
                }
            } else {
                // I2C Master (AVR) has sent a NACK to indicate it was the last byte to receive,
                // we just sent a STOP and notify reception is over.
                _stop();
                PostEvent(&AvrTwoWireInterface::mInstance, AvrTwoWireInterface::EVENT_RECEIVE_COMPLETE);
            }
            break;
    }
}

ISR(TWI_vect) {
    onTwiInterrupt();
}

void AvrTwoWireInterface::onEvent(char what) {

    // Current transfer has completed, remove it from the list
    I2CDevice* device_to_notify = mCurrentTransfer->device;
    mCurrentTransfer = mCurrentTransfer->next;

    // notify user
    switch(what) {
        case EVENT_RECEIVE_COMPLETE:
            device_to_notify->onReceiveFinished(mTransmited);
            break;
        case EVENT_TRANSMIT_COMPLETE:
            device_to_notify->onTransmitFinished(mTransmited);
            break;
        case EVENT_DEVICE_NACK:
            removeDevice(device_to_notify);
            device_to_notify->onDeviceNack();
            break;
        case EVENT_DEVICE_NOT_RESPONDING:
            removeDevice(device_to_notify);
            device_to_notify->onDeviceNotResponding();
            break;
        case EVENT_ARBITRATION_LOST:
            removeDevice(device_to_notify);
            device_to_notify->onBusError();
            break;
    }

    // let's continue with the next transfer.
    if (mCurrentTransfer) {
        StartTransfer();
    }
}
