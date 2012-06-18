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
#include "property_manager.h"
#include <wx/panel.h>

/**
 * @brief Represents an input device that can control the value of a property
 *
 * This class is the abstract base class for anything that can control the value of a property
 * like a keyboard, a joystick or a slider on the interface.
 */
class PropertyController
{

public:
	/**
	 * @brief Constructor
	 *
	 * @param[in] manager The property manager associated with a Property
	 */
	PropertyController(PropertyManager* manager);

	/**
	 * @brief Destructor
	 */
	virtual ~PropertyController();

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
	virtual wxPanel* getSettingsPanel(wxWindow *parent);

	/**
	 * @brief Method called when a property has changed
	 *
	 * @param[in,out] prop The changed property
	 * @param[in,out] what Elements that have changed
	 */
	virtual void onPropertyChanged(PropertyManager* prop, PROPERTY_INFO what) = 0;

	/**
	 * @brief Method called when a property has a new child
	 *
	 * @param[in,out] prop  The parent property
	 * @param[in,out] child The new-born child
	 * @param[in]     index The index of the child in the parent children list
	 */
	virtual void onNewChild(PropertyManager* prop, PropertyManager* child, unsigned char index) = 0;

	/**
	 * @brief Method called when a property has deleted its child
	 *
	 * @param[in,out] prop The deleted property
	 */
	virtual void onPropertyDeleted(PropertyManager* prop) = 0;

protected:
	PropertyManager* mManager;
};

#endif // PROPERTYCONTROLLER_H
