#ifndef JOYSTICKPANELIMPL_H
#define JOYSTICKPANELIMPL_H

#include "joystick_settings_panel.h" // Base class: JoystickPanel
#include "settings/wx_numeric_text_ctrl.h"
#include "controller/joystick/joystick_virtual_axe.h"
#include <wx/joystick.h>
#include <wx/gauge.h>

typedef struct S_AXE {
	int m_Index;
	wxGauge* m_Gauge;
	wxNumericTextCtrl* m_Min;
	wxNumericTextCtrl* m_Max;
} T_AXE;

class JoystickPanelImpl : public JoystickPanel
{
private:
	wxJoystick* mJoystick;
	std::vector<T_AXE*> mAxes;
	std::vector<T_AXE*> mButtons;
	JoystickVirtualAxe* mVirtualAxe;
	int mJoystickNumber;

public:
	JoystickPanelImpl(wxWindow* parent, wxJoystick* joystick, JoystickVirtualAxe* virtual_axe, int number);
	~JoystickPanelImpl();
	void onTextChanged( wxCommandEvent& event );
	void onJoystickEvent(wxJoystickEvent& event);
	void onEnabled(wxCommandEvent& event);
};

#endif // JOYSTICKPANELIMPL_H
