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

#ifndef DASHBOARDPROPERTYIMPL_H
#define DASHBOARDPROPERTYIMPL_H

#include "dashboard_property.h" // Base class: DashboardProperty
#include "controller/property_controller.h" // Base class: PropertyController
#include <wx/stattext.h>
#include <wx/event.h>
#include "Property.h"
#include "property_configuration.h"
#include "wx_auto_grid_sizer.h"

class DashboardPropertyImpl : public DashboardProperty, public PropertyController
{
private:
	wxWindow              *mParent;
	PROPERTY_VALUE         mPropertyLastKnownValue;
	PROPERTY_TYPE          mPropertyLastKnownType;
	wxAutoGridSizer*       mSizerChildren;
	wxWindow*              mValueCtrl;
	wxString			   mControllerName;

public:
	DashboardPropertyImpl(wxWindow *parent, Property *prop);
	~DashboardPropertyImpl();

	/**
	 * @copydoc PropertyController::getName()
	 */
	wxString getName() const;

	/**
	 * @copydoc PropertyListener#onPropertyChanged
	 */
	virtual void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin);

	/**
	 * @copydoc PropertyListener#onNewChild
	 */
	virtual void onNewChild(Property* prop, Property* child, unsigned char index);

protected:
	void onRefreshClick( wxCommandEvent& event );
	void onPreferencesClick( wxCommandEvent& event );
};

#endif // DASHBOARDPROPERTYIMPL_H
