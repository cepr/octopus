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

#ifndef INERTIALDATALISTENER_H
#define INERTIALDATALISTENER_H

#include "Listener.h" // Base class: Listener

/**
 * \brief Inertial data listener.
 *
 * Implement this class to receive inertial data from a InertialDataProvider.
 *
 * \see InertialDataProvider::getInertialData()
 */
class InertialDataListener : public Listener {

public:
    /**
     * \brief Listener called by an InertialDataProvider when a new inertial
     *        measure is available.
     * 
     * \param[in] gyrox todo
     * \param[in] gyroy todo
     * \param[in] gyroz todo
     */
	virtual void onNewInertialData(short gyrox, short gyroy, short gyroz) = 0;

};

#endif // INERTIALDATALISTENER_H
