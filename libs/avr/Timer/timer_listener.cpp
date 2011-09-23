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

#include "timer_listener.h"
#include "Looper.h"

class TimerListener* TimerListener::mpFirstTimerListener(0);

void TimerListener::rescheduleHardwareTimer() {

	// Raise all pending timer events
	while(mpFirstTimerListener && ((mpFirstTimerListener->mTimerWhen - now()) > MAX_DELAY)) {
		// timer_after will trigger sooner than the one we want to insert in the list
		mpFirstTimerListener->onTimerLISR(mpFirstTimerListener->mTimerWhen, mpFirstTimerListener->mWhat);
		// iterate
		mpFirstTimerListener = mpFirstTimerListener->mpNextTimerListener;
	}

	if (mpFirstTimerListener) {
		OCR1A = mpFirstTimerListener->mTimerWhen;

		TIFR1 = _BV(OCF1A); // Clear output compare A match interrupt
		TIMSK1 = _BV(OCIE1A);	// Output Compare A Match Interrupt Enable

		//todo on passe bien là, et l'IT tombe au moins une fois

	} else {
		TIMSK1 = 0; // Output Compare A Match Interrupt Enable
		TIFR1 = _BV(OCF1A); // Clear output compare A match interrupt
	}
}

/**
 * TIMER1 Interrupt Service Routine
 */
ISR (TIMER1_COMPA_vect) {
	TimerListener::rescheduleHardwareTimer();
}

TimerListener::TimerListener() : mEvent(this), mTimerWhen(0), mWhat(0) {
    TCCR1A = 0; // Normal port operation
    TCCR1B = _BV(CS11); // clkIO / 8 (From prescaler)
    TIMSK1 = _BV(OCIE1A); // Output Compare A Match Interrupt Enable
}

void TimerListener::cancel(void) {

	cli();

	TimerListener* timer_previous = 0;
	TimerListener* timer_current = mpFirstTimerListener;

	// For each timer in the list...
	while(timer_current != 0) {
		if (timer_current == this) {
			// Let's remove this timer
			if (timer_previous) {
				// Current timer is not the first one
				timer_previous->mpNextTimerListener = mpNextTimerListener;
			} else {
				// Current timer is the first one
				if (mpNextTimerListener) {
					// Modifying the first timer of the list, we must reschedule hardware timer
					mpFirstTimerListener = mpNextTimerListener;
					OCR1A = mpFirstTimerListener->mTimerWhen;
				} else {
					// The list is now empty, we must mask the timer compare match interrupt
					mpFirstTimerListener = 0;
					TIMSK1 &= ~_BV(OCIE1A); // Output Compare A Match Interrupt Enable
					TIFR1 = _BV(OCF1A); // Clear output compare A match interrupt
				}
			}
			timer_current = mpNextTimerListener;
		} else {
			// Keep this timer
			timer_previous = timer_current;
			timer_current = timer_current->mpNextTimerListener;
		}
	}

	sei();
}

void TimerListener::schedule(unsigned short when, char what) {

	// We anticipate the wakeup and interrupt treatment
	when -= TIMER_OVERHEAD;

	unsigned short _now = now();

	cancel();
	mWhat = what;

	cli();

	TimerListener* timer_before = 0;
	TimerListener* timer_after = mpFirstTimerListener;

	// Search for the right place inside the chronological list of timers
	while(timer_after && ((timer_after->mTimerWhen - _now) < (when - _now))) {
		// timer_after will trigger sooner than the one we want to insert in the list
		timer_before = timer_after;
		timer_after = timer_after->mpNextTimerListener;
	}

	this->mTimerWhen = when;
	this->mpNextTimerListener = timer_after;
	if (timer_before) {
		// Current timer is not the first one
		timer_before->mpNextTimerListener = this;
	} else {
		// Current timer is the first one
		mpFirstTimerListener = this;
		rescheduleHardwareTimer();
	}

	sei();
}

void TimerListener::onTimerLISR(unsigned short when, char what) {
	PostEvent(&mEvent, what); // trigger TimerListener::onEvent()
}

TimerListener::Event::Event(TimerListener* parent) : mParent(parent) {
}

void TimerListener::Event::onEvent(char what) {
	mParent->onTimer(what);
}
