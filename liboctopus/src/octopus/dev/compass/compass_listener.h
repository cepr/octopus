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

#ifndef COMPASSLISTENER_H
#define COMPASSLISTENER_H

/**
 * \brief Compass event listener.
 *
 * Implement this class to receive compass events.
 *
 * \see CompassProvider::getHeading()
 */
class CompassListener {

public:
    /**
     * \brief Listener called by a CompassProvider when a new heading measure is available.
     *
     * \param[in] heading Heading in 1/10 degrees, from 0 to 3599.
     */
	virtual void onNewHeading(unsigned short heading) = 0;

};

#endif // COMPASSLISTENER_H
