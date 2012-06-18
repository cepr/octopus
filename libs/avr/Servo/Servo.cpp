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
#include "Servo.h"

#define PERIOD 20000

#define EVENT_50HZ 0
#define EVENT_FINISH_PULSE 1

#define PORT PORTD
#define DDR DDRD

PropertyServoPosition::PropertyServoPosition(Packet* packet) : PropertyU16(DEFAULT, packet) {
}

Servo::Servo(char pin, Packet* packet) : PropertyRecord(packet), mEnabled(this, packet), mPosition(packet) {
    mPin = pin;
    DDR |= _BV(mPin);
}

void Servo::go(unsigned short position) {
	mPosition = position;
}

void Servo::onTimerLISR(unsigned short when, char what) {
	if (mEnabled) {
		if (what == EVENT_50HZ) {
			/* 50Hz tick */
			/* start pulse, and program the timer to stop the pulse */
			PORT |= _BV(mPin);
			schedule(when + mPosition, EVENT_FINISH_PULSE);
		} else {
			/* stop pulse */
			PORT &= ~_BV(mPin);
			schedule(when + PERIOD - mPosition, EVENT_50HZ);
		}
	}
}

Property* Servo::getChild(unsigned char index) {
	switch(index) {
	case 0: return &mEnabled;
	case 1: return &mPosition;
	default: return 0;
	}
}

void Servo::onPropertyChanged(Property* prop, PROPERTY_INFO what) {
	if (mEnabled) {
		cli();
        onTimerLISR(now(), EVENT_50HZ);
		sei();
    }
}
