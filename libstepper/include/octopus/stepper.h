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

#ifndef STEPPER_H_
#define STEPPER_H_

#include "octopus/timer.h"
#include "octopus/async_operation.h"

namespace octopus {

/**
 * @brief Abstract base class for all step motor drivers.
 *
 * This class provides both the public interface to control a step motor
 * and also the scheduler which controls the position and speed of the
 * stepper.
 *
 * Nevertheless, this class does not handle the toggling of the GPIOs to
 * move the stepper. You have to either use an existing child class or
 * define your own.
 */
class Stepper: private Timer::Task {

public:
    /**
     * @brief Type representing a stepper position.
     *
     * The position is expressed in number of steps or half-step depending
     * on the underlying implementation.
     */
    typedef int16_t pos_t;

    /**
     * @brief Type representing a stepper speed.
     *
     * Stepper rotation speed corresponding to the index in the speed
     * lookup table. The index 0 corresponds to a zero speed, and the
     * highest index of the lookup table corresponds to the highest
     * possible speed.
     */
    typedef int speed_t;

    /**
     * @brief Gets the current absolute position.
     *
     * @return The current absolute position.
     *
     * @see pos_t
     * @see reachPosition()
     */
    pos_t getPosition() {
        return current_pos;
    }

    /**
     * @brief Gets the current speed.
     *
     * @return The index of the current speed in the speed lookup table.
     *
     * @see speed_t
     * @see reachSpeed()
     */
    speed_t getSpeed() {
        return current_speed;
    }

    /**
     * @brief Gets the maximum speed.
     *
     * @return The index of the last element of the speed lookup table.
     *
     * @see speed_t
     * @see reachSpeed()
     */
    speed_t getMaxSpeed() {
        return max_speed;
    }

    /**
     * @brief Reaches an absolute position.
     *
     * This asynchronous function programs the stepper so that it reaches
     * @a position with a final zero speed.
     *
     * Once the specifed @a position has been reached, and if
     * @a callback is not zero, @a callback will be called.
     *
     * You do not have to wait for an asynchronous operation to complete
     * before starting a new one. Nevertheless, the callback of the
     * previous asynchronous operation will not be called.
     *
     * @param position
     *      Absolute position to reach.
     *
     * @param callback
     *      Called when the position is reached.
     */
    void reachPosition(pos_t position,
                       AsyncOperation* callback = 0);

    /**
     * @brief Reaches an absolution speed.
     *
     * This asynchronous function programs the stepper so that it reaches
     * @a speed.
     *
     * Once the specified @a speed has been reached, and if @a callback is
     * not zero, @a callback will be called.
     *
     * You do not have to wait for an asynchronous operation to complete
     * before starting a new one. Nevertheless, the callback of the
     * previous asynchronous operation will not be called.
     *
     * The stepper will continue to rotate at @a speed until the next call
     * to reachPosition() or reachSpeed().
     *
     * @param speed
     *      Absolute speed to reach.
     *
     * @param callback
     *      Called when the speed is reached.
     */
    void reachSpeed(speed_t speed,
                    AsyncOperation* callback = 0);

    static const uint16_t DEFAULT_SPEED_LOOKUP_TABLE[];
    static const speed_t DEFAULT_MAX_SPEED;

protected:

    /**
     * @brief Constructor.
     *
     * This constructor must be called by child classes.
     *
     * @param[in] speed_lookup_table
     *      Pointer to a speed lookup table. Each element of this table represents a delay in microseconds
     *      corresponding to an indexed speed. When the stepper is accelerating, the speed is increased by
     *      one index every step. In other terms, the speed lookup table corresponds to the acceleration
     *      profile. You can use the command line program `step_table` to compute this table given some
     *      parameters.
     *
     * @param[in] max_speed
     *      Maximum speed. It corresponds to the higher index of @a speed_lookup_table.
     *
     * @warning
     *      In the AVR implementation of this class, @a speed_lookup_table must be defined in the program
     *      memory, that is to say you must include <avr/pgmspace.h> and use the `PROGMEM` attribute. See
     *      the sample for an example.
     */
    Stepper(const uint16_t *speed_lookup_table = DEFAULT_SPEED_LOOKUP_TABLE,
            speed_t max_speed = DEFAULT_MAX_SPEED);

    // To be implemented by child classes
    virtual void step() = 0;

    const uint16_t* speed_table;    // speed lookup table
    speed_t max_speed;              // maximum stepper speed

    typedef enum {
        STATE_FREE_RUN,             // the stepper is running at continuous speed, or stopped
        STATE_TARGET_POS,           // the stepper is reaching the position
                                    // specified by target_pos, see reachPosition()
        STATE_TARGET_SPEED          // the stepper is reaching the speed
                                    // specified by target_speed, see reachSpeed()
    } State;

    State state;                    // current stepper state
    pos_t current_pos;              // current stepper position
    pos_t target_pos;               // target stepper position

    speed_t current_speed;          // current speed
    speed_t target_speed;           // target speed

    AsyncOperation *callback;       // callback to be called when stepper has
                                    // reached its target

private:
    // From Timer::Task
    void run(Timer::time_us_t when, char what = 0);
};

} /* namespace octopus */

#endif /* STEPPER_H_ */
