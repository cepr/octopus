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

#ifndef LOOPER_H_
#define LOOPER_H_

#include "octopus/util/list.h"
#include "event.h"

namespace octopus {
namespace event {

/**
 * \brief Message loop scheduler
 *
 * This class runs a message loop. Every message which is scheduled for execution with \a util::List.insert() method will be executed
 * later on by the looper.
 */
class Looper: public util::List<Event> {
public:
	/**
	 * \brief Constructor.
	 */
	Looper();

	/**
	 * \brief Run the looper
	 *
	 * Call this method to execute the looper. It will wait for incoming events and will call the onEvent() method of each event.
	 *
	 * \warning For wxWidgets implementation, this function is non blocking and should be connected to the wxIdleEvent handler.
	 */
	void run(void);

	/**
	 * \brief Get the default looper
	 *
	 * Most the time, you will only need one looper in your system. In that case you can use this static method to
	 * get it.
	 */
	static Looper* get();
};

} /* namespace event */
} /* namespace octopus */

#endif /* LOOPER_H_ */
