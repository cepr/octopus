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

#include "wx_property_number.h"
#include <wx/log.h>

wxPropertyNumber::wxPropertyNumber(wxWindow* parent, Property* property) :
	wxSlider(parent, wxID_ANY, 0, 0, 1, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS),
	mProperty(property)
{
	switch(property->getType()) {
	case PROPERTY_TYPE_U8:
		SetMin(0);
		SetMax(255);
		break;
	case PROPERTY_TYPE_S8:
		SetMin(-128);
		SetMax(127);
		break;
	case PROPERTY_TYPE_U16:
		SetMin(0);
		SetMax(65535);
		break;
	case PROPERTY_TYPE_S16:
		SetMin(-32768);
		SetMax(32767);
		break;
	case PROPERTY_TYPE_BOOL:
		SetMin(0);
		SetMax(1);
		break;
	case PROPERTY_TYPE_VOID:
		; // nothing to do
	}
	onPropertyChanged(property, Property::PROPERTY_INFO_VALUE);
	Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( wxPropertyNumber::onScroll ), (wxObject*)NULL, (wxEvtHandler*)this );
}

wxPropertyNumber::~wxPropertyNumber()
{
	Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( wxPropertyNumber::onScroll ), NULL, this );
}

void wxPropertyNumber::onScroll(wxScrollEvent& event)
{
	PROPERTY_VALUE value;
	switch(mProperty->getType()) {
	case PROPERTY_TYPE_U8:
		value.u8 = GetValue();
		break;
	case PROPERTY_TYPE_S8:
		value.s8 = GetValue();
		break;
	case PROPERTY_TYPE_U16:
		value.u16 = GetValue();
		break;
	case PROPERTY_TYPE_S16:
		value.s16 = GetValue();
		break;
	case PROPERTY_TYPE_BOOL:
		value.boolean = (GetValue() == 1);
		break;
	case PROPERTY_TYPE_VOID:
		return;
	}
	mProperty->setValue(value);
}

void wxPropertyNumber::onPropertyChanged(Property* prop, PROPERTY_INFO what)
{
	if (what & Property::PROPERTY_INFO_VALUE) {
		PROPERTY_VALUE value;
		mProperty->getValue(value);
		switch(mProperty->getType()) {
		case PROPERTY_TYPE_U8:
			SetValue(value.u8);
			break;
		case PROPERTY_TYPE_S8:
			SetValue(value.s8);
			break;
		case PROPERTY_TYPE_U16:
			SetValue(value.u16);
			break;
		case PROPERTY_TYPE_S16:
			SetValue(value.s16);
			break;
		case PROPERTY_TYPE_BOOL:
			SetValue(value.boolean ? 1 : 0);
			break;
		case PROPERTY_TYPE_VOID:
			; // nothing to do
		}
	}
}

void wxPropertyNumber::onNewChild(Property* prop, Property* child, unsigned char index)
{
}

void wxPropertyNumber::onPropertyDeleted()
{
	wxLogDebug("wxPropertyNumber::onPropertyDeleted");
}
