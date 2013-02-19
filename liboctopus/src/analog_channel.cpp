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

#include "octopus/analog_channel.h"
#include "octopus/analog_to_digital_converter.h"
#include "octopus/avr_timer.h"

namespace octopus {

AnalogChannel::AnalogChannel(CHANNEL channel, VREF vref) {
    mChannel = channel;
    mVref = vref;
	mMs = 0;
	mPeriod = 0;
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

void AnalogChannel::startOneShot() {
    mPeriod = 0;
    AnalogToDigitalConverter::getInstance()->startADC(this);
}

void AnalogChannel::startPeriodic(Timer::time_us_t period) {
    mPeriod = period;
    mTimer.schedule(Timer::now() + 1000);
}

void AnalogChannel::stop() {
    mPeriod = 0;
}

void AnalogChannel::run(time_us_t when, char what)
{
    if (mPeriod) {
        // Start a measure
        AnalogToDigitalConverter::getInstance()->startADC(this);

        // Relaunch the timer
        AvrTimer::instance.schedule(this, when + mPeriod);
    }
}

} /* namespace octopus */

#endif /* __AVR */
