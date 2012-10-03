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

#include "event.h"

#ifdef __AVR__
#include <avr/interrupt.h>
#include <avr/sleep.h>
#endif

// static initialization
Event* Event::mpFirstEvent = 0;
Event* Event::mpLastEvent = 0;

Event::Event() :
		mpNextEvent(0),
		isPending(false),
		mWhat(0)
#ifndef __AVR__
		,mInternalHandler(this)
#endif
{
}

void Event::Post(char what)
{
#ifdef __AVR__
	unsigned char sreg = SREG;
	cli();
#else
	mMutex.Lock();
#endif
	mWhat = what;
	if (!isPending) {
		// The event is not already pending, we can append it to the list
		isPending = true;
		mpNextEvent = 0;
		if (mpLastEvent) {
			// The list is not empty, we must modify the last element of the list
			mpLastEvent->mpNextEvent = this;
		} else {
			// The list is empty, we must modify the first element of the list
			mpFirstEvent = this;
		}
		// The last element of the list is this event
		mpLastEvent = this;
#ifndef __AVR__
		// On wxWidgets, we have to trigger the InternalHandler
		mInternalHandler.Post();
#endif
	}
#ifdef __AVR__
	SREG = sreg;
#else
	mMutex.Unlock();
#endif
}

void Event::handlePendingEvents(void) {
	while (mpFirstEvent) {
		// Remove first event from list
#ifdef __AVR__
		cli();
#else
		mMutex.Lock();
#endif
		Event* ev = mpFirstEvent;
		if ((mpFirstEvent = mpFirstEvent->mpNextEvent) == 0) {
			// List is empty
			mpLastEvent = 0;
		}
		ev->isPending = false;
		char what = ev->mWhat;
#ifdef __AVR__
		sei();
#else
		mMutex.Unlock();
#endif
		// Call onEvent method
		ev->onEvent(what);
	}
}

#ifdef __AVR__
void Event::startLooper(void) {
	// For ad vitam aeternam:
	for(;;) {
		handlePendingEvents();
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_enable();
		sleep_cpu();
		sleep_disable();
	}
}
#endif /* __AVR__ */

#ifndef __AVR__

DEFINE_EVENT_TYPE(wxEVT_OCTOPUS_EVENT)

wxMutex Event::mMutex;

Event::InternalHandler::InternalHandler(Event* parent) :
		mParent(parent),
		mEventPending(false)
{
	Connect(wxEVT_OCTOPUS_EVENT, wxCommandEventHandler(Event::InternalHandler::OnEvent));
}

Event::InternalHandler::~InternalHandler()
{
	Disconnect(wxEVT_OCTOPUS_EVENT, wxCommandEventHandler(Event::InternalHandler::OnEvent));
}

void Event::InternalHandler::Post()
{
	if (!mEventPending) {
		mEventPending = true;
		wxCommandEvent event( wxEVT_OCTOPUS_EVENT );
		AddPendingEvent(event);
	}
}

void Event::InternalHandler::OnEvent(wxCommandEvent& event)
{
	mEventPending = false;
	mParent->handlePendingEvents();
}

#endif
