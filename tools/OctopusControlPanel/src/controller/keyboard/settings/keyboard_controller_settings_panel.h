///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __KEYBOARD_CONTROLLER_SETTINGS_PANEL_H__
#define __KEYBOARD_CONTROLLER_SETTINGS_PANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "settings/wx_numeric_text_ctrl.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class KeyboardControllerSettingsPanel
///////////////////////////////////////////////////////////////////////////////
class KeyboardControllerSettingsPanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticTextKeyA;
		wxChoice* mKeyboardKeyA;
		wxStaticText* m_staticTextValueA;
		wxNumericTextCtrl* mKeyboardValueA;
		wxStaticText* m_staticTextReleaseA;
		wxNumericTextCtrl* mKeyboardReleaseA;
		wxStaticText* m_staticTextKeyB;
		wxChoice* mKeyboardKeyB;
		wxStaticText* m_staticTextValueB;
		wxNumericTextCtrl* mKeyboardValueB;
		wxStaticText* m_staticTextReleaseB;
		wxNumericTextCtrl* mKeyboardReleaseB;
	
	public:
		
		KeyboardControllerSettingsPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~KeyboardControllerSettingsPanel();
	
};

#endif //__KEYBOARD_CONTROLLER_SETTINGS_PANEL_H__
