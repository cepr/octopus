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

#ifdef __AVR

#include <avr/io.h>
#include <avr/interrupt.h>
#include "octopus/avr_two_wire_interface.h"
#include "octopus/fatal.h"
#include "octopus/avr_timer.h"

namespace octopus {

AvrTwoWireInterface AvrTwoWireInterface::instance;

//#define DEBUG_I2C

AvrTwoWireInterface::AvrTwoWireInterface()
{
	// set PC4 as SDA and PC5 as SCL, both with pull-up
	DDRC &= ~(_BV(PORTC4) | _BV(PORTC5));   // input
	PORTC |= _BV(PORTC4) | _BV(PORTC5);     // pull-up

#ifndef DEBUG_I2C
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
#else
    // set bit rate to minimum
    TWSR = _BV(TWPS1) | _BV(TWPS0);
    TWBR = 255;
#endif
}

void AvrTwoWireInterface::deactivateFastI2C()
{
#ifndef DEBUG_I2C
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
#endif
}

namespace {
    inline void _start(void) {
        TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
                _BV(TWSTA) | // TWSTA must be written to one to transmit a START condition
                _BV(TWEN) | // TWEN must be set to enable the 2-wire Serial Interface
                _BV(TWIE); // the TWI interrupt request will be activated for as long as the TWINT Flag is high
    }

    inline void _stop(void) {
        TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
                _BV(TWSTO) | // Generate a STOP condition
                _BV(TWEN) | // TWEN must be set to enable the 2-wire Serial Interface
                _BV(TWIE); // the TWI interrupt request will be activated for as long as the TWINT Flag is high
    }

    inline void _nextdata(void) {
        TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
                _BV(TWEN) | // TWEN must be set to enable the 2-wire Serial Interface
                _BV(TWIE); // the TWI interrupt request will be activated for as long as the TWINT Flag is high
    }

    inline void _ack(void) {
        TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
                _BV(TWEA) | // Data byte will be received and ACK will be returned
                _BV(TWEN) | // TWEN must be set to enable the 2-wire Serial Interface
                _BV(TWIE); // the TWI interrupt request will be activated for as long as the TWINT Flag is high)
    }

    inline void _nack(void) {
        TWCR = _BV(TWINT) | // TWINT must be written to one to clear the TWINT Flag
                _BV(TWEN) | // TWEN must be set to enable the 2-wire Serial Interface
                _BV(TWIE); // the TWI interrupt request will be activated for as long as the TWINT Flag is high)
    }

    inline void _deactivate_twi(void) {
        TWCR = _BV(TWINT); // TWINT must be written to one to clear the TWINT Flag
    }
}

void AvrTwoWireInterface::resume()
{
    // Pick the operation to execute
    Operation* op = execution_queue.front();

    // Mark the next operation as running
    op->status = AsyncOperation::STATUS_RUNNING;

    // Update size
    size = op->size;
    op->size = 0;

    // Send START condition
    _start();
}

void AvrTwoWireInterface::onTwiInterrupt() {
	unsigned char status = TWSR & (~(_BV(TWPS0) | _BV(TWPS1)));
    Operation *op = execution_queue.front();

	switch (status) {

	case 0x08:
		// A START condition has been transmitted.
	case 0x10:
		// A repeated START condition has been transmitted.
        TWDR = op->address + (op->type == Operation::TYPE_READ ? 1 : 0);
        _nextdata();
		break;

    case 0x28:
        // Data byte has been transmitted; ACK has been received
        op->size++;
    case 0x18:
		// SLA+W has been transmitted; ACK has been received
        if (op->size < size) {
			// Let's send one more byte
            TWDR = op->ptr[op->size];
			_nextdata();
		} else {
			// No more data to write, send STOP condition
			_stop();
			// Note: no interrupt is generated after a STOP condition, we can notify listener transfert is finished
            op->result = Operation::RESULT_OK;
            AvrAsyncOperation::post();
		}
		break;

	case 0x30:
		// Data byte has been transmitted; NOT ACK has been received
		// The I2C device does not accept any more bytes, send STOP condition
		_stop();
		// Note: no interrupt is generated after a STOP condition, we can notify listener transfert is finished
        op->result = Operation::RESULT_OK;
        AvrAsyncOperation::post();
		break;

	case 0x20:
		// SLA+W has been transmitted; NOT ACK has been received
	case 0x48:
		// SLA+R has been transmitted; NOT ACK has been received
		// send STOP condition
		_stop();
		// Note: no interrupt is generated after a STOP condition, we can notify listener transfert is finished
        op->result = Operation::RESULT_DEVICE_NOT_PRESENT;
        AvrAsyncOperation::post();
		break;

	case 0x38:
		// Arbitration lost
        _deactivate_twi();
        op->result = Operation::RESULT_BUS_BUSY;
        AvrAsyncOperation::post();
		break;

	case 0x50:
		// Data byte has been received, ACK has been returned
	case 0x58:
		// Data byte has been received; NOT ACK has been returned
        op->ptr[op->size++] = TWDR;
		/* no break */
	case 0x40:
		// SLA+R has been transmitted; ACK has been received
        if (op->size < size) {
			// at least one more byte to receive
            if ((size - op->size) > 1) {
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
            op->result = Operation::RESULT_OK;
            AvrAsyncOperation::post();
		}
		break;

    default:
        fatal(FATAL_TWI_UNKNOWN_STATUS);
	}
}

ISR(TWI_vect) {
    AvrTwoWireInterface::instance.onTwiInterrupt();
}

void AvrTwoWireInterface::onFinished() {
    // Current operation is finished, remove it from the list
    Operation* op = execution_queue.front();
    execution_queue.remove(op);

    // And release it
    int index = op - pool_array;
    if ( (index >= 0) && (index < CONFIG_I2C_POOL_SIZE) ) {
        // This operation comes from our pool, we must take it back
        pool.insert(op);
    }

    // Update its status
    op->status = AsyncOperation::STATUS_IDLE;
    if (op->callback) {
        op->callback->onFinished(op);
    }

	// let's continue with the next transfer.
    if (execution_queue.front()) {
        resume();
	}
}

void AvrTwoWireInterface::run(Timer::time_us_t when, char what)
{
    if (PORTC & _BV(PORTC5)) {
        if ((PINC & _BV(PINC4)) == 0) {
            // One device on the bus is pulling SDA low
            // The recommendation is to toggle the SCL line until
            // all devices release the bus.
            PORTC &= ~_BV(PORTC5); // set value to zero
            DDRC |= _BV(DDC5); // set output
            AvrTimer::instance.schedule(this, when + 5);
        } else {
            // Bus is OK, go back to normal mode
            if (!execution_queue.isEmpty()) {
                resume();
            }
        }
    } else {
        DDRC &= ~_BV(DDC5); // set input
        PORTC |= _BV(PORTC5); // set pull-up
        AvrTimer::instance.schedule(this, when + 5);
    }
}

void AvrTwoWireInterface::recover() {
    Lock l;
    // Deactivate the TWI controller
    _deactivate_twi();
    // Program the timer
    AvrTimer::instance.schedule(this, AvrTimer::instance.now());
}

} /* namespace octopus */

#endif /* __AVR */
