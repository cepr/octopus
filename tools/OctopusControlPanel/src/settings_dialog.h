///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __properties_dialog__
#define __properties_dialog__

class wxNumericTextCtrl;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/slider.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PropertiesDialog
///////////////////////////////////////////////////////////////////////////////
class SettingsDialog : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_TitlePanel;
		wxStaticText* m_staticTextName;
		wxStaticText* m_staticTextDescription;
		wxStaticText* m_staticTextProperties;
		wxStaticLine* m_staticline1;
		wxNotebook* m_notebook1;
		wxScrolledWindow* m_AppearanceTab;
		
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
		wxScrolledWindow* m_KeyboardTab;
		wxStaticText* m_staticText11;
		wxChoice* mKeyboardKeyA;
		wxStaticText* m_staticText19;
		wxNumericTextCtrl* mKeyboardValueA;
		wxStaticText* m_staticText20;
		wxNumericTextCtrl* mKeyboardReleaseA;
		wxStaticText* m_staticText21;
		wxChoice* mKeyboardKeyB;
		wxStaticText* m_staticText22;
		wxNumericTextCtrl* mKeyboardValueB;
		wxStaticText* m_staticText23;
		wxNumericTextCtrl* mKeyboardReleaseB;
		wxScrolledWindow* m_JoystickTab;
		wxStaticText* m_staticText17;
		wxChoice* mJoystickDevice;
		wxStaticText* m_staticText18;
		wxChoice* mJoystickAxis1;
		wxStaticText* m_staticText24;
		wxNumericTextCtrl* mJoystickReleasePosition1;
		wxStaticText* m_staticText26;
		wxNumericTextCtrl* mJoystickDeadZone1;
		wxStaticText* m_staticText25;
		wxNumericTextCtrl* mJoystickRatio1;
		wxSlider* mJoystickAxis1Value;
		wxStaticText* m_staticText182;
		wxChoice* mJoystickAxis2;
		wxStaticText* m_staticText241;
		wxNumericTextCtrl* mJoystickReleasePosition2;
		wxStaticText* m_staticText261;
		wxNumericTextCtrl* mJoystickDeadZone2;
		wxStaticText* m_staticText251;
		wxNumericTextCtrl* mJoystickRatio2;
		wxSlider* mJoystickAxis2Value;
		wxStaticText* m_staticText30;
		wxNumericTextCtrl* mJoystickPropertyOffset;
		wxStaticText* m_staticText28;
		wxNumericTextCtrl* mJoystickPropertyMinimum;
		wxStaticText* m_staticText281;
		wxNumericTextCtrl* mJoystickPropertyMaximum;
		wxSlider* mJoystickPropertyValue;
		wxStaticLine* m_staticline2;
		wxStdDialogButtonSizer* mOkCancel;
		wxButton* mOkCancelOK;
		wxButton* mOkCancelApply;
		wxButton* mOkCancelCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onJoystickDeviceSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void onJoystickAxis1Selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void onJoystickAxis2Selected( wxCommandEvent& event ) { event.Skip(); }
		virtual void onApplyButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SettingsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 773,948 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER ); 
		~SettingsDialog();
	
};

#endif //__properties_dialog__
