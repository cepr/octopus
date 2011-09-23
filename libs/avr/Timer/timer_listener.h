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

#ifndef TIMERLISTENER_H
#define TIMERLISTENER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Handler.h"

extern "C" void TIMER1_COMPA_vect(void);

/**
 * \brief Abstract base class for all classes that need a timer.
 */
class TimerListener {

public:

	/**
	 * \brief Timer event handler
	 *
	 * \param[in] what User parameter that was passed to #schedule()
	 * 
	 * This method is called when the timer event raises.
	 *
	 * You should override the method in a child class in order to perform time-consuming
	 * treatment of the event.
	 *
	 * \see #onTimerLISR(), #schedule()
	 */
	virtual void onTimer(char what = 0) {
		// default empty implementation
	}

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
	 * If you override this method, #onTimer() will not be called anymore.
	 *
	 * For longer operation, please override #onTimer().
	 *
	 * \see #onTimer(), #schedule()
	 */
	virtual void onTimerLISR(unsigned short when, char what = 0);

	/**
	 * \brief Schedules a timer event
	 *
	 * \param[in] when Timer event absolute time in microseconds. It should not be higher than now() + MAX_DELAY.
	 * \param[in] what User parameter to pass to #onTimerLISR() or #onTimer()
	 *
	 * Call this method to trigger a timer event. The method #onTimer() will be called
	 * to trigger this timer event.
	 * Any pending event of this timer is replaced by the new one.
	 *
	 * \param[in] when Absolute time when to trigger the timer event
	 */
	void schedule(unsigned short when, char what = 0);

	/**
	 * \brief Maximum delay of a timer event in microseconds
	 * \see #schedule()
	 */
	static const unsigned short MAX_DELAY = 60000;

	/**
	 * \brief Interrupt overhead delay in microseconds
	 */
	static const unsigned short TIMER_OVERHEAD = 5;	// TODO Determine TIMER_OVERHEAD

	/**
	 * \brief Cancels the timer event
	 */
	void cancel(void);

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
	TimerListener();

private:

	class Event : public Handler {
	public:
		Event(TimerListener *parent);
	private:
		TimerListener *mParent;
		/**
		 * \brief Triggered by onTimerLISR()
		 * \param what Unused parameter
		 */
		void onEvent(char what);
	};

	Event mEvent;

	/**
	 * \brief First timer of the linked-list
	 */
	static class TimerListener* mpFirstTimerListener;

	/**
	 * \brief Next timer of the linked-list
	 */
	class TimerListener* mpNextTimerListener;

	/**
	 * \brief Absolute event time in microseconds of this timer
	 */
	unsigned short mTimerWhen;

	static void rescheduleHardwareTimer();

	char mWhat;
};

#endif /* TIMERLISTENER_H */
