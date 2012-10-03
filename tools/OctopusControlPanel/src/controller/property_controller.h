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

#ifndef PROPERTYCONTROLLER_H
#define PROPERTYCONTROLLER_H

class PropertyController;

#include "Property.h"
#include <wx/panel.h>

/**
 * @brief Represents an input device that can control the value of a property
 *
 * This class is the abstract base class for anything that can control the value of a property
 * like a keyboard, a joystick or a slider on the interface.
 */
class PropertyController : public PropertyListener
{
protected:
	/**
	 * @brief Constructor
	 *
	 * @param[in] prop The property to monitor and control.
	 */
	PropertyController(Property* prop) : mProperty(prop) {
    }

public:
	/**
	 * @brief Destructor
	 */
	virtual ~PropertyController() {
        if (mProperty) {
            mProperty->unregisterListener(this);
        }
    }

	/**
	 * @brief Returns the controller name
	 */
	virtual wxString getName() const = 0;

	/**
	 * @brief Returns a settings panel
	 *
	 * This method is called when the configuration dialog of a property is displayed (class PropertiesDialog).
	 * The default implementation of this method returns NULL.
	 *
	 * @return This method returns a settings panel, or NULL if no configuration tab is needed.
	 */
	virtual wxPanel* getSettingsPanel(wxWindow *parent) {
        return NULL;
    }

    /**
     * @copydoc PropertyListener#onPropertyChanged
     */
    virtual void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin) = 0;

    /**
	 * @copydoc PropertyListener#onNewChild
	 */
	virtual void onNewChild(Property* prop, Property* child, unsigned char index) = 0;

	/**
	 * @copydoc PropertyListener#onPropertyDeleted
	 */
	virtual void onPropertyDeleted() {
        mProperty = NULL;
        delete this;
    }

protected:
	Property* mProperty;
};

#endif // PROPERTYCONTROLLER_H
