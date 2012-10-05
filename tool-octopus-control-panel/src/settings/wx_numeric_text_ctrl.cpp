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

#include "wx_numeric_text_ctrl.h"

wxNumericTextCtrl::wxNumericTextCtrl(
    wxWindow *parent,
    wxWindowID id,
    const wxString &value,
    const wxPoint &pos,
    const wxSize &size,
    long style,
    const wxValidator& validator,
    const wxString &name)
	: wxTextCtrl(
	    parent,
	    id,
	    value,
	    pos,
	    size,
	    style,
	    validator,
	    name) {
	mValue = 0;
	mParent = parent;
	refresh();
	Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( wxNumericTextCtrl::onTextChanged ), NULL, this );
}

wxNumericTextCtrl::~wxNumericTextCtrl() {
	Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( wxNumericTextCtrl::onTextChanged ), NULL, this );
}

void wxNumericTextCtrl::onTextChanged( wxCommandEvent& event ) {
	refresh();
	mParent->HandleWindowEvent(event);
}

void wxNumericTextCtrl::refresh() {
	if (GetValue().ToDouble(&mValue)) {
		SetBackgroundColour(wxNullColour);
	} else {
		mValue = 0;
		SetBackgroundColour(wxColour(255, 156, 156));
	}
}
