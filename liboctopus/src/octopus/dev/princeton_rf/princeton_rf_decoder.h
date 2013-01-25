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

#include "octopus/event/event.h"
#include "octopus/event/looper.h"

class PrincetonRfDecoder: public octopus::event::Looper::Item {

public:

	/**
	 * \brief Callback interface
	 */
	class Listener {
	public:
	    virtual void onRfReceived(char code) = 0;
	};

    /**
     * \brief Constructor
     */
    PrincetonRfDecoder(Listener* listener);

    /* From Looper::Item */
    void onEvent();

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

    typedef enum {
        EVENT_S0,
        EVENT_S1,
        EVENT_L0,
        EVENT_L1,
        EVENT_INVALID,
        EVENTS_COUNT
    } EVENT;

    static const STATE NewStateTable[STATES_COUNT][EVENTS_COUNT];

	STATE mState;
	EVENT mEvent;

private:
    char mBit;
    char mCode[13];
    Listener* mListener;

};

#endif /* PT2272_H_ */
