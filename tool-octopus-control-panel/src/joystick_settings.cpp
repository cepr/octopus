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

#include "joystick_settings.h"
#include <limits>

JoystickSettings::JoystickSettings() :
		mJoystickDeviceName(			wxS("Joystick/DeviceName"), 			wxS("")),
		mJoystickAxis1Button(			wxS("Joystick/Axis1/Button"), 			-1l),
		mJoystickAxis1Axis(				wxS("Joystick/Axis1/Axis"), 			-1l),
		mJoystickAxis1Ratio(			wxS("Joystick/Axis1/Ratio"), 			1.0),
		mJoystickAxis2Button(			wxS("Joystick/Axis2/Button"), 			-1l),
		mJoystickAxis2Axis(				wxS("Joystick/Axis2/Axis"), 			-1l),
		mJoystickAxis2Ratio(			wxS("Joystick/Axis2/Ratio"), 			1.0),
		mJoystickPostprocessOffset(		wxS("Joystick/PostProcess/Offset"), 	0l),
		mJoystickPostprocessMin(		wxS("Joystick/PostProcess/Min"), 		std::numeric_limits<long>::min()),
		mJoystickPostprocessMax(		wxS("Joystick/PostProcess/Max"), 		std::numeric_limits<long>::max())
{
}

void JoystickSettings::load()
{
	mJoystickDeviceName.load();
	mJoystickAxis1Button.load();
	mJoystickAxis1Axis.load();
	mJoystickAxis1Ratio.load();
	mJoystickAxis2Button.load();
	mJoystickAxis2Axis.load();
	mJoystickAxis2Ratio.load();
	mJoystickPostprocessOffset.load();
	mJoystickPostprocessMin.load();
	mJoystickPostprocessMax.load();
}

void JoystickSettings::save()
{
	mJoystickDeviceName.save();
	mJoystickAxis1Button.save();
	mJoystickAxis1Axis.save();
	mJoystickAxis1Ratio.save();
	mJoystickAxis2Button.save();
	mJoystickAxis2Axis.save();
	mJoystickAxis2Ratio.save();
	mJoystickPostprocessOffset.save();
	mJoystickPostprocessMin.save();
	mJoystickPostprocessMax.save();
}
