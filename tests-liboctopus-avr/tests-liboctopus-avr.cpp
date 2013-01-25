/*
 * Copyright 2013 Cedric Priscal
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

#include "octopus/event/looper.h"
#include "octopus/util/fatal.h"
#include "octopus/dev/timer/application_timer.h"

using octopus::event::Looper;

// TEST 1

class TestEvent : public Looper::Item {
public:
	TestEvent(Looper::Item* next): next(next) {
	}
	void onEvent() {
		if (next) {
			Looper::get()->insert(next);
		} else {
			fatal(FATAL_DEBUG);
		}
	}
private:
	Looper::Item* next;
};

static void TEST1() {
	TestEvent ev3(0);
	TestEvent ev2(&ev3);
	TestEvent ev1(&ev2);
	Looper::get()->insert(&ev1);
	Looper::get()->run();
}

// TEST 2

class TestSystemTimer : public SystemTimer {
public:
	TestSystemTimer() : cnt(0) {
	}
	void onTimerLISR(unsigned short when) {
		fatal(FATAL_DEBUG);
/*		schedule(when + 1000);
		cnt++;
		if (cnt == 10000) {
			// 10 seconds have elapsed
			fatal(FATAL_DEBUG);
		}*/
	}
private:
	unsigned short cnt;
};

static void TEST2() {
	TestSystemTimer timer;
	timer.schedule(SystemTimer::now()+1000);
	for(;;){}
	//Looper::get()->run();
}

// TEST 3

class TestApplicationTimer : public ApplicationTimer {
public:
	TestApplicationTimer() : cnt(0) {
	}
	void onTimer() {
		schedule(now() + 1000);
		cnt++;
		if (cnt == 10000) {
			// 10 seconds have elapsed
			fatal(FATAL_DEBUG);
		}
	}
private:
	unsigned short cnt;
};

static void TEST3() {
	TestApplicationTimer timer;
	timer.schedule(SystemTimer::now()+1000);
	Looper::get()->run();
}

int main() {
	//TEST1();
	TEST2();
	//TEST3()
	return 0;
}
