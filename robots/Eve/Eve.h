/*
 * Copyright 2010-2011 Cedric Priscal
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

#ifndef EVE_H_
#define EVE_H_

#include "Robot/Robot.h"
#include "property_record.h"
#include "Timer/Timer.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "Stepper/Stepper4C.h"
#include "Stepper/Stepper4D.h"
#include "Servo/Servo.h"
#include "PropertyPacket.h"
#include "RemotePropertyServer.h"

class LeftStepper: public Stepper4C {
public:
	LeftStepper() : Stepper4C(PORTC0, PORTC1, PORTC3, PORTC2) {}
	const char* getName() { return "LeftStepper"; }
	const char* getDescription() { return "Left step motor"; }
};

class RightStepper: public Stepper4D {
public:
	RightStepper() : Stepper4D(PORTD3, PORTD2, PORTD4, PORTD5) {}
	const char* getName() { return "RightStepper"; }
	const char* getDescription() { return "Right step motor"; }
};

/**
 * @brief Ground robot powered by two steppers, and one servomotor.
 */
class Eve : public Robot, public StepperListener, public PropertyRecord/*, public UsartListener*/ {

private:
    // List of modules
    Blink 					mBlink;
    LeftStepper 			mLeft;
    RightStepper 			mRight;
    Servo					mServo;

    // Remote control
	AvrUsart 				mAvrUsart;
	Packet 					mPacket;
	PropertyPacket 			mBridge;
	RemotePropertyServer 	mServer;

public:
    /**
     * @brief Constructor.
     */
    Eve();

    // Property definition
	PROPERTY_TYPE getType()        { return PROPERTY_TYPE_VOID; }
	const char*   getName()        { return "Eve"; }
	const char*   getDescription() { return "Ground robot"; }

    /**
     * \copydoc Robot::onStart()
     */
    void onStart();

    /**
     * \copydoc StepperListener::onStepperStopped()
     */
    void onStepperStopped(Stepper *stepper, short location);

    /**
     * \copydoc UsartListener::onUsartReceived()
     */
    void onUsartReceived(unsigned char byte);

    /**
     * \copydoc Property::getChild()
     */
    Property* getChild(unsigned char index);
};

#endif /* EVE_H_ */
