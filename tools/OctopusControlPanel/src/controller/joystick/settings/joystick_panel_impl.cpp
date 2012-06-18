#include "joystick_panel_impl.h"
#include <wx/event.h>

JoystickPanelImpl::JoystickPanelImpl(wxWindow* parent, wxJoystick* joystick, JoystickVirtualAxe* virtual_axe, int number) :
	JoystickPanel(parent),
	mJoystick(joystick),
	mVirtualAxe(virtual_axe),
	mJoystickNumber(number)
{
	// Joystick name
	wxString name = mJoystick->GetProductName();
	m_MainSizer->GetStaticBox()->SetLabel(name << " #" << (number + 1));

	// Fill m_AxesPanel with all axes and buttons
	int i, axes_count = mJoystick->GetNumberAxes(), buttons_count = mJoystick->GetNumberButtons();
	int min = mJoystick->GetXMin();
	int max = mJoystick->GetXMax();
	for (i=0; i<axes_count; i++) {
		T_AXE* axe = new T_AXE();
		axe->m_Index = i;

		axe->m_Min = new wxNumericTextCtrl(
				m_AxesPanel,
				wxID_ANY,
				wxString::FromDouble(virtual_axe->GetMin(name, number, false, i)),
				wxDefaultPosition,
				wxDefaultSize,
				0 );
		m_AxesListSizer->Add( axe->m_Min, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );

		axe->m_Gauge = new wxGauge( m_AxesPanel, wxID_ANY, max-min, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
		m_AxesListSizer->Add( axe->m_Gauge, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

		axe->m_Max = new wxNumericTextCtrl(
				m_AxesPanel,
				wxID_ANY,
				wxString::FromDouble(virtual_axe->GetMax(name, number, false, i)),
				wxDefaultPosition,
				wxDefaultSize,
				0 );
		m_AxesListSizer->Add( axe->m_Max, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );

		mAxes.push_back(axe);
	}

	for (i=0; i<buttons_count; i++) {
		T_AXE* button = new T_AXE();
		button->m_Index = i;

		button->m_Min = new wxNumericTextCtrl(
				m_AxesPanel,
				wxID_ANY,
				wxString::FromDouble(virtual_axe->GetMin(name, number, true, i)),
				wxDefaultPosition,
				wxDefaultSize,
				0 );
		m_AxesListSizer->Add( button->m_Min, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );

		button->m_Gauge = new wxGauge( m_AxesPanel, wxID_ANY, 1, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
		m_AxesListSizer->Add( button->m_Gauge, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

		button->m_Max = new wxNumericTextCtrl(
				m_AxesPanel,
				wxID_ANY,
				wxString::FromDouble(virtual_axe->GetMax(name, number, true, i)),
				wxDefaultPosition,
				wxDefaultSize,
				0 );
		m_AxesListSizer->Add( button->m_Max, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );

		mButtons.push_back(button);
	}

	// Force a refresh
	wxJoystickEvent evt;
	onJoystickEvent(evt);

	Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(JoystickPanelImpl::onTextChanged));
	Connect(wxEVT_JOY_BUTTON_DOWN, wxJoystickEventHandler(JoystickPanelImpl::onJoystickEvent));
	Connect(wxEVT_JOY_BUTTON_UP, wxJoystickEventHandler(JoystickPanelImpl::onJoystickEvent));
	Connect(wxEVT_JOY_MOVE, wxJoystickEventHandler(JoystickPanelImpl::onJoystickEvent));
	Connect(wxEVT_JOY_ZMOVE, wxJoystickEventHandler(JoystickPanelImpl::onJoystickEvent));
	mJoystick->SetCapture(this, 100);
}

JoystickPanelImpl::~JoystickPanelImpl()
{
	mJoystick->ReleaseCapture();
	std::vector<T_AXE*>::iterator it;
	// Delete axes
	for (it = mAxes.begin(); it != mAxes.end(); ++it ) {
		T_AXE* axe = (*it);
		delete axe;
	}
	// Delete buttons
	for (it = mButtons.begin(); it != mButtons.end(); ++it ) {
		T_AXE* button = (*it);
		delete button;
	}
}

void JoystickPanelImpl::onJoystickEvent(wxJoystickEvent& event)
{
	std::vector<T_AXE*>::iterator it;
	int min = mJoystick->GetXMin();

	// Refresh axes
	for (it = mAxes.begin(); it != mAxes.end(); ++it ) {
		T_AXE* axe = (*it);
		int pos = mJoystick->GetPosition(axe->m_Index);
		axe->m_Gauge->SetValue(pos - min);
	}

	// Refresh buttons
	for (it = mButtons.begin(); it != mButtons.end(); ++it ) {
		T_AXE* button = (*it);
		bool state = mJoystick->GetButtonState(button->m_Index);
		button->m_Gauge->SetValue(state ? 1 : 0);
	}
}

void JoystickPanelImpl::onEnabled(wxCommandEvent& event)
{
	if (m_Enabled->IsChecked()) {
		m_AxesPanel->Show();
	} else {
		m_AxesPanel->Hide();
	}
	GetGrandParent()->Layout();
}

void JoystickPanelImpl::onTextChanged(wxCommandEvent& event)
{
	wxString name = mJoystick->GetProductName();
	std::vector<T_AXE*>::iterator it;

	// Refresh axes
	for (it = mAxes.begin(); it != mAxes.end(); ++it ) {
		T_AXE* axe = (*it);
		mVirtualAxe->SetMin(name, mJoystickNumber, false, axe->m_Index, *axe->m_Min);
		mVirtualAxe->SetMax(name, mJoystickNumber, false, axe->m_Index, *axe->m_Max);
	}

	// Refresh buttons
	for (it = mButtons.begin(); it != mButtons.end(); ++it ) {
		T_AXE* button = (*it);
		mVirtualAxe->SetMin(name, mJoystickNumber, true, button->m_Index, *button->m_Min);
		mVirtualAxe->SetMax(name, mJoystickNumber, true, button->m_Index, *button->m_Max);
	}
}
