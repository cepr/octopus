/*
 * Copyright 2011 Cedric Priscal
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

#include "avr_timer0.h"
#include <avr/io.h>

AvrTimer0::AvrTimer0() {
}

unsigned char AvrTimer0::FastPWMChannelA::getValue() {
	return OCR0A;
}

void AvrTimer0::FastPWMChannelA::setValue(unsigned char value) {
	OCR0A = value;
}

unsigned char AvrTimer0::FastPWMChannelB::getValue() {
	return OCR0B;
}

void AvrTimer0::FastPWMChannelB::setValue(unsigned char value) {
	OCR0B = value;
}
