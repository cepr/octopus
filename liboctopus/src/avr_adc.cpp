/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __AVR

#include <avr/interrupt.h>
#include <avr/io.h>

#include "octopus/avr_adc.h"
#include "octopus/lock.h"
#include "octopus/looper.h"

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

namespace octopus {

AvrADC AvrADC::instance;

AvrADC::Channel::Channel(CHANNEL channel, VREF vref) :
    channel(channel),
    vref(vref)
{
    /* Set IO as input, no pull */
    if (channel <= CHANNEL_ADC7) {
        DDRC &= ~_BV(channel);
        PORTC &= ~_BV(channel);
        /* Deactivate digital input buffer for power consumption */
        if (channel <= CHANNEL_ADC5) {
            DIDR0 |= _BV(channel);
        }
    }
}

AvrADC::AvrADC() :
    AsyncOperation(&Looper::instance)
{
}

void AvrADC::start(Channel *channel)
{
    Lock l;
    bool empty = list.isEmpty();

    // Add AnalogChannel to pending list
    list.insert(channel);

	/* If ADC not already running, start it now */
    if (empty) {
		programNextADC();
	}
}

void AvrADC::programNextADC() {

	/* Retrieve the next ADC to perform */
    Channel* channel = list.front();

    /* Clear 'Power Reduction ADC' bit from Power Reduction Register. */
    PRR &= ~_BV(PRADC);

	/* Configure the ADC */
    ADMUX = channel->vref | channel->channel;
    ADCSRA = _BV(ADEN) | 	// ADC Enable
             _BV(ADIF) | 	// Clear ADC Interrupt Flag
             _BV(ADIE) | 	// ADC Interrupt Enable
             ADC_PRESCALER; // ADC Prescaler

    /* Start a measure */
	ADCSRA |= _BV(ADSC);
}

/*
 * ADC Conversion Complete
 * Interrupt context, we make it the shortest as possible
 */
ISR(ADC_vect)
{
    AvrADC::instance.post();
}

/*
 * ADC conversion is complete
 * Main thread context, we retrieve the ADC result
 */
void AvrADC::onFinished()
{
    // Remove the current measure from the list
    Channel *channel = list.remove(list.front());

    /* Call the channel with the ADC result */
    channel->onNewMeasure(ADC);

	/* If still some measures to do, directly program the next */
    if (!list.isEmpty()) {
		programNextADC();
	} else {
		/* Stop the ADC for power consumption */
        ADCSRA = 0;

        /* Set 'Power Reduction ADC' bit from Power Reduction Register. */
        PRR |= _BV(PRADC);
	}
}

} /* namespace octopus */

#endif /* __AVR */
