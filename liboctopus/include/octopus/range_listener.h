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

#ifndef RANGELISTENER_H
#define RANGELISTENER_H

/**
 * \brief Range event listener.
 *
 * Implement this class to receive range events.
 *
 * \see RangeProvider::getRange()
 */
class RangeListener {

public:
    /**
     * \brief Listener called by a RangeProvider when a new range measure is available.
     *
     * \param[in] range Range in centimeters.
     */
	virtual void onNewRange(unsigned short range) = 0;

};

#endif // RANGELISTENER_H
