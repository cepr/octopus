/*
 * Copyright 2010-2012 Cedric Priscal
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

#ifndef PROPERTYCONFIGURATION_H
#define PROPERTYCONFIGURATION_H

#include <wx/string.h>
#include "octopus/prop/property.h"

class PropertyConfiguration {

private:
	const Property* mProperty;

public:
	PropertyConfiguration(const Property* property);
	~PropertyConfiguration();

	/**
	 * @brief Loads the configuration of a property from the application configuration file.
	 *
	 * This methods searches for the configuration of a property inside the application configuration file
	 * and loads it if found.
	 */
	void load();

	/**
	 * @brief Saves the current configuration into the application configuration file.
	 */
	void save();

	typedef enum {
		ORIENTATION_AUTO = 0,
		ORIENTATION_HORIZONTAL = 1,
		ORIENTATION_VERTICAL = 2
	} ORIENTATION;

	typedef enum {
		CONTROL_TYPE_AUTO = 0,
		CONTROL_TYPE_SLIDER_ = 1,
		CONTROL_TYPE_GAUGE = 2,
		CONTROL_TYPE_CHECKBOX = 3,
		CONTROL_TYPE_TOGGLEBUTTON = 4,
		CONTROL_TYPE_PLOT = 5,
		CONTROL_TYPE_NONE = 6
	} CONTROL_TYPE;

	// Appearance
	bool mLayoutVisible;
	ORIENTATION mLayoutChildrenOrientation;
	long mLayoutProportion;
	bool mLayoutStretch;
	CONTROL_TYPE mControlType;
	ORIENTATION mControlOrientation;
	bool mControlReverse;
	bool mRefreshPolling;
	long mRefreshPeriod;

	// Keyboard
	long mKeyboardKeyA;
	long mKeyboardValueA;
	long mKeyboardReleaseA;
	long mKeyboardKeyB;
	long mKeyboardValueB;
	long mKeyboardReleaseB;

};

#endif // PROPERTYCONFIGURATION_H
