/*
 * Copyright 2010-2012 Cedric Priscal
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

#include "octopus/prop/property_record.h"
#include "octopus/dev/usart/avr_usart.h"
#include "octopus/dev/usart/usart_listener.h"
#include "octopus/dev/blink/blink.h"
#include "octopus/util/fatal.h"

class LoopBack: private UsartListener {

private:
	// List of modules
	Blink mBlink;

	// Remote control
	AvrUsart mAvrUsart;

public:
	// Constructor
	LoopBack() :
			mBlink(0), mAvrUsart(AvrUsart::B57600) {
		mAvrUsart.registerListener(this);
	}

	void onStart() {
		mAvrUsart.sendString("LoopBack starting!");
	}

	void onUsartReceived(unsigned char byte) {
		mAvrUsart.sendByte(byte);
	}

	void onUsartBufferEmpty() {
	}
};

int main(void) {
	static LoopBack lb;
	lb.onStart();
	Event::startLooper();
	return 0;
}