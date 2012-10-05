/*
 * Copyright 2012 Cedric Priscal
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

#if 0

#ifndef PROPERTYMANAGER_H
#define PROPERTYMANAGER_H

class PropertyManager;

#include "PropertyListener.h"
#include "controller/property_controller.h"
#include <list>

/**
 * \brief Property manager class
 *
 * This class manages a Property:
 * - it holds all its listeners
 * - it manages its settings
 */
class PropertyManager : public PropertyListener
{
public:
	/**
	 * @brief Constructor
	 *
	 * @param[in,out] prop The property to manage
	 */
	PropertyManager(Property* prop);

	/**
	 * @brief Destructor
	 */
	~PropertyManager();

	/**
	 * @copydoc PropertyListener::onPropertyChanged()
	 */
	void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin);

	/**
	 * @copydoc PropertyListener::onPropertyChildCreated()
	 */
	void onNewChild(Property* prop, Property* child, unsigned char index);

	/**
	 * @copydoc PropertyListener::onPropertyDeleted()
	 */
	void onPropertyDeleted();

	/**
	 * @brief Register a property controller class
	 *
	 * @param[in] controller PropertyController instance to register
	 */
	void registerController(PropertyController* controller);

	/**
	 * @brief Unregister a property controller class
	 *
	 * @param[in] controller PropertyController instance to unregister
	 */
	void unregisterController(PropertyController* controller);

	Property* getProperty() {
		return mProperty;
	}

	/**
	 * @brief Display the preferences dialog for the managed property
	 */
	void displaySettingsDialog();

	/**
	 * @brief List of all controllers for current property
	 */
	std::list<PropertyController*> 	mControllers;

private:
	Property* 						mProperty;
	PROPERTY_INFO 					mPropertyAvailableInfo;
	std::vector<PropertyManager*>	mChildren;
};

#endif // PROPERTYMANAGER_H

#endif
