/*
 * Copyright 2010 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Timer.h"
#include "Handler.h"
#include "Looper.h"
#include "fatal.h"

#if 0

/**
 * Global and unique instance of Timer.
 */
Timer gTimer;

typedef struct {
    bool enable;
    bool available;
    unsigned long when;
    TimerListener *listener;
    char what;
} SClient;

#define CLIENTS_SIZE 6
static SClient clients[CLIENTS_SIZE];

#define THRESHOLD 30

static void reschedule() {
    unsigned short now = TCNT1;
    unsigned short next = 0xffff;
    int i;
    for (i=0; i<CLIENTS_SIZE; i++) {
        if (clients[i].enable) {
            unsigned short remaining = clients[i].when - now;
            if (((0x10000-THRESHOLD) < remaining) || (remaining < THRESHOLD)) {
                PostEvent(&gTimer, i);
                clients[i].enable = false;
            } else if (remaining < next) {
                next = remaining;
            }
        }
    }
    OCR1A = now + next;
}

void Timer::onEvent(char what) {
    TimerListener *listener = clients[(int)what].listener;
    if (listener) {
        listener->onTimer(/*clients[(int)what].what,*/ clients[(int)what].when);
    }
    clients[(int)what].available = true;
}

/**
 * TIMER1 Interrupt Service Routine
 * It runs each time the timer reaches zero.
 */
ISR (TIMER1_COMPA_vect) {
    reschedule();
}

Timer::Timer() {
    int i;
    for (i=0; i<CLIENTS_SIZE; i++) {
        clients[i].enable = false;
        clients[i].available = true;
    }
    TCCR1A = 0; // Normal port operation
    TCCR1B = _BV(CS11); // clkIO / 8 (From prescaler)
    TIMSK1 = _BV(OCIE1A); // Output Compare A Match Interrupt Enable
}

void Timer::schedule(TimerListener *listener, char what, unsigned short when) {
    /* Add the event in the list */
    int i;
    for (i=0; i<CLIENTS_SIZE; i++) {
        if (clients[i].available) {
            clients[i].available = false;
            clients[i].listener = listener;
            clients[i].what = what;
            clients[i].when = when;
            clients[i].enable = true;
            /* Force a reschedule */
            cli();
            reschedule();
            sei();
            return;
        }
    }
    fatal(FATAL_TIMER_CLIENTS_OVERFLOW);
}

#endif
