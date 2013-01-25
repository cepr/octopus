/*
 * Copyright 2012 Cedric Priscal
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

#ifndef APPLICATIONTIMER_H
#define APPLICATIONTIMER_H

#ifdef __AVR__

#include "system_timer.h"
#include "octopus/event/event.h"
#include "octopus/event/looper.h"

/**
 * \brief Provides a timer for long tasks.
 */
class ApplicationTimer : public SystemTimer
{

protected:

	/**
	 * \brief Constructor
	 */
	ApplicationTimer();

	/**
	 * \brief Timer event handler
	 *
	 * This method is called when the timer event raises.
	 *
	 * You should override the method in a child class in order to perform time-consuming
	 * treatment of the event.
	 *
	 * \see #schedule()
	 */
	virtual void onTimer() = 0;

private:
	void onTimerLISR(unsigned short when);

	class TimerEvent : public octopus::event::Looper::Item
	{
	public:
		TimerEvent(ApplicationTimer* parent);
	private:
		ApplicationTimer* mParent;
		void onEvent();
	};

	TimerEvent mEvent;
};

#endif /* __AVR__ */

#endif // APPLICATIONTIMER_H
