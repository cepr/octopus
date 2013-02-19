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

#ifndef HMC6352_H
#define HMC6352_H

#ifdef __AVR__

#include "octopus/compass_provider.h" // Base class: CompassProvider
#include "octopus/i2c.h"
#include "octopus/timer.h"

namespace octopus {

/**
 * \defgroup HMC6352 Honeywell HMC6252 Digital Compass
 * \ingroup SENSORS_LIBS
 * \{
 */

/**
 * \brief CompassProvider implementation for Honeywell HMC6352 digital compass.
 *
 * This chip is an I2C digital compass.
 */
class Hmc6352 : public CompassProvider,
        private I2C::Callback,
        private Timer::Task {

public:

    /**
     * \brief Constructor
     */
    Hmc6352(I2C* i2c);

    /*
     * see CompassProvider::getHeading()
     */
    void getHeading(CompassListener* listener);

private:
    // From Timer::Task
    void run(Timer::time_us_t when, char what);

    // I2C::Operation::Callback
    void onFinished(I2C::Operation* operation);

    static const uint8_t I2C_ADDRESS = 0x42;
    I2C* i2c;
    uint8_t buffer[2];
    CompassListener *listener;
};

/**
 * \}
 */

} /* namespace octopus */

#endif /* __AVR__ */

#endif // HMC6352_H
