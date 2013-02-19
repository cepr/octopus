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

#ifdef __AVR

#include <avr/io.h>
#include "servo.h"

#define EVENT_START_PULSE 0
#define EVENT_FINISH_PULSE 1

#define PORT PORTD
#define DDR DDRD

Servo::Servo(char pin, Packet* packet) : PropertyRecord(packet), mEnabled(packet), mPosition(packet), mPin(pin), mNextPulse(0), mPulseWidth(MIN_PULSE_WIDTH) {
    DDR |= _BV(mPin);
    mEnabled.registerListener(this);
    mPosition.registerListener(this);
}

void Servo::onTimerLISR(unsigned short when, char what) {
    if (what == EVENT_START_PULSE) {
        /* 50Hz tick */
        /* start pulse, and program the timer to stop the pulse */
        PORT |= _BV(mPin);
        mNextPulse = when + PULSE_PERIOD;
        schedule(when + mPulseWidth, EVENT_FINISH_PULSE);
    } else {
        /* stop pulse */
        PORT &= ~_BV(mPin);
        schedule(mNextPulse, EVENT_START_PULSE);
    }
}

Property* Servo::getChild(uint8_t index) {
	switch(index) {
	case 0: return &mEnabled;
	case 1: return &mPosition;
	default: return 0;
	}
}

void Servo::onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin) {

    if (prop == &mPosition) {
        // Position has changed, refresh pulse width
        uint32_t value = (unsigned short)mPosition;
        mPulseWidth = MIN_PULSE_WIDTH + (((MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) * value) >> 16);
    } else if (prop == &mEnabled) {
        // Enable has changed, let's start or stop timer
        if (mEnabled) {
            schedule(0, EVENT_START_PULSE);
        } else {
            PORT &= ~_BV(mPin);
            cancel();
        }
    }
}

#endif /* __AVR */
