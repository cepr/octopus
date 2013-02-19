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

#include "octopus/avr_timer.h"
#include "octopus/fatal.h"

namespace octopus {

AvrTimer AvrTimer::instance;

AvrTimer::AvrTimer() :
    offset(0)
{
    TCCR1A = 0; // Normal port operation
    TCCR1B = _BV(CS11); // clkIO / 8 (From prescaler)
    TIMSK1 = _BV(TOIE2); // activate overflow interrupt to count 'offset'
}

AvrTimer::time_us_t AvrTimer::now()
{
    return offset + TCNT1;
}

// This function is meant to be called with masked interrupts
void AvrTimer::reschedule()
{
    Task* task;
    while((task = list.front()) != 0) {

        int32_t delay = (int32_t) (task->when - now());
        if (delay > 0) {
            // No more task to execute
            break;
        }

        // The task must be executed now
        list.remove(task);
        task->post();
    }

    if (task && ((task->when >> 16) == (offset >> 16))) {
        OCR1A = (uint16_t)list.front()->when;
        TIMSK1 = _BV(OCIE1A) |  // Timer/Counter1, Output Compare A Match Interrupt Enable
                 _BV(TOIE1);    // Timer/Counter1, Overflow Interrupt Enable
    } else {
        // No more timers soon
        TIMSK1 = _BV(TOIE1);    // Timer/Counter1, Overflow Interrupt Enable
    }
}

/**
 * Timer/Counter1, Overflow Interrupt
 */
ISR(TIMER1_OVF_vect)
{
    AvrTimer::instance.offset += 0x10000;
    AvrTimer::instance.reschedule();
}

/**
 * TIMER1 Interrupt Service Routine
 */
ISR(TIMER1_COMPA_vect)
{
    AvrTimer::instance.reschedule();
}

} /* namespace octopus */
