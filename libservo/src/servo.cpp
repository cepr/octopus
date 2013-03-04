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

#ifdef __AVR__

#include <avr/io.h>
#include "octopus/servo.h"
#include "octopus/fatal.h"
#include "octopus/avr_timer.h"
#include "octopus/lock.h"

namespace octopus {

Servo::Servo(volatile uint8_t *port,
             uint8_t pin,
             Timer::time_us_t min_pulse_width,
             Timer::time_us_t max_pulse_width,
             Timer::time_us_t period) :
    min_pulse_width(min_pulse_width),
    max_pulse_width(max_pulse_width),
    enabled(false),
    position(0),
    start_task(port, _BV(pin), period)
{
    if (port == &PORTB) {
        PORTB &= ~_BV(pin);
        DDRB |= _BV(pin);
    } else if (port == &PORTC) {
        PORTC &= ~_BV(pin);
        DDRC |= _BV(pin);
    } else if (port == &PORTD) {
        PORTD &= ~_BV(pin);
        DDRD |= _BV(pin);
    } else {
        fatal(FATAL_INVALID_PARAMETER);
    }
}

void Servo::reachPosition(pos_t position)
{
    // Compute the pulse width before masquing interrupts since a modulo can be quite long.
    Timer::time_us_t i = (position % (max_pulse_width - min_pulse_width)) + min_pulse_width;
    {
        // Mask interrupts and apply new pulse width.
        Lock l;
        start_task.pulse_width = i;
        if (!enabled) {
            start_task.run(AvrTimer::instance.now(), 0);
            enabled = true;
        }
    }
}

void Servo::stop()
{
    Lock l;
    if (enabled) {
        AvrTimer::instance.cancel(&start_task);
        enabled = false;
    }
}

Servo::StartPulseTask::StartPulseTask(volatile uint8_t *port,
                                      uint8_t pin,
                                      Timer::time_us_t period) :
    port(port),
    pin(pin),
    period(period),
    stop_task(port, pin)
{
}

void Servo::StartPulseTask::run(Timer::time_us_t when, char what)
{
    // set GPIO high
    _MMIO_BYTE(port) |= pin;

    // program end of pulse
    AvrTimer::instance.schedule(&stop_task, when + pulse_width);

    // program next pulse
    AvrTimer::instance.schedule(this, when + period);
}

Servo::StopPulseTask::StopPulseTask(volatile uint8_t *port,
                                    uint8_t pin) :
    port(port),
    npin(~pin)
{
}

void Servo::StopPulseTask::run(Timer::time_us_t when, char what)
{
    // clear GPIO
    _MMIO_BYTE(port) &= npin;
}

} /* namespace octopus */

#endif /* __AVR__ */
