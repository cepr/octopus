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

#include "octopus/looper.h"
#include "octopus/lock.h"

#include <avr/sleep.h>

namespace octopus {

Looper Looper::instance;

void Looper::run(bool led_activity) {
	// Initialize sleep mode
	set_sleep_mode(SLEEP_MODE_IDLE);

    // Configure Arduino LED
    if (led_activity) {
        DDRB |= _BV(DDB5);
    }

    // Activate interrupts
    sei();

	// Handle all events
	while(true) {
		// Extract the next item from the list
        AsyncOperation* item;

		// Critical section
		{
			Lock lock;
			item = remove(front());
		}

		// Execution with activated interrupts
		if (item) {
			// Call onEvent() method
            item->onFinished();
		} else {
			// No more pending event, go to sleep
            if (led_activity) {
                PORTB &= ~_BV(PORTB5);
            }
			sleep_enable();
			sleep_cpu();
			sleep_disable();
            if (led_activity) {
                PORTB |= _BV(PORTB5);
            }
		}
	}
}

} /* namespace octopus */

#endif /* __AVR__ */
