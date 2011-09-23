#include "dashboard_property.h"
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/tglbtn.h>
#include <wx/slider.h>
#include "wx_property_boolean.h"
#include "wx_property_number.h"

DashboardProperty::DashboardProperty(wxWindow *parent, Property* property, wxOrientation orient) : wxBoxSizer(wxVERTICAL)
{
    mProperty = property;

    // Title bar
    wxPanel* bTitleBar;
	bTitleBar = new wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bTitleBar->SetForegroundColour( wxColour( 255, 255, 255 ) );
	bTitleBar->SetBackgroundColour( wxColour( 217, 176, 134 ) );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	mStaticTextName = new wxStaticText( bTitleBar, wxID_ANY, wxString::FromAscii(property->getName()) );
	mStaticTextName->SetFont( wxFont( 16, 70, 90, 90, false ) );
	bSizer1->Add( mStaticTextName, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	mStaticTextDescription = new wxStaticText( bTitleBar, wxID_ANY, wxString::FromAscii(property->getDescription()) );
	mStaticTextDescription->SetFont( wxFont( 10, 70, 93, 90, false) );
	bSizer1->Add( mStaticTextDescription, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	bTitleBar->SetSizer( bSizer1 );
	bTitleBar->Layout();
	bSizer1->Fit( bTitleBar );
	this->Add( bTitleBar, 0, wxEXPAND | wxALL, 5 );

    // Property page
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	wxStaticLine* bStaticLine = new wxStaticLine( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer2->Add( bStaticLine, 0, wxALL|wxEXPAND, 5 );
    // child properties
	wxBoxSizer* bSizerChilds;
	bSizerChilds = new wxBoxSizer( orient );
	bSizer2->Add( bSizerChilds, 1, wxEXPAND, 5 );

    PROPERTY_VALUE value;
	property->getValue(value);

    wxWindow* bValue;
    switch(property->getType()) {
    case PROPERTY_TYPE_BOOL:
        bValue = new wxPropertyBoolean(parent, property);
        break;
    case PROPERTY_TYPE_U8:
    case PROPERTY_TYPE_S8:
    case PROPERTY_TYPE_U16:
    case PROPERTY_TYPE_S16:
        bValue = new wxPropertyNumber(parent, property);
        break;
    default:
        bValue = NULL;
    }
    if (bValue) {
        bSizerChilds->Add(bValue, 1, wxEXPAND, 5);
    }

    unsigned char index = 0;
    Property* child;
    while((child = mProperty->getChild(index)) != NULL) {
        DashboardProperty* dashprop = new DashboardProperty(parent, child, orient == wxHORIZONTAL ? wxVERTICAL : wxHORIZONTAL);
        bSizerChilds->Add(dashprop, 1, wxEXPAND, 5);
        index++;
    }

	this->Add( bSizer2, 1, wxEXPAND, 5 );
}

DashboardProperty::~DashboardProperty()
{
}

void DashboardProperty::refresh()
{
    
}
