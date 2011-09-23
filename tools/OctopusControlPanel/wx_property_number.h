#ifndef WXPROPERTYNUMBER_H
#define WXPROPERTYNUMBER_H

#include <wx/slider.h> // Base class: wxSlider
#include <wx/timer.h>
#include "Property.h"

class wxPropertyNumber : public wxSlider {

    class RefreshTimer : public wxTimer {
    private:
        wxPropertyNumber* mParent;
    public:
        RefreshTimer(wxPropertyNumber* parent) : mParent(parent) {  }
        void Notify() { mParent->Refresh(); }
    };

public:
	wxPropertyNumber(wxWindow* parent, Property* property);
	~wxPropertyNumber();

private:
    Property* mProperty;
    void onScroll( wxScrollEvent& event );
    RefreshTimer mTimer;
    void Refresh();
};

#endif // WXPROPERTYNUMBER_H
