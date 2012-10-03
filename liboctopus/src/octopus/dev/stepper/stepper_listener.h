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

#ifndef STEPPERLISTENER_H_
#define STEPPERLISTENER_H_

#include "Listener.h"

/**
 * @brief Listener interface.
 *
 * You should implement this interface in order to be notified when a stepper
 * has reached its destination.
 *
 * @see Stepper::go()
 */
class StepperListener : public Listener {
public:
	/**
	 * @brief Called when the step motor has reached its destination.
	 *
	 * @param stepper [in] Reference to the Stepper involved.
	 * @param location [in] Current stepper location.
	 *
     * @see Stepper::go()
	 */
    virtual void onStepperStopped(class Stepper *stepper, short location)=0;
};

#endif /* STEPPERLISTENER_H_ */
