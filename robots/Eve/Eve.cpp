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

#include "Eve.h"
#include "fatal.h"

static Eve eve;
Robot* gRobot = &eve;

Eve::Eve() : PropertyRecord(),
	// Modules
    mBlink(),
    mLeft(),
    mRight(),
    mServo(PORTD7),

    // Remote control
    mAvrUsart(),
    mPacket(&mAvrUsart),
    mBridge(&mPacket),
    mServer(this, &mBridge)
{
	mBridge.registerServer(&mServer);
    //mAvrUsart.registerListener(this);
}

void Eve::onStart() {
	mBlink.mEnabled = true;
    mAvrUsart.sendString("Hello, World !");
}

void Eve::onUsartReceived(unsigned char byte) {
//    mAvrUsart.send(byte+1);
}

void Eve::onStepperStopped(Stepper *stepper, short location) {
}

Property* Eve::getChild(unsigned char index) {
	switch(index) {
	case 0: return &mBlink;
	case 1: return &mLeft;
	case 2: return &mRight;
	case 3: return &mServo;
	default: return 0;
	}
}
