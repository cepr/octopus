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
#include "PrincetonRf.h"
#include "PrincetonRfDecoder.h"
#include "Looper.h"

//#define DBG

#define TOLERANCE 0.25

static const unsigned short SHORT_PULSE_MIN = ((1-TOLERANCE) * SHORT_DURATION);
static const unsigned short SHORT_PULSE_MAX = ((1+TOLERANCE) * SHORT_DURATION);
static const unsigned short LONG_PULSE_MIN = ((1-TOLERANCE) * LONG_DURATION);
static const unsigned short LONG_PULSE_MAX = ((1+TOLERANCE) * LONG_DURATION);

typedef enum {
    EVENT_S0,
    EVENT_S1,
    EVENT_L0,
    EVENT_L1,
    EVENT_INVALID,
    EVENTS_COUNT
} EVENT;

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

const STATE NewStateTable[STATES_COUNT][EVENTS_COUNT] = {
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

static Handler* _this;

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
        char what;
        if ((SHORT_PULSE_MIN < duration) && (duration < SHORT_PULSE_MAX)) {
            what = previousvalue ? EVENT_S1 : EVENT_S0;
        } else if ((LONG_PULSE_MIN < duration) && (duration < LONG_PULSE_MAX)) {
            what = previousvalue ? EVENT_L1 : EVENT_L0;
        } else {
            what = EVENT_INVALID;
        }
        PostEvent(_this, what);
        previousvalue = value;
        start = now;
    }
}

void PrincetonRfDecoder::onEvent(char what) {
    /* Compute new state */
    mState = NewStateTable[mState][(int)what];
#ifdef DBG
    mListener->onRfReceived(DBG_EVENT_CHARS[(int)what]);
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
        char i;
        for (i=0; i<12; i++) {
            mListener->onRfReceived(mCode[(int)i]);
        }
        mListener->onRfReceived('\n');
        mBit = 0;
    }
#endif
}

PrincetonRfDecoder::PrincetonRfDecoder(PrincetonRfListener* listener) {
    /* Initialize variables */
    mState = STATE_INIT;
    mBit = 0;
    mListener = listener;
    mCode[12] = 0;
    /* Set GPIO in input, no pull */
    PORTD &=~ _BV(PORTD2);
    DDRD &=~ _BV(PORTD2);
    /* Activate INT0 */
    _this = this;
    //PCICR |= _BV(PCIE2);
    //PCMSK2 |= _BV(PCINT23);
    EICRA = _BV(ISC00);
    EIMSK = _BV(INT0);
}
