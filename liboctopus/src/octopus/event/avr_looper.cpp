/*
 * Copyright 2013 Cedric Priscal
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

#ifdef __AVR__

#include "octopus/event/looper.h"
#include "octopus/util/lock.h"

#include <avr/sleep.h>

namespace octopus {
namespace event {

using util::List;
using util::Lock;

Looper::Looper() {
}

void Looper::run() {
	// Initialize sleep mode
	set_sleep_mode(SLEEP_MODE_IDLE);

	// Handle all events
	while(true) {
		// Extract the next item from the list
		Item* item;

		// Critical section
		{
			Lock lock;
			item = remove(front());
			if (!item) {
				sleep_enable();
				sleep_cpu();
				sleep_disable();
			}
		}

		// If we was sleeping, it means an interrupt has awake the CPU.
		// This interrupt is treated right now, with a possible new Event
		// being posted.

		// Execution with activated interrupts
		if (item) {
			// Call onEvent() method
			item->onEvent();
		}
	}
}

namespace {
	Looper default_looper;
}

Looper* Looper::get() {
	return &default_looper;
}

} /* namespace event */
} /* namespace octopus */

#endif /* __AVR__ */
