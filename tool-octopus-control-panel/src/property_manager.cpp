
#if 0

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

#include "property_manager.h"
#include "settings/settings_dialog_impl.h"

PropertyManager::PropertyManager(Property* prop) :
	mProperty(prop),
	mPropertyAvailableInfo(0)
{
	// Start listening to the property events
	prop->registerListener(this);
}

PropertyManager::~PropertyManager()
{
}

void PropertyManager::onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin)
{
	// Save available information
	mPropertyAvailableInfo |= what;
	// Notify all Controllers about the new property
	std::list<PropertyController*>::iterator it;
	for (it = mControllers.begin(); it != mControllers.end(); ++it) {
		(*it)->onPropertyChanged(this, what, origin);
	}
}

void PropertyManager::onNewChild(Property* prop, Property* child, unsigned char index)
{
	// Resize children if necessary
	if (mChildren.size() <= index) {
		mChildren.resize(index + 1);
	}

	// Check that no previous child of this type already exists
	if (mChildren[index] == 0) {
		// Create a PropertyManager to manage this new Property
		mChildren[index] = new PropertyManager(child);
		// Notify all Controllers about the new property
		std::list<PropertyController*>::iterator it;
		for (it = mControllers.begin(); it != mControllers.end(); ++it) {
			(*it)->onNewChild(this, mChildren[index], index);
		}
	}
}

void PropertyManager::onPropertyDeleted()
{
	// Stop listening to property
	mProperty = 0;
	// Notify all Controllers about the deleted property
	std::list<PropertyController*>::iterator it;
	while (mControllers.size() > 0) {
        PropertyController* pc = mControllers.front();
		pc->onPropertyDeleted();
        delete pc;
	}
	// bye bye
	delete this;
}

void PropertyManager::registerController(PropertyController* controller)
{
	// Register the controller
	mControllers.push_back(controller);

	// Report value, name, type and description
	controller->onPropertyChanged(this, mPropertyAvailableInfo, ORIGIN_REMOTE);

	// Report children (if any)
	size_t i;
	for (i=0; i<mChildren.size(); i++) {
		if (mChildren[i] != 0) {
			controller->onNewChild(this, mChildren[i], i);
		}
	}
}

void PropertyManager::unregisterController(PropertyController* controller)
{
	mControllers.remove(controller);
}

void PropertyManager::displaySettingsDialog()
{
	SettingsDialogImpl dialog(NULL, this);
	dialog.ShowModal();
}

#endif
