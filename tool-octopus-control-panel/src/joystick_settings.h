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

#ifndef JOYSTICKSETTINGS_H
#define JOYSTICKSETTINGS_H

#include <wx/string.h>
#include "settings/setting.h"

class JoystickSettings {

public:
	JoystickSettings();
	void load();
	void save();

	Setting<wxString>	mJoystickDeviceName;	// TODO Joystick should be identified by more than its name (what if duplicate ?)
	Setting<long>		mJoystickAxis1Button;
	Setting<long> 		mJoystickAxis1Axis;
	Setting<double> 	mJoystickAxis1Ratio;
	Setting<long> 		mJoystickAxis2Button;
	Setting<long> 		mJoystickAxis2Axis;
	Setting<double> 	mJoystickAxis2Ratio;
	Setting<long> 		mJoystickPostprocessOffset;
	Setting<long> 		mJoystickPostprocessMin;
	Setting<long> 		mJoystickPostprocessMax;
};

#endif // JOYSTICKSETTINGS_H
