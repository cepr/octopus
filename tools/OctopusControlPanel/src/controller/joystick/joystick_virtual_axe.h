#ifndef JOYSTICKVIRTUALAXE_H
#define JOYSTICKVIRTUALAXE_H

#include <wx/timer.h>
#include <wx/string.h>
#include <wx/joystick.h>
#include <vector>
#include <map>

typedef struct {
	wxString		mJoystickName;		// Joystick name as reported by wxJoystick::GetProductName
	int				mJoystickNumber;	// Joystick number with same name
	wxJoystick*		mJoystick;			// Joystick
	bool			mIsButton;			// Defines whether the axe is a real axe or a button
	int             mAxeNumber;			// Defines the axe or button number to use
	double			mMin;				// Defines the minimal value of the axe
	double			mMax;				// Defines the maximal value of the axe
} T_JOYSTICK_AXE;

class JoystickVirtualAxe : private wxTimer
{
private:
	std::vector<T_JOYSTICK_AXE*> mAxes;
	T_JOYSTICK_AXE* FindAxe(const wxString & name, int number, bool is_button, int axe_number);
	void Notify();

public:
	JoystickVirtualAxe();
	~JoystickVirtualAxe();
	bool isEnabled();
	double GetValue();
	double GetMin(const wxString & name, int number, bool is_button, int axe_number);
	void SetMin(const wxString & name, int number, bool is_button, int axe_number, double min);
	double GetMax(const wxString & name, int number, bool is_button, int axe_number);
	void SetMax(const wxString & name, int number, bool is_button, int axe_number, double max);
};

#endif // JOYSTICKVIRTUALAXE_H
