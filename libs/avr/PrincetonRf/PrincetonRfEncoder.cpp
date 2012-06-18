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
#include "PrincetonRfEncoder.h"

PrincetonRfEncoder::PrincetonRfEncoder(char pin) {
    mPin = pin;
    mCode = 0;
    /* Set pin as output 0 */
    PORTD &= ~_BV(pin);
    DDRD |= _BV(mPin);
}

void PrincetonRfEncoder::send(tristate address, tristate data) {
    char i;

    PORTD &= ~_BV(mPin);

    // Address is sent from A0 to A7
    mRawAddress = 0;
    for (i=0; i<32; i+=4) {
        if (address.mask & 1) {
            if (address.value & 1) {
                // It is a 1
                mRawAddress |= ((unsigned long)5) << i;
            } else {
                // It is a 0
                mRawAddress |= ((unsigned long)10) << i;
            }
        } else {
            // It is a F
            mRawAddress |= ((unsigned long)6) << i;
        }
        address.mask >>= 1;
        address.value >>= 1;
    }

    // Data is sent from D3 to D0
    mRawData = 0;
    for (i=0; i<16; i+=4) {
        if (data.mask & 8) {
            if (data.value & 8) {
                // It is a 1
                mRawData |= 5 << i;
            } else {
                // It is a 0
                mRawData |= 10 << i;
            }
        } else {
            // It is a F
            mRawData |= 6 << i;
        }
        data.mask <<= 1;
        data.value <<= 1;
    }

    mState = 0;
    mIndex = 0;
    mRepeat = 50;
    mCode++;
    onTimerLISR(mCode, now());
}

void PrincetonRfEncoder::onTimerLISR(unsigned short when, char what) {
    if (what == mCode) {
        /* Switch output */
        PORTD ^= _BV(mPin);

        /* Program timer for next switch */
        switch(mState) {
        case 0:
            // Sending address
            if ((mRawAddress>>mIndex) & 1) {
                when += LONG_DURATION;
            } else {
                when += SHORT_DURATION;
            }
            mIndex++;
            if (mIndex == 32) {
                mIndex = 0;
                mState = 1;
            }
            break;
        case 1:
            // Sending data
            if ((mRawData>>mIndex) & 1) {
                when += LONG_DURATION;
            } else {
                when += SHORT_DURATION;
            }
            mIndex++;
            if (mIndex == 16) {
                mIndex = 0;
                mState = 2;
            }
            break;
        case 2:
            // Sending SYNC1
            when += SYNC_HIGH_DURATION;
            mState = 3;
            break;
        case 3:
            // Sending SYNC2
            when += SYNC_LOW_DURATION;
            mState = 0;
            if (!--mRepeat) {
                return;
            }
            break;
        }
        schedule(when, what);
    }
}
