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
#include "octopus/power_manager.h"

namespace octopus {

Looper Looper::instance;

void Looper::run(Gpio* led_activity) {

    // Configure activity LED
    if (led_activity) {
        led_activity->setDirection(Gpio::OUTPUT);
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
                led_activity->clear();
            }

            PowerManager::instance.sleep();

            if (led_activity) {
                led_activity->set();
            }
		}
	}
}

} /* namespace octopus */

#endif /* __AVR__ */
