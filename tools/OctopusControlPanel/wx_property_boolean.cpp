#include "wx_property_boolean.h"

wxPropertyBoolean::wxPropertyBoolean(wxWindow* parent, Property* property) : wxToggleButton(parent, wxID_ANY, wxT("")), mProperty(property)
{
    PROPERTY_VALUE value;
	property->getValue(value);
    if (value.boolean) {
        SetValue(true);
        SetLabel(wxT("on"));
    } else {
        SetValue(false);
        SetLabel(wxT("off"));
    }

    Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(wxPropertyBoolean::onToggleButton), NULL, this);
}

wxPropertyBoolean::~wxPropertyBoolean()
{
    Disconnect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(wxPropertyBoolean::onToggleButton), NULL, this);
}

void wxPropertyBoolean::onToggleButton(wxCommandEvent& event)
{
    PROPERTY_VALUE value;
    value.boolean = GetValue();

    if (value.boolean) {
        SetLabel(wxT("on"));
    } else {
        SetLabel(wxT("off"));
    }

    mProperty->setValue(value);
}
