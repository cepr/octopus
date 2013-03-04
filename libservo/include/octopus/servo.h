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
     * the servomotor. The zero position corresponds to the servomotor
     * position when sending the minimum pulse width. The pulse width is
     * computed as a modulo in order to support continuous rotation
     * servomotors.
     */
    typedef int16_t pos_t;

    /**
     * @brief Constructor.
     *
     * This constructor gives you access to an analog servomotor motor using 1
     * GPIO.
     *
     * @param[in] port
     *      Port to use:
     *      @arg @c &PORTB
     *      @arg @c &PORTC
     *      @arg @c &PORTD
     *
     * @param[in] pin
     *      GPIO number to use on which the servomotor is plugged.
     *
     * @param[in] min_pulse_width
     *      Minimum pulse width.
     *
     * @param[in] max_pulse_wdith
     *      Maximum pulse width.
     *
     * @param[in] period
     *      Pulse refresh period.
     */
    Servo(volatile uint8_t *port,
          uint8_t pin,
          Timer::time_us_t min_pulse_width,
          Timer::time_us_t max_pulse_width,
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
    Timer::time_us_t min_pulse_width;
    Timer::time_us_t max_pulse_width;
    bool enabled;
    pos_t position;

    // Timer task to stop the pulse
    class StopPulseTask : public Timer::Task {
    public:
        StopPulseTask(volatile uint8_t *port,
                      uint8_t pin);
    private:
        volatile uint8_t *port;
        uint8_t npin;
        void run(Timer::time_us_t when, char what);
    };

    // Timer task to start the pulse
    class StartPulseTask : public Timer::Task {
    public:
        StartPulseTask(volatile uint8_t *port,
                       uint8_t pin,
                       Timer::time_us_t period);
        void run(Timer::time_us_t when, char what);
        Timer::time_us_t pulse_width;
    private:
        volatile uint8_t *port;
        uint8_t pin;
        Timer::time_us_t period;
        StopPulseTask stop_task;
    } start_task;
};

} /* namespace octopus */

#endif /* __AVR__ */

#endif /* SERVO_H_ */
