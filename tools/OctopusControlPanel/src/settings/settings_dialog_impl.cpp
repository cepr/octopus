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

#include "settings_dialog_impl.h"
using std::vector;

SettingsDialogImpl::SettingsDialogImpl(wxWindow *parent, PropertyManager *manager) :
	SettingsDialog(parent), mManager(manager) {

	// Request settings tabs from PropertyManager
	std::list<PropertyController*>::iterator iter;
	for (iter = mManager->mControllers.begin(); iter != mManager->mControllers.end(); ++iter) {
		PropertyController *controller = (*iter);
		wxPanel *panel = controller->getSettingsPanel(m_notebook1);
		if (panel) {
			m_notebook1->AddPage(panel, controller->getName());
		}
	}

	// Load settings from PropertyConfiguration
	// Appearance
/*	mLayoutVisible->SetValue(configuration->mLayoutVisible);
	mLayoutChildrenOrientation->SetSelection((int)configuration->mLayoutChildrenOrientation);
	mLayoutProportion->SetValue(wxString::FromDouble(configuration->mLayoutProportion, 0));
	mLayoutStretch->SetValue(configuration->mLayoutStretch);
	mControlType->SetSelection((int)configuration->mControlType);
	mControlOrientation->SetSelection((int)configuration->mControlOrientation);
	mControlReverse->SetValue(configuration->mControlReverse);
	mRefreshPolling->SetValue(configuration->mRefreshPolling);
	mRefreshPeriod->SetValue(wxString::FromDouble(configuration->mRefreshPeriod, 0));*/
	// Keyboard
/*	mKeyboardKeyA->SetSelection(configuration->mKeyboardKeyA);
	mKeyboardValueA->SetValue(wxString::FromDouble(configuration->mKeyboardValueA, 0));
	mKeyboardReleaseA->SetValue(wxString::FromDouble(configuration->mKeyboardReleaseA, 0));
	mKeyboardKeyB->SetSelection(configuration->mKeyboardKeyB);
	mKeyboardValueB->SetValue(wxString::FromDouble(configuration->mKeyboardValueB, 0));
	mKeyboardReleaseB->SetValue(wxString::FromDouble(configuration->mKeyboardReleaseB, 0));*/
}

SettingsDialogImpl::~SettingsDialogImpl() {
}

void SettingsDialogImpl::onApplyButtonClick(wxCommandEvent& event) {
/*	// Appearance
	mConfiguration->mLayoutVisible = mLayoutVisible->GetValue();
	mConfiguration->mLayoutChildrenOrientation = (PropertyConfiguration::ORIENTATION)mLayoutChildrenOrientation->GetSelection();
	mConfiguration->mLayoutProportion = mLayoutProportion->getValue();
	mConfiguration->mLayoutStretch = mLayoutStretch->GetValue();
	mConfiguration->mControlType = (PropertyConfiguration::CONTROL_TYPE)mControlType->GetSelection();
	mConfiguration->mControlOrientation = (PropertyConfiguration::ORIENTATION)mControlOrientation->GetSelection();
	mConfiguration->mControlReverse = mControlReverse->GetValue();
	mConfiguration->mRefreshPolling = mRefreshPolling->GetValue();
	mConfiguration->mRefreshPeriod = mRefreshPeriod->getValue();
	// Keyboard
	mConfiguration->mKeyboardKeyA = mKeyboardKeyA->GetSelection();
	mConfiguration->mKeyboardValueA = mKeyboardValueA->getValue();
	mConfiguration->mKeyboardReleaseA = mKeyboardReleaseA->getValue();
	mConfiguration->mKeyboardKeyB = mKeyboardKeyB->GetSelection();
	mConfiguration->mKeyboardValueB = mKeyboardValueB->getValue();
	mConfiguration->mKeyboardReleaseB = mKeyboardReleaseB->getValue();
	// Save
	mConfiguration->save();*/
}

void SettingsDialogImpl::onCancelButtonClick(wxCommandEvent& event) {
	EndModal(0);
}

void SettingsDialogImpl::onOKButtonClick(wxCommandEvent& event) {
	onApplyButtonClick(event);
	EndModal(1);
}
