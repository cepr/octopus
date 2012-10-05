///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 12 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dashboard_property__
#define __dashboard_property__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DashboardProperty
///////////////////////////////////////////////////////////////////////////////
class DashboardProperty : public wxPanel 
{
	private:
	
	protected:
		wxPanel* mTitleBar;
		wxStaticText* mStaticTextName;
		wxStaticText* mStaticTextDescription;
		wxToolBar* mToolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onRefreshClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onPreferencesClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DashboardProperty( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 748,537 ), long style = wxRAISED_BORDER|wxTAB_TRAVERSAL ); 
		~DashboardProperty();
	
};

#endif //__dashboard_property__
