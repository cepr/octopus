#ifndef JOYSTICKSETTINGSPANELIMPL_H
#define JOYSTICKSETTINGSPANELIMPL_H

#include "joystick_settings_panel.h" // Base class: JoystickSettingsPanel
#include "joystick_panel_impl.h"
#include "controller/joystick/joystick_virtual_axe.h"
#include <wx/timer.h>

class JoystickSettingsPanelImpl : public JoystickSettingsPanel, private wxTimer {

private:
	std::vector<JoystickPanelImpl*> mJoystickPanels;
	void Notify();
	JoystickVirtualAxe* mVirtualAxe;

public:
	JoystickSettingsPanelImpl(wxWindow* parent, JoystickVirtualAxe* virtual_axe);
	~JoystickSettingsPanelImpl();
	virtual void onJoystickTextCtrlChanged(wxCommandEvent& event);
};

#endif // JOYSTICKSETTINGSPANELIMPL_H
