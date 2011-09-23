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

#include <avr/io.h>
#include "Stepper.h"

#include "AccelerationTable.h"
#include "AvrFlash.h"

#define NB_DELAYS (sizeof(DELAYS)/sizeof(DELAYS[0]))
#define MAX_SPEED ((short)(NB_DELAYS - 1))

Stepper::Stepper(char pinA1, char pinA2, char pinB1, char pinB2) :
	mCurrentLocation(), mTargetLocation(this), mManual(this) {

	mFinishListener = 0;
	PinsMask        = _BV(pinA1) | _BV(pinA2) | _BV(pinB1) | _BV(pinB2);

#define A_OFF 0
#define A_CCW _BV(pinA2)
#define A_CW _BV(pinA1)

#define B_OFF 0
#define B_CCW _BV(pinB2)
#define B_CW _BV(pinB1)

#ifdef HALF_STEP
	PinsSequence[0] = A_CCW | B_CCW;
    PinsSequence[1] = A_OFF | B_CCW;
    PinsSequence[2] = A_CW  | B_CCW;
    PinsSequence[3] = A_CW  | B_OFF;
    PinsSequence[4] = A_CW  | B_CW;
    PinsSequence[5] = A_OFF | B_CW;
    PinsSequence[6] = A_CCW | B_CW;
	PinsSequence[7] = A_CCW | B_OFF;
#else
	PinsSequence[0] = A_CCW | B_CCW;
    PinsSequence[1] = A_CW  | B_CCW;
    PinsSequence[2] = A_CW  | B_CW;
    PinsSequence[3] = A_CCW | B_CW;
#endif

	mCurrentLocation = 0;
    mCurrentSpeed = 0;
    mTimerStarted = false;
}

void Stepper::registerListener(StepperListener *finishListener) {
    mFinishListener = finishListener;
}

void Stepper::onTimer(char what, unsigned short when) {

	/* Update location according to current speed */
	if (mCurrentSpeed > 0) {
		mCurrentLocation++;
	} else if (mCurrentSpeed < 0) {
		mCurrentLocation--;
	}

	/* Compute remaining distance */
	short delta_x;
	if (mManual) {
		if (mTargetLocation == 0) {
			// We need to stop as quickly as possible.
			if (mCurrentSpeed > 0) {
				delta_x = -1;
			} else if (mCurrentSpeed < 0) {
				delta_x = 1;
			} else {
				delta_x = 0;
			}
		} else {
			delta_x = mTargetLocation;
		}
	} else {
		delta_x = mTargetLocation - mCurrentLocation - mCurrentSpeed;
	}

	/* Accelerate or decelerate if possible */
	if (delta_x > 0) {
		if (mCurrentSpeed < MAX_SPEED) {
			mCurrentSpeed++;
		}
	} else if (delta_x < 0) {
		if (mCurrentSpeed > -MAX_SPEED) {
			mCurrentSpeed--;
		}
	} else {
		if (mCurrentSpeed == 0) {
			/* We have reached out destination */
			mTimerStarted = false;
			setEnabled(false);
			if (mFinishListener) {
				mFinishListener->onStepperStopped(this, mCurrentLocation);
			}
			return;
		}
	}

	/* Compute waiting time before next tick */
	if (mCurrentSpeed >= 0) {
		when += readU16(&DELAYS[mCurrentSpeed]);
	} else {
		when += readU16(&DELAYS[-mCurrentSpeed]);
	}

	/* Update motor rotation angle, and reprogram timer */
	tick();
	schedule(when, 0);
}

PROPERTY_TYPE Stepper::getType() {
	return PROPERTY_TYPE_VOID;
}

Property* Stepper::getChild(unsigned char index) {
	switch(index) {
	case 0: return &mTargetLocation;
	case 1: return &mCurrentLocation;
	case 2: return &mManual;
	default: return 0;
	}
}

void Stepper::onPropertyChanged(class Property* prop) {
	if (!mTimerStarted) {
		mTimerStarted = true;
		setEnabled(true);
		onTimer(now(), 0);
	}
}
