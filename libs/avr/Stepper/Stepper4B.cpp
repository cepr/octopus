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

#include "Stepper4B.h"

#define PORT PORTB
#define DDR DDRB

Stepper4B::Stepper4B(char pinA1, char pinA2, char pinB1, char pinB2)
	: Stepper(pinA1, pinA2, pinB1, pinB2) {
    PORT = PORT & ~PinsMask;
    DDR |= PinsMask;
}

void Stepper4B::tick() {
	int index = mCurrentLocation & (sizeof(PinsSequence) / sizeof(PinsSequence[0]) - 1);
	PORT = (PORT & ~PinsMask) | PinsSequence[index];
}

void Stepper4B::setEnabled(bool enable) {
	if (enable) {
		tick();
	} else {
		PORT = PORT & ~PinsMask;
	}
}
