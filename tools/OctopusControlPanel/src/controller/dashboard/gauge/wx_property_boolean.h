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

#ifndef WXPROPERTYBOOLEAN_H
#define WXPROPERTYBOOLEAN_H

#include <wx/tglbtn.h> // Base class: wxToggleButton
#include "Property.h"
#include "PropertyListener.h"

class wxPropertyBoolean : public wxToggleButton, public PropertyListener
{
public:
	wxPropertyBoolean(wxWindow* parent, Property* property);
	~wxPropertyBoolean();
	void onPropertyChanged(Property* prop, PROPERTY_INFO what);
	void onNewChild(Property* prop, Property* child, unsigned char index);
	void onPropertyDeleted(Property* prop);

private:
	Property* mProperty;
	void onToggleButton( wxCommandEvent& event );
};

#endif // WXPROPERTYBOOLEAN_H
