/*
 * Copyright 2010 Cedric Priscal
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

#ifndef STEPPER4B_H_
#define STEPPER4B_H_

#include "Stepper.h"

/**
 * @brief Bipolar step motor driver using 4 GPIOs of port B.
 */
class Stepper4B : public Stepper {
    void tick();
    void setEnabled(bool enable);
public:
    /**
     * Constructor.
     *
     * Create a new step motor driver for a motor plugged into @a pinA1, @a pinA2, @a pinB1, and @a pinB2 of ATMEGA328 port B.
     * If specified, the @a pinEN will be used to put automatically the motor in standby.
     *
     * @param pinA1 [in] GPIO of port B on which the first coil is plugged
     * @param pinA2 [in] GPIO of port B on which the first coil is plugged
     * @param pinB1 [in] GPIO of port B on which the second coil is plugged
     * @param pinB2 [in] GPIO of port B on which the second coil is plugged
     */
    Stepper4B(char pinA1, char pinA2, char pinB1, char pinB2);

	const char* getDescription() { return "Step motor on port B"; }
};

#endif /* STEPPER4B_H_ */
