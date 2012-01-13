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

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread {

private:
	pthread_t mThread;

public:
	/**
	 * @brief Thread entry point.
	 */
	virtual void run() = 0;

	/**
	 * @brief Starts the new Thread of execution.
	 */
	void start();
};

#endif /* THREAD_H_ */