#ifndef DASHBOARDPANEL_H
#define DASHBOARDPANEL_H

#include <wx/scrolwin.h> // Base class: wxScrolledWindow
#include "Property.h"

class DashboardPanel : public wxScrolledWindow {

public:
	DashboardPanel(wxWindow* parent, Property* prop);
	~DashboardPanel();

};

#endif // DASHBOARDPANEL_H
