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
#include <avr/sleep.h>
#include "Looper.h"
#include "fatal.h"
#include "Robot/Robot.h"

#define MAX_EVENTS 24

static const Handler* mHandlers[MAX_EVENTS];
static char mWhats[MAX_EVENTS];
static volatile char mCount = 0;

void PostEvent(const Handler* handler, char what) {
    static int mPushIndex = 0;
    if (mCount < MAX_EVENTS) {
        mHandlers[mPushIndex] = handler;
        mWhats[mPushIndex] = what;
        mPushIndex++;
        if (mPushIndex == MAX_EVENTS) {
            mPushIndex = 0;
        }
        mCount++;
    } else {
        fatal(FATAL_LOOPER_OVERFLOW);
    }
}

int main(void) {
    int mPullIndex = 0;
    sei();

    /* Start Robot */
    gRobot->onStart();

    /* Process messages queue, and sleep */
    for (;;) {
        while(mCount == 0) {
//          set_sleep_mode(SLEEP_MODE_IDLE);
//          sleep_enable();
//          sleep_cpu();
//          sleep_disable();
        }
        const Handler *handler = mHandlers[mPullIndex];
        char what = mWhats[mPullIndex];
        mPullIndex++;
        if (mPullIndex == MAX_EVENTS) {
            mPullIndex = 0;
        }
        cli();
        mCount--;
        sei();
        ((Handler*)handler)->onEvent(what);
    }
    return 0;
}
