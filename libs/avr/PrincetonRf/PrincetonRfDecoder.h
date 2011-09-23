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

#ifndef PT2272_H_
#define PT2272_H_

#include "Handler.h"

class PrincetonRfListener {
public:
    virtual void onRfReceived(char code);
};

typedef enum {
    STATE_INIT,
    STATE_S,
    STATE_SL,
    STATE_SLS,
    STATE_BIT0,
    STATE_SLL,
    STATE_BITF,
    STATE_L,
    STATE_LS,
    STATE_LSL,
    STATE_BIT1,
    STATES_COUNT
} STATE;

class PrincetonRfDecoder: public Handler {
	STATE mState;
    char mBit;
    char mCode[13];
    PrincetonRfListener* mListener;
public:
    PrincetonRfDecoder(PrincetonRfListener* listener);
    /* From Handler */
    void onEvent(char what);
};

#endif /* PT2272_H_ */
