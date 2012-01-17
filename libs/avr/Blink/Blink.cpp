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

#include <avr/io.h>
#include "Blink.h"
#include "fatal.h"

Blink::Blink() : mEnabled(this), mTimer(this) {
    DDRB |= _BV(DDB5);
    mRequestId = 0;
}

Blink::Timer::Timer(Blink* parent) : mParent(parent) {
	mTimeMs = 0;
}

void Blink::Timer::onTimerLISR(unsigned short when, char what) {
	// In order to only take into account the last call to setEnabled(), we
	// check if this timer was scheduled from the same instance.
	if (what == mParent->mRequestId) {
		schedule(when+1000, what);
		mTimeMs++;
		if (mTimeMs == 1000) {
			PORTB ^= _BV(PORTB5);
			mTimeMs = 0;
		}
	}
}

Property* Blink::getChild(unsigned char index) {
	switch(index) {
	case 0: return &mEnabled;
	default: return 0;
	}
}

void Blink::onPropertyChanged(class Property* prop) {
	mRequestId++;
	if (mEnabled) {
		cli();
		mTimer.onTimerLISR(SystemTimer::now(), mRequestId);
		sei();
	} else {
		// We do not need to stop the timer, onTimer will detect that
		// mRequestId has changed, and will not reschedule.
		PORTB &= ~_BV(PORTB5);
	}
}
