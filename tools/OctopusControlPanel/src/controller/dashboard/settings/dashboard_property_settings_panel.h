///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DASHBOARD_PROPERTY_SETTINGS_PANEL_H__
#define __DASHBOARD_PROPERTY_SETTINGS_PANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "settings/wx_numeric_text_ctrl.h"
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DashboardPropertySettingsPanel
///////////////////////////////////////////////////////////////////////////////
class DashboardPropertySettingsPanel : public wxPanel 
{
	private:
	
	protected:
		wxCheckBox* mLayoutVisible;
		wxStaticText* m_staticTextChildrenLayout;
		wxChoice* mLayoutChildrenOrientation;
		wxStaticText* m_staticTextLayoutProportion;
		wxNumericTextCtrl* mLayoutProportion;
		wxCheckBox* mLayoutStretch;
		wxStaticText* m_staticText10;
		wxChoice* mControlType;
		wxStaticText* m_staticText6;
		wxChoice* mControlOrientation;
		wxCheckBox* mControlReverse;
		wxCheckBox* mRefreshPolling;
		wxStaticText* m_staticText9;
		wxNumericTextCtrl* mRefreshPeriod;
	
	public:
		
		DashboardPropertySettingsPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~DashboardPropertySettingsPanel();
	
};

#endif //__DASHBOARD_PROPERTY_SETTINGS_PANEL_H__
