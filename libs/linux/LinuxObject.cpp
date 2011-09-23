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

#include "LinuxObject.h"
#include <string.h>
#include <time.h>
#include <sys/time.h>

LinuxObject::LinuxObject() {
	pthread_cond_init(&mCond, NULL);
	pthread_mutex_init(&mMutex, NULL);
}

void LinuxObject::notify() {
	pthread_mutex_lock(&mMutex);
	pthread_cond_signal(&mCond);
	pthread_mutex_unlock(&mMutex);
}

void LinuxObject::wait() {
	pthread_mutex_lock(&mMutex);
	pthread_cond_wait(&mCond, &mMutex);
	pthread_mutex_unlock(&mMutex);
}

void LinuxObject::wait(long millis) {
	struct timeval now;
	struct timespec timeout;
	gettimeofday(&now, NULL);
	timeout.tv_sec = now.tv_sec + (millis / 1000);
	timeout.tv_nsec = (now.tv_usec + (millis % 1000) * 1000) * 1000;
	pthread_mutex_lock(&mMutex);
	pthread_cond_timedwait(&mCond, &mMutex, &timeout);
	pthread_mutex_unlock(&mMutex);
}
