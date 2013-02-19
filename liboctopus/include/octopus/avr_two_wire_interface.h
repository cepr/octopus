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

#ifndef AVRTWOWIREINTERFACE_H_
#define AVRTWOWIREINTERFACE_H_

#include "i2c.h"
#include "octopus/timer.h"

namespace octopus {

class AvrAsyncOperation: public AsyncOperation {};

class AvrTwoWireInterface:
        public I2C,
        private AvrAsyncOperation,
        private Timer::Task {

public:
    static AvrTwoWireInterface instance;
    void onTwiInterrupt();

private:
    size_t size;

    // Constructor
    AvrTwoWireInterface();

    // From I2C
    void deactivateFastI2C();
    void resume();

    // From AsyncOperation
    void onFinished();

    // From Timer::Task
    void run(Timer::time_us_t when, char what);

    // To recover a frozen I2C bus (TODO unused)
    void recover();
};

} /* namespace octopus */

#endif /* AVRTWOWIREINTERFACE_H_ */
