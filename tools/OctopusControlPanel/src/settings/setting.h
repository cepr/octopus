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

#ifndef SETTING_H
#define SETTING_H

#include <wx/string.h>
#include <wx/config.h>

template <class T>
class Setting {

public:
	Setting(const wxString & key, const T & value) :
			mKey(key),
			mValue(value)
	{
	}

	void load()
	{
		wxConfig::Get()->Read(mKey, &mValue);
	}

	void save()
	{
		wxConfig::Get()->Write(mKey, mValue);
	}

	operator T() const {
		return mValue;
	}
	
	T& operator =(const T& value) {
		return (mValue = value);
	}

private:
	wxString mKey;
	T mValue;
};

#endif // SETTING_H
