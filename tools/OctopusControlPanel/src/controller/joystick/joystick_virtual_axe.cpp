#include "joystick_virtual_axe.h"

JoystickVirtualAxe::JoystickVirtualAxe()
{
	Notify();
}

JoystickVirtualAxe::~JoystickVirtualAxe()
{
	// Delete joysticks
	std::vector<T_JOYSTICK_AXE*>::iterator it;
	for (it = mAxes.begin(); it != mAxes.end(); ++it) {
		T_JOYSTICK_AXE* axe = *it;
		if (!axe->mJoystick) {
			delete axe->mJoystick;
		}
	}
}

// Called every seconds to detect new joysticks
void JoystickVirtualAxe::Notify()
{
	bool missing_joystick = false;

	// Create a map of the joysticks to quickly find a joystick by its name and its number
	std::map<wxString, std::vector<int> > joysticks;
	int joy_count = wxJoystick::GetNumberJoysticks();
	for (int i = 0; i<joy_count; i++) {
		wxJoystick joy(i);
		wxString name = joy.GetProductName();
		if (name.IsEmpty()) {
			name = wxT("Generic joystick");
		}
		joysticks[name].push_back(i);
	}

	// For each 
	std::vector<T_JOYSTICK_AXE*>::iterator it;
	for (it = mAxes.begin(); it != mAxes.end(); ++it) {
		T_JOYSTICK_AXE* axe = *it;
		if (!axe->mJoystick) {
			if ((joysticks.find(axe->mJoystickName) != joysticks.end()) && ((int)joysticks[axe->mJoystickName].size() > axe->mJoystickNumber)) {
				// Joystick found
				axe->mJoystick = new wxJoystick(joysticks[axe->mJoystickName][axe->mJoystickNumber]);
			} else {
				// Joystick not present, retry later
				missing_joystick = true;
			}
		}
	}

	// Trigger a new joystick search in 1 second
	if (missing_joystick) {
		Start(1000, true);
	}
}

bool JoystickVirtualAxe::isEnabled()
{
	return mAxes.size() > 0;
}

double JoystickVirtualAxe::GetValue()
{
	double ret = 0.0;

	std::vector<T_JOYSTICK_AXE*>::iterator it;
	for (it = mAxes.begin(); it != mAxes.end(); ++it) {
		T_JOYSTICK_AXE* axe = *it;
		if (axe->mJoystick) {
			if (axe->mIsButton) {
				ret += axe->mJoystick->GetButtonState(axe->mAxeNumber) ? axe->mMax : axe->mMin;
			} else {
				int joy_min = axe->mJoystick->GetXMin();
				int joy_max = axe->mJoystick->GetXMax();
				int joy_val = axe->mJoystick->GetPosition(axe->mAxeNumber);
				ret += (joy_val - joy_min) * (axe->mMax - axe->mMin) / (joy_max - joy_min) + axe->mMin;
			}
		}
	}

	return ret;
}

double JoystickVirtualAxe::GetMax(const wxString& name, int number, bool is_button, int axe_number)
{
	T_JOYSTICK_AXE* axe = FindAxe(name, number, is_button, axe_number);
	return axe ? axe->mMax : 0.0;
}

double JoystickVirtualAxe::GetMin(const wxString& name, int number, bool is_button, int axe_number)
{
	T_JOYSTICK_AXE* axe = FindAxe(name, number, is_button, axe_number);
	return axe ? axe->mMin : 0.0;
}

void JoystickVirtualAxe::SetMax(const wxString& name, int number, bool is_button, int axe_number, double max)
{
	T_JOYSTICK_AXE* axe = FindAxe(name, number, is_button, axe_number);
	if (axe) {
		axe->mMax = max;
	} else if (max != 0.0) {
		axe = new T_JOYSTICK_AXE;
		axe->mJoystickName = name;
		axe->mJoystickNumber = number;
		axe->mJoystick = 0;
		axe->mIsButton = is_button;
		axe->mAxeNumber = axe_number;
		axe->mMin = 0.0;
		axe->mMax = max;
		mAxes.push_back(axe);
		Notify();
	}
}

void JoystickVirtualAxe::SetMin(const wxString& name, int number, bool is_button, int axe_number, double min)
{
	T_JOYSTICK_AXE* axe = FindAxe(name, number, is_button, axe_number);
	if (axe) {
		axe->mMin = min;
	} else if (min != 0.0) {
		axe = new T_JOYSTICK_AXE;
		axe->mJoystickName = name;
		axe->mJoystickNumber = number;
		axe->mJoystick = 0;
		axe->mIsButton = is_button;
		axe->mAxeNumber = axe_number;
		axe->mMin = min;
		axe->mMax = 0.0;
		mAxes.push_back(axe);
		Notify();
	}
}

T_JOYSTICK_AXE* JoystickVirtualAxe::FindAxe(const wxString& name, int number, bool is_button, int axe_number)
{
	std::vector<T_JOYSTICK_AXE*>::iterator it;
	for (it = mAxes.begin(); it != mAxes.end(); ++it) {
		T_JOYSTICK_AXE* axe = *it;
		if ((axe->mJoystickName == name) &&
		    (axe->mJoystickNumber == number) &&
			(axe->mIsButton == is_button) &&
			(axe->mAxeNumber == axe_number)) {
			return axe;
		}
	}
	return 0;
}

