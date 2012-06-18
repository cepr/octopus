#include "joystick_settings_panel_impl.h"
#include <wx/joystick.h>
#include "joystick_panel_impl.h"

JoystickSettingsPanelImpl::JoystickSettingsPanelImpl(wxWindow* parent, JoystickVirtualAxe* virtual_axe) :
		JoystickSettingsPanel(parent),
		mVirtualAxe(virtual_axe)
{
	// Fill m_JoysticksListPanel with all present joysticks
	int count = wxJoystick::GetNumberJoysticks();
	int i;
	std::map<wxString, int> joystick_number;
	for (i=0; i<count; i++) {
		wxJoystick* joy = new wxJoystick(i);
		wxString name = joy->GetProductName();
		if (joystick_number.find(name) == joystick_number.end()) {
			joystick_number[name] = 0;
		} else {
			joystick_number[name]++;
		}
		JoystickPanelImpl* joy_panel = new JoystickPanelImpl(m_scrolledWindow, joy, virtual_axe, joystick_number[name]);
		m_JoysticksListSizer->Add(joy_panel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
		mJoystickPanels.push_back(joy_panel);
	}

	// Start the timer
	Start(10);
}

JoystickSettingsPanelImpl::~JoystickSettingsPanelImpl()
{
}

void JoystickSettingsPanelImpl::onJoystickTextCtrlChanged(wxCommandEvent& event)
{
}

void JoystickSettingsPanelImpl::Notify()
{
	mFinalValue->SetValue(mVirtualAxe->GetValue());
}
