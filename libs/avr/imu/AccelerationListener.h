/*
 * Copyright 2010-1011 Cedric Priscal
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

#ifndef ACCELERATION_LISTENER_H_
#define ACCELERATION_LISTENER_H_

/**
 * \class AccelerationListener
 * \file AccelerationListener.h
 * \brief Listener interface for acceleration events.
 */
class AccelerationListener: public Listener {

    /**
     * \brief Called when a single acceleration event greater than a
     *        specified threshold is detected.
     */
    virtual void onSingleTap(void) = 0;

    /**
     * \brief Called when a double acceleration event greater than a
     *        specified threshold is detected.
     */
    virtual void onDoubleTap(void) = 0;

    /**
     * \brief Called when acceleration gets higher than a specified
     *        threshold.
     */
    virtual void onActivity(void) = 0;

    /**
     * \brief Called when acceleration gets lower than a specified
     *        threshold.
     */
    virtual void onInactivity(void) = 0;

    /**
     * \brief Called when acceleration gets lower than a specified
     *        threshold.
     */
    virtual void onFreeFall(void) = 0;

}

#endif /* ACCELERATION_LISTENER_H_ */