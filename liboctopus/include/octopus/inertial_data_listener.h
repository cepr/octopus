/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INERTIALDATALISTENER_H
#define INERTIALDATALISTENER_H

#include <stdint.h>

/**
 * \brief Inertial data listener.
 *
 * Implement this class to receive inertial data from a InertialDataProvider.
 *
 * \see InertialDataProvider::getInertialData()
 */
class InertialDataListener {

public:
    /**
     * @brief Listener called by an InertialDataProvider when a new inertial
     *        measure is available.
     * 
     * @param[in] gyrox todo
     * @param[in] gyroy todo
     * @param[in] gyroz todo
     */
    virtual void onNewInertialData(int16_t gyrox, int16_t gyroy, int16_t gyroz) = 0;

    /**
     * @brief Called when the inertial data cannot be retreived
     *
     * @param error_code  Internal error code for debug purpose
     */
    virtual void onInertialError(uint8_t error_code) = 0;
};

#endif // INERTIALDATALISTENER_H
