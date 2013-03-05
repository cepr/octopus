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
#include "octopus/avr_timer.h"
#include "octopus/lock.h"

namespace octopus {

Servo::Servo(Gpio* gpio,
             Timer::time_us_t period) :
    enabled(false),
    position(0),
    start_task(gpio, period)
{
    gpio->setDirection(Gpio::OUTPUT);
    gpio->clear();
}

void Servo::reachPosition(pos_t position)
{
    Lock l;
    start_task.pulse_width = position;
    if (!enabled) {
        start_task.run(AvrTimer::instance.now(), 0);
        enabled = true;
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

Servo::StartPulseTask::StartPulseTask(Gpio *gpio,
                                      Timer::time_us_t period) :
    gpio(gpio),
    period(period),
    stop_task(gpio)
{
}

void Servo::StartPulseTask::run(Timer::time_us_t when, char what)
{
    // set GPIO high
    gpio->set();

    // program end of pulse
    AvrTimer::instance.schedule(&stop_task, when + pulse_width);

    // program next pulse
    AvrTimer::instance.schedule(this, when + period);
}

Servo::StopPulseTask::StopPulseTask(Gpio *gpio) :
    gpio(gpio)
{
}

void Servo::StopPulseTask::run(Timer::time_us_t when, char what)
{
    // clear GPIO
    gpio->clear();
}

} /* namespace octopus */

#endif /* __AVR__ */
