/*
 * Copyright 2010-2011 Cedric Priscal
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

#include "analog_channel.h"
#include "analog_to_digital_converter.h"

AnalogChannel::AnalogChannel(CHANNEL channel, VREF vref) : mTimer(this) {
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

AnalogChannel::Timer::Timer(AnalogChannel* parent) : mParent(parent) {
}

void AnalogChannel::startOneShot() {
    mMs = mPeriod = 0;
    AnalogToDigitalConverter::getInstance()->startADC(this);
}

void AnalogChannel::startPeriodic(unsigned short period) {
    mMs = mPeriod = period;
    mTimer.schedule(Timer::now() + 1000);
}

void AnalogChannel::stop() {
    mMs = mPeriod = 0;
}

void AnalogChannel::Timer::onTimer(char what) {
    if (mParent->mPeriod) {
        /* 1ms has been elapsed */
        mParent->mMs--;
        if (!mParent->mMs) {
            /* The period has been elapsed,
             * we can launch a new measure.
             */
            mParent->mMs = mParent->mPeriod;
            //gAnalogToDigitalConverter.startADC(this);
            AnalogToDigitalConverter::getInstance()->startADC(mParent);
        }
        /* Reprogram timer for 1ms from now */
        schedule(now() + 1000);
    }
}

#endif /* __AVR */
