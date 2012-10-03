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
#include "blink.h"
#include "octopus/util/fatal.h"

Blink::Blink(Packet* packet) : PropertyRecord(packet), mEnabled(packet), mTimer(this) {
    DDRB |= _BV(DDB5);
    mEnabled.registerListener(this);
}

Blink::Timer::Timer(Blink* parent) : mParent(parent), mTime20Ms(0) {
}

void Blink::Timer::onTimerLISR(unsigned short when, char what) {
	// In order to only take into account the last call to setEnabled(), we
	// check if this timer was scheduled from the same instance.
    schedule(when+20000, 0);
    mTime20Ms++;
    if (mTime20Ms == 50) {
        PORTB ^= _BV(PORTB5);
        mTime20Ms = 0;
    }
}

Property* Blink::getChild(unsigned char index) {
	switch(index) {
	case 0: return &mEnabled;
	default: return 0;
	}
}

void Blink::onPropertyChanged(class Property* prop, PROPERTY_INFO what, ORIGIN origin) {

	if (mEnabled) {
		cli();
		mTimer.onTimerLISR(SystemTimer::now(), 0);
		sei();
	} else {
        mTimer.cancel();
		PORTB &= ~_BV(PORTB5);
	}
}
