#ifndef AVRSTEPPER_H
#define AVRSTEPPER_H

#ifdef __AVR__

#include "octopus/stepper.h"
#include <avr/io.h>

namespace octopus {

/**
 * @brief Two phase stepper motor implementation for AVR microcontrollers.
 *
 * This class can control a two phase stepper motor using 4 GPIOs of an AVR microcontroller.
 *
 * @par Example
 * @include stepper-sample.cpp
 */
class AvrStepper: public Stepper
{
public:
    /**
     * @brief Stepper mode.
     */
    typedef enum {
        /**
         * This is the usual method for full step driving the motor.
         * Two phases are always on. The motor will have full rated torque.
         *
         * <em>(from <a href="http://en.wikipedia.org/wiki/Stepper_motor#Full_step_drive_.28two_phases_on.29">Wikipedia</a>)</em>
         */
        MODE_FULL_STEP_DRIVE,

        /**
         *
         * When half stepping, the drive alternates between two phases on
         * and a single phase on. This increases the angular resolution,
         * but the motor also has less torque (approx 70%) at the half step
         * position (where only a single phase is on). This may be
         * mitigated by increasing the current in the active winding to
         * compensate. The advantage of half stepping is that the drive
         * electronics need not change to support it.
         *
         * <em>(from <a href="http://en.wikipedia.org/wiki/Stepper_motor#Half_stepping">Wikipedia</a>)</em>
         */
        MODE_HALF_STEPPING,

        /**
         * In this drive method only a single phase is activated at a time.
         * It has the same number of steps as the full step drive, but the
         * motor will have significantly less than rated torque. It is
         * rarely used.
         *
         * <em>(from <a href="http://en.wikipedia.org/wiki/Stepper_motor#Wave_drive">Wikipedia</a>)</em>
         */
        MODE_WAVE_DRIVE
    } Mode;

    /**
     * @brief Constructor.
     *
     * This constructor gives you access to a step motor using 4 GPIOs.
     * If the motor turns in the wrong direction, you can invert just two
     * @a pin parameters.
     *
     * @param[in] port
     *      Port to use:
     *      @arg @c &PORTB
     *      @arg @c &PORTC
     *      @arg @c &PORTD
     *
     * @param[in] pinA1
     *      First PIN for coil A.
     *
     * @param[in] pinA2
     *      Second PIN for coil A.
     *
     * @param[in] pinB1
     *      First PIN for coil B.
     *
     * @param[in] pinB2
     *      Second PIN for coil B.
     *
     * @param[in] mode
     *      Driving mode, see Mode for a description of this parameters.
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
     */
    AvrStepper(volatile uint8_t *port,
               uint8_t pinA1,
               uint8_t pinA2,
               uint8_t pinB1,
               uint8_t pinB2,
               Mode mode = MODE_FULL_STEP_DRIVE,
               const uint16_t *speed_lookup_table = DEFAULT_SPEED_LOOKUP_TABLE,
               speed_t max_speed = DEFAULT_MAX_SPEED);

protected:
    // From Stepper
    void step();

private:
    volatile uint8_t *port;
    uint8_t gpio_mask;
    Mode mode;
    uint8_t gpio_sequence[8];
};

/**
 * @example stepper-sample.cpp
 * This is an example of how to use the octopus::AvrStepper class.
 */

} /* namespace octopus */

#endif // AVRSTEPPER_H

#endif /* __AVR__ */
