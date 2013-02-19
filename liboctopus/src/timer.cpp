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

#include "octopus/timer.h"
#include "octopus/fatal.h"
#include "octopus/list.h"
#include "octopus/lock.h"

namespace octopus {

void Timer::schedule(Task *task,
                     time_us_t when,
                     char what)
{
    // Prepare it
    // From Timer::Task
    task->when = when;
    task->what = what;
    // From AsyncOperation
    task->status = AsyncOperation::STATUS_PENDING;

    // Add it to the list in the correct place
    {
        Lock l;
        List<Task>::Iterator it;
        for (it = list.begin(); it.is_valid(); ++it) {
            if ((*it)->when > when) {
                break;
            }
        }
        list.insert(task, *it);
        if (list.front() == task) {
            reschedule();
        }
    }
}

void Timer::cancel(Task *task)
{
    Lock l;
    bool reschedule_needed = false;
    if (list.front() == task) {
        // This was the next timer, we need to reschedule
        reschedule_needed = true;
    }
    list.remove(task);
    if (reschedule_needed) {
        reschedule();
    }
}

} /* namespace octopus */
