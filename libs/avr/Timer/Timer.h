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

#ifndef TIMER_H_
#define TIMER_H_

#if 0

#include <avr/io.h>
#include "Handler.h"
#include "timer_listener.h"

/**
 * You should never instantiate this class, please directly
 * use the variable gTimer instead.
 */
class Timer : public Handler {
public:
    Timer();

    /**
     * \brief Schedule a new event in the future.
     *
     * \param[in] listener Listener to be called.
     * \param[in] what User-defined integer which will be passed as an argument to the listener.
     * \param[in] when Absolute time in microseconds.
     */
    void schedule(TimerListener *listener, char what, unsigned short when);

    unsigned inline short now() {
        return TCNT1;
    }
    void onEvent(char what);
};

extern Timer gTimer;

#endif

#endif /* TIMER_H_ */
