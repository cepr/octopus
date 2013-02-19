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

#ifndef AVRTIMER_H
#define AVRTIMER_H

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

namespace octopus {

class AvrTimer : public Timer
{
public:
    static AvrTimer instance;
    virtual time_us_t now();
    virtual void reschedule();
    time_us_t offset;
private:
    AvrTimer();
};

} /* namespace octopus */

#endif // AVRTIMER_H
