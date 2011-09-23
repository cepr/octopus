#include "dashboard_panel.h"
#include "dashboard_property.h"

DashboardPanel::DashboardPanel(wxWindow* parent, Property* prop) : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL)
{
	this->SetScrollRate( 5, 5 );
    this->SetBackgroundColour( wxColour( 255, 255, 255 ) );
    DashboardProperty* bRootDashboardProperty = new DashboardProperty(this, prop, wxVERTICAL);
    this->SetSizer(bRootDashboardProperty);
    this->Layout();
}

DashboardPanel::~DashboardPanel()
{
}
