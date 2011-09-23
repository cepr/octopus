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
#include <avr/interrupt.h>
#include "SwitchingRegulator.h"

/**
 * Updating period of PWM duty cycle, in milliseconds
 */
#define REGULATION_PERIOD 1

#if (F_CPU == 8000000L)
#define REGULATION_FREQUENCY_31250HZ _BV(CS00)
#else
#error Unknown CPU frequency
#endif

/**
 * PWM frequency
 */
#define REGULATION_FREQUENCY REGULATION_FREQUENCY_31250HZ

/**
 * Initial duty cycle between 0 and 255.
 * Setting this value to anything other than 0 will speed up the
 * initial voltage establishment.
 */
#define INITIAL_DUTYCYCLE 0

/**
 * Maximum duty cycle, between 0 and 255.
 * A very high duty cycle may means a short circuit, this is why limiting the
 * duty cycle is safer.
 */
#define MAX_DUTYCYCLE 128

/**
 * Proportional factor of the regulation, between 0 and 15
 * Set this value the highest possible without observing instabilities.
 */
#define REGULATION_K 10

static volatile unsigned char dutycycle;

SwitchingRegulator::SwitchingRegulator(CHANNEL channel, VREF vref, unsigned short voltage) : AnalogChannel(channel, vref)
{
	mEnabled = false;
	mVoltage = voltage;

	/* Set OC0A (PD6) as output, zero */
	PORTD &=~ _BV(PORTD6);
	DDRD |= _BV(DDD6);

	/* Activate Timer/Counter0 Overflow Interrupt Enable
	 */
	TIMSK0 = _BV(TOIE0);
}

/* Timer/Couner0 Overflow */
ISR(TIMER0_OVF_vect) {
	OCR0A = dutycycle;
}

void SwitchingRegulator::setEnable(bool enable) {
	if (mEnabled != enable) {
		mEnabled = enable;
		if (enable) {
			/* *****************
			 * Enable regulation
			 * *****************/

			/* Start ADC */
			startPeriodic(REGULATION_PERIOD);

			/* Start fast PWM, and set GPIO as OC0A*/
			OCR0A = dutycycle = INITIAL_DUTYCYCLE;
			TCCR0A = _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);
			TCCR0B = REGULATION_FREQUENCY;

		} else {
			/* ******************
			 * Disable regulation
			 * ******************/

			/* Stop fast PWM, and set PD6 as GPIO */
			TCCR0A = _BV(WGM01) | _BV(WGM00);
			TCCR0B = 0;

			/* Stop ADC */
			stop();
		}
	}
}

void SwitchingRegulator::setVoltage(unsigned short voltage)
{
	mVoltage = voltage;
}

void SwitchingRegulator::onNewMeasure(unsigned short value)
{
	/*
	 * value is the real voltage
	 * mVoltage is the targeted voltage
	 *
	 *           |\
	 *           | \         ___     |\
	 * value-----|+ \       |   |    | \
	 *           |   }--dV--| K |----|+ \
	 * mVoltage--|- /       |___|    |   }--.--dutycycle
	 *           | /              .--|+ /   |
	 *           |∕               |  | /    |
	 *                            |  |/     |
	 *                            |_________|
	 *
	 * dV is the voltage error, either positive or negative.
	 * K is a multiplicative factor, to convert from a voltage error to a duty-cycle correction.
	 * The duty cycle is finally updated with a corrected value.
	 *
	 * For security purpose, duty cycle is limited to MAX_DUTYCYCLE.
	 */
	if (mEnabled) {
		short dV = value - mVoltage;
		short dc = (dV >> (15-REGULATION_K)) + (short)dutycycle;
		if (dc < 0) {
			dc = 0;
		} else if (dc > MAX_DUTYCYCLE) {
			dc = MAX_DUTYCYCLE;
		}
		dutycycle = dc;
	}
}
