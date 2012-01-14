/*
 * Copyright 2010-2012 Cedric Priscal
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

#include "event.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

// static initialization
Event* Event::mpFirstEvent = 0;
Event* Event::mpLastEvent = 0;

Event::Event() {
	mpNextEvent = 0;
	isPending = false;
}

void Event::Post()
{
	cli();
	if (!isPending) {
		// The event is not already pending, we can append it to the list
		isPending = true;
		mpNextEvent = 0;
		if (mpLastEvent) {
			// The list is not empty, we must modify the last element of the list
			mpLastEvent->mpNextEvent = this;
		} else {
			// The list is empty, we must modify the first element of the list
			mpFirstEvent = this;
		}
		// The last element of the list is this event
		mpLastEvent = this;
	}
	sei();
}

void Event::startLooper(void) {
	// For ad vitam aeternam:
	for(;;) {
		if (mpFirstEvent) {
			// Remove first event from list
			cli();
			Event* ev = mpFirstEvent;
			if ((mpFirstEvent = mpFirstEvent->mpNextEvent) == 0) {
				// List is empty
				mpLastEvent = 0;
			}
			sei();

			// Call onEvent method
			ev->isPending = false;
			ev->onEvent();
		} else {
			// No pending event, we can go to sleep
//			set_sleep_mode(SLEEP_MODE_IDLE);
//          sleep_enable();
//          sleep_cpu();
//          sleep_disable();
		}
	}
}
