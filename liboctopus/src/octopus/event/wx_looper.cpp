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

#ifdef __WXGTK__

#include "octopus/event/looper.h"
#include "octopus/util/lock.h"

namespace octopus {
namespace event {

using util::List;
using util::Lock;

Looper::Looper() {
}

void Looper::run() {

	// Handle all events
	while(true) {
		// Extract the next item from the list
		Item* item;

		// Critical section
		{
			Lock lock;
			item = remove(front());
			if (!item) {
				return;
			}
		}

		// Call onEvent() method
		item->onEvent();
	}
}

} /* namespace event */
} /* namespace octopus */

#endif /* __WXGTK__ */
