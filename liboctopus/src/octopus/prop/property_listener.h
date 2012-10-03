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

#ifndef PROPERTYLISTENER_H_
#define PROPERTYLISTENER_H_

class PropertyListener;

#include "property.h"

/**
 * @brief Listener.
 */
class PropertyListener {

public:
    /**
     * Origin of a property modification.
     * 
     * @see #onPropertyChanged()
     */
    typedef enum {
        ORIGIN_LOCAL, /**< The property has been modified localy, for example by a direct affectation. */
        ORIGIN_REMOTE /**< The property has been modified remotely. */
    } ORIGIN;

	/**
	 * Method called when a property has changed
	 *
	 * @param[in,out] prop    The changed property
	 * @param[in]     what    Elements that have changed
     * @param[in]     origin  Origin of the modification
	 */
	virtual void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin) = 0;

	/**
	 * @brief Method called when a property has a new child
	 *
	 * @param[in,out] prop  The parent property
	 * @param[in,out] child The new-born child
	 * @param[in]     index The index of the child in the parent children list
	 */
	virtual void onNewChild(Property* prop, Property* child, unsigned char index) {};

	/**
	 * @brief Method called when a property is no more available
	 */
	virtual void onPropertyDeleted() {};
};

#endif /* PROPERTYLISTENER_H_ */
