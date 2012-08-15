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

#include "property_controller_joystick.h"
#include "settings/joystick_settings_panel_impl.h"

PropertyControllerJoystick::PropertyControllerJoystick(Property* prop) :
	PropertyController(prop)
{
	Notify();
}

PropertyControllerJoystick::~PropertyControllerJoystick()
{
}

void PropertyControllerJoystick::onPropertyChanged(Property* prop, PROPERTY_INFO what)
{
}

void PropertyControllerJoystick::onNewChild(Property* prop, Property* child, unsigned char index)
{
    child->registerListener(new PropertyControllerJoystick(child));
}

wxString PropertyControllerJoystick::getName() const
{
	static wxString name = wxT("Joystick");
	return name;
}

wxPanel* PropertyControllerJoystick::getSettingsPanel(wxWindow *parent)
{
	return new JoystickSettingsPanelImpl(parent, &mVirtualAxe/*, mSettings, mManager ? mManager->getProperty() : 0*/);
}

void PropertyControllerJoystick::Notify()
{
	if (mVirtualAxe.isEnabled()) {
		double dvalue = mVirtualAxe.GetValue();
		PROPERTY_VALUE evalue;
		switch(mProperty->getType()) {
			case PROPERTY_TYPE_BOOL:
				evalue.boolean = (dvalue != 0);
				break;
			case PROPERTY_TYPE_U16:
				if (dvalue < 0) {
					evalue.u16 = 0;
				} else if (dvalue > 0xFFFF) {
					evalue.u16 = 0xFFFF;
				} else {
					evalue.u16 = (unsigned short)dvalue;
				}
				break;
			case PROPERTY_TYPE_S16:
				if (dvalue < -32768) {
					evalue.s16 = -32768;
				} else if (dvalue > 32767) {
					evalue.s16 = 32767;
				} else {
					evalue.s16 = (short)dvalue;
				}
				break;
			case PROPERTY_TYPE_S8:
				if (dvalue < -128) {
					evalue.s8 = -128;
				} else if (dvalue > 127) {
					evalue.s8 = 127;
				} else {
					evalue.s8 = (char)dvalue;
				}
				break;
			case PROPERTY_TYPE_U8:
				if (dvalue < 0) {
					evalue.u8 = 0;
				} else if (dvalue > 255) {
					evalue.u8 = 255;
				} else {
					evalue.u8 = (unsigned char)dvalue;
				}
				break;
			default:
				return;
		}
		mProperty->setValue(evalue);
	}
	Start(10, true);
}
