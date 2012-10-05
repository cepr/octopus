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

#ifndef PROPERTYCONTROLLERJOYSTICK_H
#define PROPERTYCONTROLLERJOYSTICK_H

#include "controller/property_controller.h" // Base class: PropertyControllerSource
#include <wx/timer.h>
#include "joystick_settings.h"
#include "joystick_virtual_axe.h"

/**
 * Joystick
 *
 * This class reads the value of the axis and buttons of a joystick, and compute an absolute
 * value to apply to the property under control.
 */
class PropertyControllerJoystick : public PropertyController, private wxTimer
{
private:
	JoystickSettings mSettings;
	JoystickVirtualAxe mVirtualAxe;

public:
	/**
	 * Constructor.
	 *
	 * @param[in] prop The property to control.
	 */
	PropertyControllerJoystick(Property* prop);

	/**
	 * @brief Destructor
	 */
	virtual ~PropertyControllerJoystick();

    /**
     * @copydoc PropertyListener#onPropertyChanged
     */
    virtual void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin);

    /**
	 * @copydoc PropertyListener#onNewChild
	 */
	virtual void onNewChild(Property* prop, Property* child, unsigned char index);

	/**
	 * @brief Returns the controller name
	 */
	virtual wxString getName() const;

	/**
	 * @brief Returns the associated configuration panel
	 *
	 * @return This function returns a @ref JoystickSettingsPanel object
	 */
	virtual wxPanel* getSettingsPanel(wxWindow *parent);

	/**
	 * @brief Called periodically to read Joystick position.
	 */
	void Notify();
};

#endif // PROPERTYCONTROLLERJOYSTICK_H
