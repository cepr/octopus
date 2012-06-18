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

#ifndef WXNUMERICTEXTCTRL_H
#define WXNUMERICTEXTCTRL_H

#include "wx/textctrl.h" // Base class: wxTextCtrl

class wxNumericTextCtrl : public wxTextCtrl {

private:
	wxNumericTextCtrl(const wxNumericTextCtrl& rhs);
	wxNumericTextCtrl& operator=(const wxNumericTextCtrl& rhs);
	double mValue;
	wxWindow *mParent;
	void refresh();

public:
	wxNumericTextCtrl(
	    wxWindow *parent,
	    wxWindowID id,
	    const wxString &value = wxEmptyString,
	    const wxPoint &pos = wxDefaultPosition,
	    const wxSize &size = wxDefaultSize,
	    long style = 0,
	    const wxValidator& validator = wxDefaultValidator,
	    const wxString &name = wxTextCtrlNameStr);
	~wxNumericTextCtrl();
	operator double() {
		return mValue;
	}
	double getValue() {
		return mValue;
	}
	virtual void onTextChanged( wxCommandEvent& event );
};

#endif // WXNUMERICTEXTCTRL_H
