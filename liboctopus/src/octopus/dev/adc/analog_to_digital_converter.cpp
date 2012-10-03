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

#include <avr/interrupt.h>
#include <avr/io.h>

#include "analog_to_digital_converter.h"
#include "analog_channel.h"
#include "octopus/util/fatal.h"

#define ADC_PRESCALER_2   (                          _BV(ADPS0))
#define ADC_PRESCALER_4   (             _BV(ADPS1)             )
#define ADC_PRESCALER_8   (             _BV(ADPS1) | _BV(ADPS0))
#define ADC_PRESCALER_16  (_BV(ADPS2)                          )
#define ADC_PRESCALER_32  (_BV(ADPS2) |              _BV(ADPS0))
#define ADC_PRESCALER_64  (_BV(ADPS2) | _BV(ADPS1)             )
#define ADC_PRESCALER_128 (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0))

#if (F_CPU == 8000000L)
#define ADC_PRESCALER ADC_PRESCALER_64 // ADC clock = 125 kHz
#elif (F_CPU == 16000000L)
#define ADC_PRESCALER ADC_PRESCALER_128 // ADC clock = 125 kHz
#else
	#error Unknown CPU frequency
#endif

#define VREF_STABILIZATION_DELAY 0

static AnalogToDigitalConverter* gAnalogToDigitalConverter;

AnalogToDigitalConverter* AnalogToDigitalConverter::getInstance()
{
    static AnalogToDigitalConverter instance;
    return &instance;
}

AnalogToDigitalConverter::AnalogToDigitalConverter() : mTimer(this) {
	gAnalogToDigitalConverter = this;
	mPutIndex = 0;
	mGetIndex = 0;
	mCount = 0;
	mRunning = false;
	ADCSRA = _BV(ADIE) |				// ADC Interrupt Enable
#if (F_CPU == 8000000L)
			_BV(ADPS2) | _BV(ADPS1);	// Prescaler 64 => ADC clock = 125 kHz
#elif (F_CPU == 16000000L)
			_BV(ADPS2) | _BV(ADPS1);	// Prescaler 128 => ADC clock = 125 kHz
#else
	#error Unknown CPU frequency
#endif
}

AnalogToDigitalConverter::Timer::Timer(AnalogToDigitalConverter* parent) : mParent(parent) {
}

void AnalogToDigitalConverter::startADC(AnalogChannel *channel) {

	/* Check that there are not too many pending measurements */
	if (mCount == MAX_PENDING_CONVERTIONS) {
		fatal(FATAL_PENDING_ADC_OVERFLOW);
		return;
	}
	mCount++;

	/* Add AnalogChannel to pending list */
	mList[mPutIndex++] = channel;
	if (mPutIndex == MAX_PENDING_CONVERTIONS) {
		mPutIndex = 0;
	}

	/* If ADC not already running, start it now */
	if (!mRunning) {
		programNextADC();
	}
}

void AnalogToDigitalConverter::programNextADC() {
	/* Retrieve the next ADC to perform */
	AnalogChannel* channel = mList[mGetIndex];

	/* Configure the ADC */
	ADMUX = channel->mVref | channel->mChannel;
	ADCSRA = _BV(ADEN) | 	// ADC Enable
			_BV(ADIF) | 	// Clear ADC Interrupt Flag
			_BV(ADIE) | 	// ADC Interrupt Enable
			ADC_PRESCALER; 	// ADC Prescaler
	mRunning = true;

	/* Program the timer to be notified when ADC is stable */
#if VREF_STABILIZATION_DELAY > 0
	mTimer.schedule(Timer::now() + VREF_STABILIZATION_DELAY);
#else
	ADCSRA |= _BV(ADSC);
#endif
}

void AnalogToDigitalConverter::Timer::onTimerLISR(unsigned short when, char what) {
	/* Stabilization if finished, we can launch conversion */
	ADCSRA |= _BV(ADSC);
}

/*
 * ADC Conversion Complete
 * Interrupt context, we make it the shortest as possible
 */
ISR(ADC_vect) {
	gAnalogToDigitalConverter->Post(0);
}

/*
 * ADC conversion is complete
 * Main thread context, we retrieve the ADC result
 */
void AnalogToDigitalConverter::onEvent(char what) {

	/* Read ADC result */
	unsigned short value = ADC;

	/* Update list of pending measurements */
	AnalogChannel* channel = mList[mGetIndex++];
	if (mGetIndex == MAX_PENDING_CONVERTIONS) {
		mGetIndex = 0;
	}
	mCount--;

	/* If still some measures to do, directly program the next */
	if (mCount) {
		programNextADC();
	} else {
		/* Stop the ADC for power consumption */
		ADCSRA = 0;
		mRunning = false;
	}

	/* Report result to AnalogChannel */
	channel->onNewMeasure(value);
}
