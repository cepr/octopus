#ifndef WXPROPERTYBOOLEAN_H
#define WXPROPERTYBOOLEAN_H

#include <wx/tglbtn.h> // Base class: wxToggleButton
#include "Property.h"

class wxPropertyBoolean : public wxToggleButton {

public:
	wxPropertyBoolean(wxWindow* parent, Property* property);
	~wxPropertyBoolean();

private:
    Property* mProperty;
    void onToggleButton( wxCommandEvent& event );
};

#endif // WXPROPERTYBOOLEAN_H
