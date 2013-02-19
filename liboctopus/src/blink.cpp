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
#include "octopus/blink.h"
#include "octopus/lock.h"
#include "octopus/avr_timer.h"

namespace octopus {

Blink::Blink(Looper* looper) :
    Task(looper),
    enabled(false)
{
    DDRB |= _BV(DDB5);
}

void Blink::enable(bool enable)
{
    if (enabled != enable) {
        Lock l;
        enabled = enable;
        if (enable) {
            AvrTimer::instance.schedule(this, AvrTimer::instance.now() + 1000000);
        } else {
            AvrTimer::instance.cancel(this);
            PORTB &= ~_BV(PORTB5);
        }
    }
}

void Blink::run(Timer::time_us_t when, char what)
{
    AvrTimer::instance.schedule(this, when + 1e6L);
    PORTB ^= _BV(PORTB5);
}

} /* namespace octopus */

#endif /* __AVR__ */
