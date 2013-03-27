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

#ifndef LOOPER_H_
#define LOOPER_H_

#include "octopus/list.h"
#include "octopus/async_operation.h"
#include "octopus/gpio.h"

namespace octopus {

/**
 * @brief Message loop scheduler
 *
 * This class runs a message loop. Every message which is scheduled for
 * execution with @a List::insert() method will be executed later on by
 * the looper.
 */
class Looper: public List<AsyncOperation> {
public:
    /**
     * @brief The only instance of looper
     */
    static Looper instance;

    /**
     * @brief Run the looper.
	 *
     * Call this method to execute the looper. It will wait for incoming
     * events and will call the AsyncOperation::onFinished() method of
     * each event.
	 *
     * @param[in] led_activity
     *      GPIO used to monitor the Looper activity.
	 */
    void run(Gpio* led_activity = 0);

private:
    // Private constructor.
    Looper() {}
};

} /* namespace octopus */

#endif /* LOOPER_H_ */
