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

#ifndef EVENT_H
#define EVENT_H

#ifndef __AVR__
#include <wx/event.h>
#include <wx/thread.h>
#endif

/**
 * \brief Simple event
 *
 * This class defines the methods to post and receive an event.
 */
class Event {

public:

	/**
	 * \brief Constructor
	 */
	Event();

	/**
	 * \brief Posts this event to the event queue
	 *
	 * \param[in] what User parameter
	 *
	 * This method appends the event to the event queue if it is not already pending.
	 * The event queue looper will call the method #onEvent() in application context.
	 */
	void Post(char what = 0);

	/**
	 * \brief Handle all the pending events
	 */
	static void handlePendingEvents(void);

#ifdef __AVR__
	/**
	 * \brief Starts the event queue looper
	 *
	 * This method is called at boot, it waits for incoming events and call the onEvent() methods.
	 */
	static void startLooper(void);
#endif /* __AVR__ */

	/**
	 * \brief Virtual event handler
	 *
	 * \param[in] what User parameter
	 *
	 * Implement this method in order to handle the event.
	 */
	virtual void onEvent(char what)=0;

private:
	/**
	 * \brief First event of the linked-list of events
	 */
	static class Event* mpFirstEvent;

	/**
	 * \brief Next event of the linked-list of events
	 */
	class Event* mpNextEvent;

	/**
	 * \brief Last event of the linked-list of events
	 */
	static class Event* mpLastEvent;

	/**
	 * \brief Whether the event is pending or not
	 * An event is pending if it is present in the linked-list mpFirstEvent..mpNextEvent..mpLastEvent
	 */
	bool isPending;

	/**
	 * \brief User parameter
	 */
	char mWhat;

#ifndef __AVR__
	static wxMutex mMutex;

	/**
	 * @brief Internal event handler using wxWidgets
	 */
	class InternalHandler : public wxEvtHandler {
	public:
		InternalHandler(Event* parent);
		~InternalHandler();
		void Post();
		void OnEvent( wxCommandEvent &event );
	private:
		Event* mParent;
		bool mEventPending;
	};

	InternalHandler mInternalHandler;
#endif

	friend class InternalHandler;
};

#endif // EVENT_H
