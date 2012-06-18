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
#include "../property_controller.h"
#include <wx/stattext.h>
#include <wx/event.h>
#include "Property.h"
#include "property_configuration.h"
#include "wx_auto_grid_sizer.h"

class DashboardPropertyImpl : public DashboardProperty, public PropertyController
{
public:
	DashboardPropertyImpl(wxWindow *parent, PropertyManager *manager);
	~DashboardPropertyImpl();

	/**
	 * @copydoc PropertyController::getName()
	 */
	wxString getName() const;

	/**
	 * @copydoc PropertyController::onPropertyChildCreated()
	 */
	void onNewChild(PropertyManager* parent, PropertyManager* child, unsigned char index);

	/**
	 * @copydoc PropertyListener#onPropertyChanged
	 */
	void onPropertyChanged(PropertyManager* manager, PROPERTY_INFO what);

	/**
	 * @copydoc PropertyListener#onPropertyDeleted
	 */
	void onPropertyDeleted(PropertyManager* manager);

protected:
	void onRefreshClick( wxCommandEvent& event );
	void onPreferencesClick( wxCommandEvent& event );

private:
	wxWindow              *mParent;
	PROPERTY_VALUE         mPropertyLastKnownValue;
	PROPERTY_TYPE          mPropertyLastKnownType;
	wxAutoGridSizer*       mSizerChildren;
	wxWindow*              mValueCtrl;
	wxString			   mControllerName;
};

#endif // DASHBOARDPROPERTYIMPL_H
