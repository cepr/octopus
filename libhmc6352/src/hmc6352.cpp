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

#include "octopus/hmc6352.h"
#include "octopus/fatal.h"
#include "octopus/avr_timer.h"

namespace octopus {

Hmc6352::Hmc6352(I2C* i2c) : i2c(i2c)
{
    // HMC6352 does not support 400 kHz mode
    i2c->deactivateFastI2C();
}

void Hmc6352::getHeading(CompassListener* listener)
{
    if (listener) {
        this->listener = listener;
        static const uint8_t CMD[] = {'A'};
        i2c->write(I2C_ADDRESS, CMD, sizeof(CMD), this);
    }
}

void Hmc6352::onFinished(I2C::Operation* op)
{
    if (op->result != I2C::Operation::RESULT_OK) {
        listener->onCompassError((char)op->result);
        return;
    }

    if (op->type == I2C::Operation::TYPE_WRITE) {
        if (op->size == 1) {
            // The 'A' command has been sent
            AvrTimer::instance.schedule(this,
                                        AvrTimer::instance.now() + 6000);
        } else {
            // The compass rejected our command with a NACK
            listener->onCompassError(10);
        }
    } else {
        if (op->size == 2) {
            // We just have received the heading value
            uint16_t heading;
            ((uint8_t*)&heading)[0] = buffer[1];
            ((uint8_t*)&heading)[1] = buffer[0];
            listener->onNewHeading(heading);
        } else {
            // The compass sent a NACK during the reading
            listener->onCompassError(11);
        }
    }
}

void Hmc6352::run(Timer::time_us_t when, char what)
{
    i2c->read(I2C_ADDRESS, buffer, sizeof(buffer), this);
}

} /* namespace octopus */

#endif /* __AVR */
