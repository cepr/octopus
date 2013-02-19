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

#ifndef TIMER_H
#define TIMER_H

#include "octopus/async_operation.h"
#include "octopus/list.h"
#include <stdint.h>

namespace octopus {

/**
 * @brief Timer
 *
 * Abstract base class for all Timer drivers. Use this class to schedule
 * timers at specified absolute time.
 */
class Timer {

public:
    /**
     * @brief Time type
     *
     * The type time_us_t represents an instant expressed in number of
     * microseconds elapsed since boot.
     */
    typedef uint32_t time_us_t;

    /**
     * @brief Abstract task
     *
     * The @a Task class represents a task to be run at a specified time.
     */
    class Task: public AsyncOperation
    {
    public:
        /**
         * @brief Constructor.
         *
         * @param looper
         *      Looper which should handle the call to run(), or zero if you want
         *      run() to be called directly. Using a Looper is recommended if
         *      run() has to perform a long treatment.
         */
        Task(Looper* looper = 0) :
            AsyncOperation(looper)
        {
        }

        /**
         * @brief Task implementation.
         *
         * The task to run should be specified in the implementation of
         * the @a run() method.
         *
         * @param when
         *      Original scheduled execution time. It roughly corresponds
         *      to the current time, minus a small latency due to the
         *      task scheduling.
         *
         * @param what
         *      User parameter which was passed in @ref Timer::schedule().
         */
        virtual void run(time_us_t when, char what) = 0;

        time_us_t when;
        char what;

        // For List<Task>
        Task* prev;
        Task* next;

    private:
        // From AsyncOperation
        virtual void onFinished() {
            status = STATUS_IDLE;
            run(when, what);
        }
    };

    /**
     * @brief Schedules a timer
     *
     * @param[in] task
     *      Task to execute.
     *
     * @param[in] when
     *      Scheduled execution time expressed as elapsed microseconds
     *      from boot. If @a when is smaller than current time, the task
     *      will be executed right away.
     *
     * @param[in] what
     *      User parameter. This parameter will be passed to the call
     *      to @ref Task::run().
     */
    void schedule(
            Task* task,
            time_us_t when,
            char what = 0);

    /**
     * @brief Cancels a timer task
     *
     * @param[in,out] task  Timer task to cancel
     */
    void cancel(Task* task);

    /**
     * @brief Get absolute time
     *
     * @return Absolute elapsed time from boot in microseconds
     */
    virtual time_us_t now() = 0;

protected:
    // Program physical timer for next event
    virtual void reschedule() = 0;
    // List of scheduled tasks
    List<Task> list;
};

} /* namespace octopus */

#endif /* TIMER_H */
