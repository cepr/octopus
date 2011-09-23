#include "wx_property_number.h"

wxPropertyNumber::wxPropertyNumber(wxWindow* parent, Property* property) : wxSlider(parent,
                                                                                    wxID_ANY,
                                                                                    0,
                                                                                    0,
                                                                                    1,
                                                                                    wxDefaultPosition,
                                                                                    wxDefaultSize,
                                                                                    wxSL_HORIZONTAL|wxSL_LABELS),
                                                                           mProperty(property),
                                                                           mTimer(this)
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
    case PROPERTY_TYPE_INVALID:
    case PROPERTY_TYPE_UNKNOWN:
    case PROPERTY_TYPE_VOID:
        ; // nothing to do
    }
    Refresh();
    Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( wxPropertyNumber::onScroll ), (wxObject*)NULL, (wxEvtHandler*)this );
}

wxPropertyNumber::~wxPropertyNumber()
{
    Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( wxPropertyNumber::onScroll ), NULL, this );
    mTimer.Stop();
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
    case PROPERTY_TYPE_INVALID:
    case PROPERTY_TYPE_UNKNOWN:
    case PROPERTY_TYPE_VOID:
        return;
    }
    mProperty->setValue(value);
}

// Timer notify function
void wxPropertyNumber::Refresh()
{
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
    case PROPERTY_TYPE_INVALID:
    case PROPERTY_TYPE_UNKNOWN:
    case PROPERTY_TYPE_VOID:
        ; // nothing to do
    }
    mTimer.Start(20, true);
}
