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

#ifndef RANGEFINDERPROVIDER_H
#define RANGEFINDERPROVIDER_H

#include "range_listener.h"

/**
 * \brief Base class for range finder devices.
 */
class RangeProvider {

public:
	/**
	 * \brief Trigger a single range measure.
	 *
     * \param[in] listener Listener to be called when the measure is finished.
	 */
	virtual void getRange(RangeListener *listener) = 0;

};

#endif // RANGEFINDERPROVIDER_H
