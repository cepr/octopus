#ifndef DASHBOARDPROPERTY_H
#define DASHBOARDPROPERTY_H

#include <wx/sizer.h> // Base class: wxBoxSizer
#include <wx/stattext.h>
#include "Property.h"

class DashboardProperty : public wxBoxSizer {

public:
	DashboardProperty(wxWindow *parent, Property *property, wxOrientation orient = wxHORIZONTAL);
	~DashboardProperty();
    void refresh();

private:
    wxStaticText *mStaticTextName;
    wxStaticText *mStaticTextDescription;
    Property *mProperty;
};

#endif // DASHBOARDPROPERTY_H
