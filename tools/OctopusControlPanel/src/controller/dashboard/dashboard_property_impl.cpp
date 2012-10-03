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

#include "dashboard_property_impl.h"
#include "property_manager.h"
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/tglbtn.h>
#include <wx/slider.h>
#include <wx/button.h>
#include <wx/log.h>
#include "gauge/wx_property_boolean.h"
#include "gauge/wx_property_number.h"
#include "settings/settings_dialog_impl.h"
#include <math.h>

DashboardPropertyImpl::DashboardPropertyImpl(wxWindow *parent, Property *prop) :
	DashboardProperty(parent),
	PropertyController(prop),
	mParent(parent),
	mPropertyLastKnownType(PROPERTY_TYPE_VOID),
	mSizerChildren(0),
	mValueCtrl(0),
	mControllerName(wxT("DashboardProperty"))
{
	// Add a sizer for the children
	mSizerChildren = new wxAutoGridSizer(10, 10);
	GetSizer()->Add(mSizerChildren, 1, wxEXPAND | wxALL, 10);
}

DashboardPropertyImpl::~DashboardPropertyImpl()
{
}

void DashboardPropertyImpl::onPreferencesClick(wxCommandEvent& event)
{
    SettingsDialogImpl dialog(NULL, mProperty);
	dialog.ShowModal();
	//if (mManager) {
		//mManager->displaySettingsDialog();
	//}
}

void DashboardPropertyImpl::onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin)
{
    // Property has changed, we should refresh the dashboard
    if (what & Property::PROPERTY_INFO_NAME) {
        mStaticTextName->SetLabel(wxString::FromUTF8(prop->getName()));
    }
    if (what & Property::PROPERTY_INFO_DESCRIPTION) {
        mStaticTextDescription->SetLabel(wxString::FromUTF8(prop->getDescription()));
    }
    if (what & Property::PROPERTY_INFO_TYPE) {
        PROPERTY_TYPE new_type = prop->getType();
        if (new_type != mPropertyLastKnownType) {
            // Save new type
            mPropertyLastKnownType = new_type;
            // Create a new value control
            wxWindow* newValueCtrl;
            switch(new_type) {
            case PROPERTY_TYPE_BOOL:
                newValueCtrl = new wxPropertyBoolean(this, prop);
                break;
            case PROPERTY_TYPE_U8:
            case PROPERTY_TYPE_S8:
            case PROPERTY_TYPE_U16:
            case PROPERTY_TYPE_S16:
                newValueCtrl = new wxPropertyNumber(this, prop);
                break;
            default:
                newValueCtrl = 0;
            }
            // Detach and remove old control
            if (mValueCtrl) {
                mSizerChildren->Detach(mValueCtrl);
                mValueCtrl->Destroy();
            }
            // Attach the new one
            mValueCtrl = newValueCtrl;
            if (mValueCtrl) {
                mSizerChildren->Add(mValueCtrl, 1, wxEXPAND | wxALIGN_CENTER, 5);
            }
            prop->getValue(mPropertyLastKnownValue);
            Layout();
        }
    }
    if (what & Property::PROPERTY_INFO_VALUE) {
        if (mValueCtrl) {
            // TODO cast is not clean
            dynamic_cast<PropertyListener*>(mValueCtrl)->onPropertyChanged(prop, what & Property::PROPERTY_INFO_VALUE, origin);
        }
    }
}

void DashboardPropertyImpl::onNewChild(Property* prop, Property* child, unsigned char index)
{
	if (mValueCtrl) {
		// index 0 is reserved for current property value
		index++;
	}

	// Create a DashboardProperty dedicated for the new child
	DashboardPropertyImpl* dashprop = new DashboardPropertyImpl(this, child);
	wxSizerItem* newchild = new wxSizerItem(dashprop, 1, wxEXPAND, 0);

	if (index < mSizerChildren->GetItemCount()) {
		// Get the old DashboardProperty using the given index
		wxSizerItem* oldchild = mSizerChildren->GetItem(index);

		// We must replace the old child by this new one
		mSizerChildren->Replace(index, newchild);
		if (oldchild->IsWindow()) {
			wxWindow* win = oldchild->GetWindow();
			if (win) {
				win->Destroy();
			}
		}
	} else {
		// We must add a new child
		// First step: we add as many spacers as needed
		for (size_t i = mSizerChildren->GetItemCount(); i < index; i++) {
			mSizerChildren->AddStretchSpacer();
		}
		// Second step: we add the child itself
		mSizerChildren->Add(newchild);
	}

	// Refresh screen
	Layout();

    // Register listener
    child->registerListener(dashprop);
}

void DashboardPropertyImpl::onRefreshClick(wxCommandEvent& event)
{
	// Force a refresh of the underlying property
	if (mProperty) {
        mProperty->refresh();
	}
}

wxString DashboardPropertyImpl::getName() const
{
	return mControllerName;
}
