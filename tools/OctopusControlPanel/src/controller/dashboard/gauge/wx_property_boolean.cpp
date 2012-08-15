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

#include "wx_property_boolean.h"
#include <wx/log.h>

wxPropertyBoolean::wxPropertyBoolean(wxWindow* parent, Property* property) : wxToggleButton(parent, wxID_ANY, wxT("")), mProperty(property)
{
	// Force a refresh
	onPropertyChanged(property, Property::PROPERTY_INFO_VALUE);
	Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(wxPropertyBoolean::onToggleButton), NULL, this);
}

wxPropertyBoolean::~wxPropertyBoolean()
{
	Disconnect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(wxPropertyBoolean::onToggleButton), NULL, this);
}

void wxPropertyBoolean::onPropertyChanged(Property* prop, PROPERTY_INFO what)
{
	if (what & Property::PROPERTY_INFO_VALUE) {
		PROPERTY_VALUE value;
		prop->getValue(value);
		if (value.boolean) {
			SetValue(true);
			SetLabel(wxT("on"));
		} else {
			SetValue(false);
			SetLabel(wxT("off"));
		}
	}
}

void wxPropertyBoolean::onNewChild(Property* prop, Property* child, unsigned char index)
{
}

void wxPropertyBoolean::onPropertyDeleted()
{
	wxLogDebug("wxPropertyBoolean::onPropertyDeleted");
}

void wxPropertyBoolean::onToggleButton(wxCommandEvent& event)
{
	PROPERTY_VALUE value;
	value.boolean = GetValue();

	if (value.boolean) {
		SetLabel(wxT("on"));
	} else {
		SetLabel(wxT("off"));
	}

	mProperty->setValue(value);
}
