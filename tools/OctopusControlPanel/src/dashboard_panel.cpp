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

#include "dashboard_panel.h"
#include "controller/dashboard/dashboard_property_impl.h"
#include "controller/joystick/property_controller_joystick.h"
#include "property_manager.h"

DashboardPanel::DashboardPanel(wxWindow* parent, Property* prop) : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL)
{
	SetScrollRate( 5, 5 );
    SetBackgroundColour( wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME) );
	wxGridSizer* bBoxSizer = new wxGridSizer(0, 0, 0);

	// Create a property manager
	PropertyManager* manager = new PropertyManager(prop);

	// Attach all controllers
	manager->registerController(new PropertyControllerJoystick(manager));

    DashboardPropertyImpl* bRootDashboardProperty = new DashboardPropertyImpl(this, manager);
	bBoxSizer->Add(bRootDashboardProperty, 1, wxEXPAND | wxALL, 10);
    SetSizer(bBoxSizer);
    Layout();
}

DashboardPanel::~DashboardPanel()
{
}
