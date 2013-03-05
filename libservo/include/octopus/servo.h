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

#ifndef SERVO_H_
#define SERVO_H_

#ifdef __AVR__

#include <stdint.h>
#include "octopus/timer.h"
#include <avr/io.h>
#include "octopus/gpio.h"

namespace octopus {

/**
 * @brief Servomotor driver using 1 GPIO of port D.
 */
class Servo {

public:
    /**
     * @brief Type representing a servomotor position.
     *
     * One step of the position corresponds to 1 us of the pulse width sent to
     * the servomotor.
     */
    typedef Timer::time_us_t pos_t;

    /**
     * @brief Constructor.
     *
     * This constructor gives you access to an analog servomotor motor using 1
     * GPIO.
     *
     * @param[in] gpio
     *      GPIO to use
     *
     * @param[in] period
     *      Pulse refresh period.
     */
    Servo(Gpio* gpio,
          Timer::time_us_t period = 20000);

    /**
     * @brief Reaches an absolute position.
     *
     * This asynchronous function activate the generation of the pulse with
     * a pulse width corresponding to @a position.
     *
     * @param position
     *      Absolute position to reach. The zero position corresponds to the
     *      minimum pulse width each step of position corresponds to 1
     *      microsecond of the pulse width.
     */
    void reachPosition(pos_t position);

    /**
     * @brief Releases the servomotor.
     *
     * This function
     */
    void stop();

private:
    bool enabled;
    pos_t position;

    // Timer task to stop the pulse
    class StopPulseTask : public Timer::Task {
    public:
        StopPulseTask(Gpio* gpio);
    private:
        Gpio* gpio;
        void run(Timer::time_us_t when, char what);
    };

    // Timer task to start the pulse
    class StartPulseTask : public Timer::Task {
    public:
        StartPulseTask(Gpio* gpio,
                       Timer::time_us_t period);
        void run(Timer::time_us_t when, char what);
        Timer::time_us_t pulse_width;
    private:
        Gpio* gpio;
        Timer::time_us_t period;
        StopPulseTask stop_task;
    } start_task;
};

} /* namespace octopus */

#endif /* __AVR__ */

#endif /* SERVO_H_ */
