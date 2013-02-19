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

#ifndef BLINK_H_
#define BLINK_H_

#include "octopus/timer.h"
#include "octopus/looper.h"

namespace octopus {

/**
 * @brief Blinking LED.
 *
 * Use this class to make the Arduino onboard LED
 * (GPIO B5 of ATMEGA328) blink at a 2 seconds period.
 */
class Blink: private Timer::Task {

public:
    /**
     * @brief Constructor.
     *
     * You need to call enable() to activate the LED blinking.
     *
     * You can specify a Looper on which the blinking timer task will run. This may be
     * useful to check that the Looper is not frozen.
     *
     * @param[in] looper
     *      Looper to use for blinking, or zero to toggle the LED from interrupt context.
     */
    Blink(Looper* looper = 0);

    /**
     * @brief Enable or disable the LED blinking.
     *
     * @param enable
     *      @a true to enable blinking, @a false otherwise.
     */
    void enable(bool enable = true);

private:
    // is blinking enabled or not
    Looper* looper;
    bool enabled;

    // timer handler
    void run(Timer::time_us_t when, char what);
};

} /* namespace octopus */

#endif /* BLINK_H_ */
