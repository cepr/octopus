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

#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

extern "C" void TIMER1_COMPA_vect(void);

/**
 * \brief Provides a timer for short tasks.
 *
 * This class provides a timer for executing code at specified time.
 * To use this function, override the method SystemTimer#onTimerLISR()
 * with the code you want to execute, and call SystemTimer#schedule()
 * to program its execution.
 *
 * SystemTimer#onTimerLISR() will be called in interrupt context, so
 * you should avoid any time consumming treatment. To execute such
 * time-consumming functions, you should use an AppTimer instead.
 *
 * \see AppTimer
 */
class SystemTimer {

public:
	/**
	 * \brief Schedules the timer
	 *
	 * \param[in] when Timer event absolute time in microseconds. It should not be higher than now() + MAX_DELAY.
	 * \param[in] what User parameter to pass to #onTimerLISR().
	 *
	 * Call this method to trigger a timer event. The method #onTimerLISR() will be called
	 * to trigger this timer event.
	 * Any pending scheduling of this timer will be replaced by this new one.
	 */
	void schedule(unsigned short when, char what = 0);

	/**
	 * \brief Maximum delay of a timer event in microseconds
	 * \see #schedule()
	 */
	static const unsigned short MAX_DELAY = 60000;

	/**
	 * \brief Cancels the timer event
	 * 
	 * \warning Cannot be called from interrupt context.
	 */
	inline void cancel(void) {
		cli();
		cancelUnsafe();
		sei();
	}

	/**
	 * \brief Cancels the timer event
	 * 
	 * This function must be called with masked interrupt
	 */
	void cancelUnsafe(void);

	/**
	 * \brief Get absolute time
	 *
	 * \return Absolute time in microseconds
	 */
	static inline unsigned short now() {
		return TCNT1;
	}

	friend void TIMER1_COMPA_vect(void);

protected:
	/**
	 * \brief Constructor
	 */
	SystemTimer();

	/**
	 * \brief Low-latency timer event handler
	 *
	 * \param[in] when Timer event absolute time in microseconds
	 * \param[in] what User parameter that was passed to #schedule()
	 *
	 * This method is called from hardware timer interrupt context.
	 * It ensures a very low latency, but the handler should be the shortest as possible to
	 * not delay any other pending interrupt.
	 *
	 * For longer operation, please notify the application using an event.
	 *
	 * \see #schedule()
	 */
	virtual void onTimerLISR(unsigned short when, char what = 0) = 0;

private:

	/**
	 * \brief Internal scheduler overhead delay in microseconds
	 *
	 * This delay must be determined this way:
	 * - build a program with SCHEDULER_OVERHEAD set to 0
	 * - program a timer to trigger an event at now()+1
	 * - if the event actually trigger 65537 us later, you should increase SCHEDULER_OVERHEAD and retry
	 *
	 * SCHEDULER_OVERHEAD must be determined with TIMER_OVERHEAD set to 0
	 */
	static const unsigned short SCHEDULER_OVERHEAD = 0; // TODO Determine SCHEDULER_OVERHEAD

	/**
	 * \brief Interrupt overhead delay in microseconds
	 *
	 * This delay must be determined this way:
	 * - build a program with TIMER_OVERHEAD set to 0
	 * - program a timer to trigger an event at T0
	 * - in onTimerLISR() method, call the method now() and compute TIMER_OVERHEAD = now() - T0
	 */
	static const unsigned short TIMER_OVERHEAD = 0;	// TODO Determine TIMER_OVERHEAD

	/**
	 * \brief First timer of the linked-list
	 */
	static class SystemTimer* mpFirstTimerListener;

	/**
	 * \brief Next timer of the linked-list
	 */
	class SystemTimer* mpPreviousTimerListener;

	/**
	 * \brief Next timer of the linked-list
	 */
	class SystemTimer* mpNextTimerListener;

	/**
	 * \brief Last timer of the linked-list
	 */
	static class SystemTimer* mpLastTimerListener;

	/**
	 * \brief Absolute event time in microseconds of this timer
	 */
	unsigned short mTimerWhen;

	static void rescheduleHardwareTimer();

	char mWhat;
};

#endif /* SYSTEM_TIMER_H */
