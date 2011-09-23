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

#ifndef STEPPER4C_H_
#define STEPPER4C_H_

#include "Stepper.h"

/**
 * @brief Bipolar step motor driver using 4 GPIOs of port C.
 */
class Stepper4C : public Stepper {
    void tick();
    void setEnabled(bool enable);
public:
    /**
     * Constructor.
     *
     * Create a new step motor driver for a motor plugged into @a pinA1, @a pinA2, @a pinB1, and @a pinB2 of ATMEGA328 port C.
     * If specified, the @a pinEN will be used to put automatically the motor in standby.
     *
     * @param[in] pinA1 		GPIO of port C on which the first coil is plugged
     * @param[in] pinA2 		GPIO of port C on which the first coil is plugged
     * @param[in] pinB1 		GPIO of port C on which the second coil is plugged
     * @param[in] pinB2 		GPIO of port C on which the second coil is plugged
     */
    Stepper4C(char pinA1, char pinA2, char pinB1, char pinB2);
};

#endif /* STEPPER4C_H_ */
