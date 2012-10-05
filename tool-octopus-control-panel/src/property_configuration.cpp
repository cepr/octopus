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

#include <wx/config.h>
#include "property_configuration.h"

namespace {
	const wxChar CFG_KEY_APPEARANCE_LAYOUT_VISIBLE[]			  	= wxT("Appearance/Layout/Visible");
	const wxChar CFG_KEY_APPEARANCE_LAYOUT_CHILDRENORIENTATION[]	= wxT("Appearance/Layout/ChildrenOrientation");
	const wxChar CFG_KEY_APPEARANCE_LAYOUT_PROPORTION[]   			= wxT("Appearance/Layout/Proportion");
	const wxChar CFG_KEY_APPEARANCE_LAYOUT_STRETCH[]				= wxT("Appearance/Layout/Stretch");
	const wxChar CFG_KEY_APPEARANCE_CONTROL_TYPE[]					= wxT("Appearance/Control/Type");
	const wxChar CFG_KEY_APPEARANCE_CONTROL_ORIENTATION[]			= wxT("Appearance/Control/Orientation");
	const wxChar CFG_KEY_APPEARANCE_CONTROL_REVERSE[]				= wxT("Appearance/Control/Reverse");
	const wxChar CFG_KEY_APPEARANCE_REFRESH_POLLING[]				= wxT("Appearance/Refresh/Polling");
	const wxChar CFG_KEY_APPEARANCE_REFRESH_PERIOD[]				= wxT("Appearance/Refresh/Period");
	const wxChar CFG_KEY_KEYBOARD_KEYA[]							= wxT("Keyboard/KeyA");
	const wxChar CFG_KEY_KEYBOARD_VALUEA[]							= wxT("Keyboard/ValueA");
	const wxChar CFG_KEY_KEYBOARD_RELEASEA[]						= wxT("Keyboard/ReleaseA");
	const wxChar CFG_KEY_KEYBOARD_KEYB[]							= wxT("Keyboard/KeyB");
	const wxChar CFG_KEY_KEYBOARD_VALUEB[]							= wxT("Keyboard/ValueB");
	const wxChar CFG_KEY_KEYBOARD_RELEASEB[]						= wxT("Keyboard/ReleaseB");
}

PropertyConfiguration::PropertyConfiguration(const Property* property) :
		mProperty(property),

		// Appearance
		mLayoutVisible(true),
		mLayoutChildrenOrientation(ORIENTATION_AUTO),
		mLayoutProportion(1),
		mLayoutStretch(false),
		mControlType(CONTROL_TYPE_AUTO),
		mControlOrientation(ORIENTATION_AUTO),
		mControlReverse(false),
		mRefreshPolling(false),
		mRefreshPeriod(100),

		// Keyboard
		mKeyboardKeyA(-1),
		mKeyboardValueA(0),
		mKeyboardReleaseA(0),
		mKeyboardKeyB(-1),
		mKeyboardValueB(0),
		mKeyboardReleaseB(0)
{
}

PropertyConfiguration::~PropertyConfiguration()
{
}

void PropertyConfiguration::load()
{
	if ((mProperty != NULL) && (mProperty->getName() != NULL)) {

		// TODO Property should be identified by an UUID
		wxString root = wxString(mProperty->getName()) + wxT("/");

		wxConfigBase* cfg = wxConfigBase::Get();
		if (cfg) {
			// Appearance
			mLayoutVisible 					= cfg->ReadBool(root + CFG_KEY_APPEARANCE_LAYOUT_VISIBLE, true);
			mLayoutChildrenOrientation 		= (ORIENTATION)cfg->ReadLong(root + CFG_KEY_APPEARANCE_LAYOUT_CHILDRENORIENTATION, (long)ORIENTATION_AUTO);
			mLayoutProportion 				= cfg->ReadLong(root + CFG_KEY_APPEARANCE_LAYOUT_PROPORTION, 1);
			mLayoutStretch 					= cfg->ReadBool(root + CFG_KEY_APPEARANCE_LAYOUT_STRETCH, false);
			mControlType 					= (CONTROL_TYPE)cfg->ReadLong(root + CFG_KEY_APPEARANCE_CONTROL_TYPE, (long)CONTROL_TYPE_AUTO);
			mControlOrientation 			= (ORIENTATION)cfg->ReadLong(root + CFG_KEY_APPEARANCE_CONTROL_ORIENTATION, (long)ORIENTATION_AUTO);
			mControlReverse 				= cfg->ReadBool(root + CFG_KEY_APPEARANCE_CONTROL_REVERSE, false);
			mRefreshPolling 				= cfg->ReadBool(root + CFG_KEY_APPEARANCE_REFRESH_POLLING, false);
			mRefreshPeriod 					= cfg->ReadLong(root + CFG_KEY_APPEARANCE_REFRESH_PERIOD, 100);
			// Keyboard
			mKeyboardKeyA					= cfg->ReadLong(root + CFG_KEY_KEYBOARD_KEYA, -1);
			mKeyboardValueA					= cfg->ReadLong(root + CFG_KEY_KEYBOARD_VALUEA, 0);
			mKeyboardReleaseA				= cfg->ReadLong(root + CFG_KEY_KEYBOARD_RELEASEA, 0);
			mKeyboardKeyB					= cfg->ReadLong(root + CFG_KEY_KEYBOARD_KEYB, -1);
			mKeyboardValueB					= cfg->ReadLong(root + CFG_KEY_KEYBOARD_VALUEB, 0);
			mKeyboardReleaseB				= cfg->ReadLong(root + CFG_KEY_KEYBOARD_RELEASEB, 0);
		}
	}
}

void PropertyConfiguration::save()
{
	if ((mProperty != NULL) && (mProperty->getName() != NULL)) {

		// TODO Property should be identified by an UUID
		wxString root = wxString(mProperty->getName()) + wxT("/");

		wxConfigBase* cfg = wxConfigBase::Get();
		if (cfg) {
			// Appearance
			cfg->Write(root + CFG_KEY_APPEARANCE_LAYOUT_VISIBLE, mLayoutVisible);
			cfg->Write(root + CFG_KEY_APPEARANCE_LAYOUT_CHILDRENORIENTATION, (long)mLayoutChildrenOrientation);
			cfg->Write(root + CFG_KEY_APPEARANCE_LAYOUT_PROPORTION, mLayoutProportion);
			cfg->Write(root + CFG_KEY_APPEARANCE_LAYOUT_STRETCH, mLayoutStretch);
			cfg->Write(root + CFG_KEY_APPEARANCE_CONTROL_TYPE, (long)mControlType);
			cfg->Write(root + CFG_KEY_APPEARANCE_CONTROL_ORIENTATION, (long)mControlOrientation);
			cfg->Write(root + CFG_KEY_APPEARANCE_CONTROL_REVERSE, mControlReverse);
			cfg->Write(root + CFG_KEY_APPEARANCE_REFRESH_POLLING, mRefreshPolling);
			cfg->Write(root + CFG_KEY_APPEARANCE_REFRESH_PERIOD, mRefreshPeriod);
			// Keyboard
			cfg->Write(root + CFG_KEY_KEYBOARD_KEYA, mKeyboardKeyA);
			cfg->Write(root + CFG_KEY_KEYBOARD_VALUEA, mKeyboardValueA);
			cfg->Write(root + CFG_KEY_KEYBOARD_RELEASEA, mKeyboardReleaseA);
			cfg->Write(root + CFG_KEY_KEYBOARD_KEYB, mKeyboardKeyB);
			cfg->Write(root + CFG_KEY_KEYBOARD_VALUEB, mKeyboardValueB);
			cfg->Write(root + CFG_KEY_KEYBOARD_RELEASEB, mKeyboardReleaseB);
		}
	}
}
