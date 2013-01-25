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

#ifdef __AVR__

#include <avr/interrupt.h>
#include <avr/io.h>
#include "princeton_rf.h"
#include "princeton_rf_decoder.h"
#include "octopus/event/event.h"
#include "octopus/event/looper.h"

using octopus::event::Looper;

//#define DBG

#define TOLERANCE 0.25

static const unsigned short SHORT_PULSE_MIN = ((1-TOLERANCE) * SHORT_DURATION);
static const unsigned short SHORT_PULSE_MAX = ((1+TOLERANCE) * SHORT_DURATION);
static const unsigned short LONG_PULSE_MIN = ((1-TOLERANCE) * LONG_DURATION);
static const unsigned short LONG_PULSE_MAX = ((1+TOLERANCE) * LONG_DURATION);

#ifdef DBG
static const char DBG_EVENT_CHARS[] = {
    '.',
    '\'',
    '_',
    '-',
    'x'
};
#endif

#ifdef DBG
static const char DBG_STATE_CHARS[] = {
    'I',
    'S',
    '2',
    '3',
    '0',
    '4',
    'F',
    'L',
    '5',
    '6',
    '1'
};
#endif

const PrincetonRfDecoder::STATE PrincetonRfDecoder::NewStateTable[PrincetonRfDecoder::STATES_COUNT][PrincetonRfDecoder::EVENTS_COUNT] = {
    /*                      EVENT_S0,   EVENT_S1,   EVENT_L0,   EVENT_L1,   EVENT_INVALID */
    /* -----------------------------------------------------------------------------------*/
    /* STATE_INIT */    {   STATE_INIT, STATE_S,    STATE_INIT, STATE_L,    STATE_INIT},
    /* STATE_S    */    {   STATE_INIT, STATE_INIT, STATE_SL,   STATE_INIT, STATE_INIT},
    /* STATE_SL   */    {   STATE_INIT, STATE_SLS,  STATE_INIT, STATE_SLL,  STATE_INIT},
    /* STATE_SLS  */    {   STATE_INIT, STATE_INIT, STATE_BIT0, STATE_INIT, STATE_INIT},
    /* STATE_BIT0 */    {   STATE_INIT, STATE_S,    STATE_INIT, STATE_L,    STATE_INIT},
    /* STATE_SLL  */    {   STATE_BITF, STATE_INIT, STATE_INIT, STATE_INIT, STATE_INIT},
    /* STATE_BITF */    {   STATE_INIT, STATE_S,    STATE_INIT, STATE_L,    STATE_INIT},
    /* STATE_L    */    {   STATE_LS,   STATE_INIT, STATE_INIT, STATE_INIT, STATE_INIT},
    /* STATE_LS   */    {   STATE_INIT, STATE_INIT, STATE_INIT, STATE_LSL,  STATE_INIT},
    /* STATE_LSL  */    {   STATE_BIT1, STATE_INIT, STATE_INIT, STATE_INIT, STATE_INIT},
    /* STATE_BIT1 */    {   STATE_INIT, STATE_S,    STATE_INIT, STATE_L,    STATE_INIT}
};

static PrincetonRfDecoder* thiz;

/* Pin Change Interrupt Request 0 */
ISR(INT0_vect) {
    unsigned short now = TCNT1;
    static unsigned short start = 0;
    unsigned char value = PIND & _BV(PORTD2);
    static unsigned char previousvalue = 0;
    if (value != previousvalue) {
        /* Pin has changed, compute duration */
        unsigned short duration = now - start;
        /* Try to decode pulse */
        if ((SHORT_PULSE_MIN < duration) && (duration < SHORT_PULSE_MAX)) {
        	thiz->mEvent = previousvalue ? PrincetonRfDecoder::EVENT_S1 : PrincetonRfDecoder::EVENT_S0;
        } else if ((LONG_PULSE_MIN < duration) && (duration < LONG_PULSE_MAX)) {
        	thiz->mEvent = previousvalue ? PrincetonRfDecoder::EVENT_L1 : PrincetonRfDecoder::EVENT_L0;
        } else {
        	thiz->mEvent = PrincetonRfDecoder::EVENT_INVALID;
        }
        Looper::get()->insert(thiz);
        previousvalue = value;
        start = now;
    }
}

void PrincetonRfDecoder::onEvent() {
    /* Compute new state */
    mState = NewStateTable[mState][mEvent];
#ifdef DBG
    mListener->onRfReceived(DBG_EVENT_CHARS[mEvent]);
    mListener->onRfReceived(DBG_STATE_CHARS[mState]);
#else
    switch(mState) {
    case STATE_BIT0:
        mCode[(int)mBit++]='0';
        break;
    case STATE_BIT1:
        mCode[(int)mBit++]='1';
        break;
    case STATE_BITF:
        mCode[(int)mBit++]='.';
        break;
    case STATE_INIT:
        mBit = 0;
        break;
    default:
    	return;
    }
    if (mBit == 12) {
        int i;
        for (i=0; i<12; i++) {
            mListener->onRfReceived(mCode[i]);
        }
        mListener->onRfReceived('\n');
        mBit = 0;
    }
#endif
}

PrincetonRfDecoder::PrincetonRfDecoder(Listener* listener) :
		mState(STATE_INIT),
		mEvent(EVENT_INVALID),
		mBit(0),
		mListener(listener) {
    /* Set GPIO in input, no pull */
    PORTD &=~ _BV(PORTD2);
    DDRD &=~ _BV(PORTD2);
    /* Activate INT0 */
    thiz = this;
    //PCICR |= _BV(PCIE2);
    //PCMSK2 |= _BV(PCINT23);
    EICRA = _BV(ISC00);
    EIMSK = _BV(INT0);
}

#endif /* __AVR__ */
