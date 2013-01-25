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

#ifndef PT2262_H_
#define PT2262_H_

#ifdef __AVR

#include "princeton_rf.h"
#include "octopus/dev/timer/system_timer.h"

class PrincetonRfEncoder : public SystemTimer {
private:
    char mPin;
    // Address is 8 bits long, which corresponds to 8*4=32 pulses.
    unsigned long mRawAddress;
    // Data is 4 bits long, which corresponds to 4*4=16 pulses.
    unsigned short mRawData;
    // mState==0 : sending address
    // mState==1 : sending data
    // mState==2 : sending SYNC1
    // mState==3 : sending SYNC2
    char mState;
    // mIndex corresponds to the offset inside mRawAddress or mRawData
    int mIndex;
    // mRepeat corresponds to the number of bursts to send
    char mRepeat;
public:
    PrincetonRfEncoder(char pin);
    void send(tristate address, tristate data);
    void onTimerLISR(unsigned short when);
};

#endif /* __AVR */

#endif /* PT2262_H_ */
