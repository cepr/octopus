/*
 * Copyright 2010-2012 Cedric Priscal
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

#include "system_timer.h"

class SystemTimer* SystemTimer::mFirstSystemTimer(0);
class SystemTimer* SystemTimer::mLastSystemTimer(0);

void SystemTimer::rescheduleHardwareTimer() {

	// Raise all pending timer events
	// The test "> MAX_DELAY" should be read as "< 0" because the operation is performed on
	// unsigned shorts (a negative signed value corresponds to a huge unsigned value).
	while(mFirstSystemTimer && ((mFirstSystemTimer->mTimerWhen - now()) > MAX_DELAY)) {

		SystemTimer* timer = mFirstSystemTimer;

		// remove timer from the list
		mFirstSystemTimer = mFirstSystemTimer->mNextSystemTimer;
        if (mFirstSystemTimer) {
            mFirstSystemTimer->mPreviousSystemTimer = 0;
        } else {
			mLastSystemTimer = 0;
		}
        timer->mPreviousSystemTimer = 0;
        timer->mNextSystemTimer = 0;
 
		// Raise user timer event
		timer->onTimerLISR(timer->mTimerWhen, timer->mWhat);
	}

	if (mFirstSystemTimer) {
		// We add SCHEDULER_OVERHEAD to the timer to not miss one complete timer cycle (65536 us).
		OCR1A = mFirstSystemTimer->mTimerWhen + SCHEDULER_OVERHEAD;
		TIFR1 = _BV(OCF1A); // Clear output compare A match interrupt
		TIMSK1 = _BV(OCIE1A);	// Output Compare A Match Interrupt Enable
	} else {
		TIMSK1 = 0; // Output Compare A Match Interrupt Enable
		TIFR1 = _BV(OCF1A); // Clear output compare A match interrupt
	}
}

/**
 * TIMER1 Interrupt Service Routine
 */
ISR (TIMER1_COMPA_vect) {
	SystemTimer::rescheduleHardwareTimer();
}

SystemTimer::SystemTimer() : mPreviousSystemTimer(0), mNextSystemTimer(0), mTimerWhen(0), mWhat(0) {
    TCCR1A = 0; // Normal port operation
#if (F_CPU == 8000000L)
    TCCR1B = _BV(CS11); // clkIO / 8 (From prescaler)
#else
# error Unknown CPU frequency
#endif
}

void SystemTimer::cancelUnsafe(void) {

	if (mNextSystemTimer) {
		// Timer is not the last one
		mNextSystemTimer->mPreviousSystemTimer = mPreviousSystemTimer;
	} else if (mLastSystemTimer == this) {
        // Timer is the last one
        mLastSystemTimer = mPreviousSystemTimer;
	}

	if (mPreviousSystemTimer) {
		// Timer is not the first one
		mPreviousSystemTimer->mNextSystemTimer = mNextSystemTimer;
	} else if (mFirstSystemTimer == this) {
		// Modifying the first timer of the list, we must reschedule hardware timer
		mFirstSystemTimer = mNextSystemTimer;
		rescheduleHardwareTimer();
	}

}

void SystemTimer::schedule(unsigned short when, char what) {

	// We anticipate the wakeup and interrupt treatment
	when -= TIMER_OVERHEAD;

	unsigned short _now = now();

	unsigned char sreg = SREG;
	cli();

	cancelUnsafe();
	mTimerWhen = when;
	mWhat = what;

	SystemTimer* timer = mFirstSystemTimer;

	// Search for the right place inside the chronological list of timers
	while(timer && ((timer->mTimerWhen - _now) < (when - _now))) {
		// timer_after will trigger sooner than the one we want to insert in the list
		timer = timer->mNextSystemTimer;
	}
	mNextSystemTimer = timer;

	if (timer) {
		// We must insert ourself between 'timer->mpPreviousTimer' and 'timer'
		mPreviousSystemTimer = timer->mPreviousSystemTimer;
		timer->mPreviousSystemTimer = this;
		if (mPreviousSystemTimer) {
			// Not the first of the list
			mPreviousSystemTimer->mNextSystemTimer = this;
		} else {
			// First timer of the list
			mFirstSystemTimer = this;
			rescheduleHardwareTimer();
		}
	} else {
		// We must append ourself at the end of the list
		mPreviousSystemTimer = mLastSystemTimer;
		mLastSystemTimer = this;
		if (mPreviousSystemTimer) {
			// The list is not empty
			mPreviousSystemTimer->mNextSystemTimer = this;
		} else {
			// The list was empty
			mFirstSystemTimer = this;
			rescheduleHardwareTimer();
		}
	}

	// Restore interrupt mask
	SREG = sreg;
}
