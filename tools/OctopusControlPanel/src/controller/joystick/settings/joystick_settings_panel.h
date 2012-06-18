///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __JOYSTICK_SETTINGS_PANEL_H__
#define __JOYSTICK_SETTINGS_PANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/gdicmn.h>
#include <wx/slider.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class JoystickSettingsPanel
///////////////////////////////////////////////////////////////////////////////
class JoystickSettingsPanel : public wxPanel 
{
	private:
	
	protected:
		wxScrolledWindow* m_scrolledWindow;
		wxStaticBoxSizer* m_JoysticksListSizer;
		wxSlider* mFinalValue;
	
	public:
		
		JoystickSettingsPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~JoystickSettingsPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class JoystickPanel
///////////////////////////////////////////////////////////////////////////////
class JoystickPanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticBoxSizer* m_MainSizer;
		wxCheckBox* m_Enabled;
		wxPanel* m_AxesPanel;
		wxFlexGridSizer* m_AxesListSizer;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onEnabled( wxCommandEvent& event ) = 0;
		
	
	public:
		
		JoystickPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~JoystickPanel();
	
};

#endif //__JOYSTICK_SETTINGS_PANEL_H__
