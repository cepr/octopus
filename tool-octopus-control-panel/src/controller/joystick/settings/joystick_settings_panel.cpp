///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "joystick_settings_panel.h"

///////////////////////////////////////////////////////////////////////////

JoystickSettingsPanel::JoystickSettingsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_JoysticksListSizer = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, wxT("Joysticks selection") ), wxVERTICAL );
	
	
	bSizer2->Add( m_JoysticksListSizer, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	mFinalValue = new wxSlider( m_scrolledWindow, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	mFinalValue->Enable( false );
	
	sbSizer3->Add( mFinalValue, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( sbSizer3, 0, wxEXPAND|wxALL, 5 );
	
	
	m_scrolledWindow->SetSizer( bSizer2 );
	m_scrolledWindow->Layout();
	bSizer2->Fit( m_scrolledWindow );
	bSizer1->Add( m_scrolledWindow, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

JoystickSettingsPanel::~JoystickSettingsPanel()
{
}

JoystickPanel::JoystickPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	m_MainSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Joystick 1") ), wxVERTICAL );
	
	m_Enabled = new wxCheckBox( this, wxID_ANY, wxT("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	m_MainSizer->Add( m_Enabled, 0, wxALL, 5 );
	
	m_AxesPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_AxesPanel->Hide();
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_AxesPanel, wxID_ANY, wxT("Axes and buttons") ), wxVERTICAL );
	
	m_AxesListSizer = new wxFlexGridSizer( 0, 3, 0, 0 );
	m_AxesListSizer->AddGrowableCol( 1 );
	m_AxesListSizer->SetFlexibleDirection( wxBOTH );
	m_AxesListSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticText* bstaticText1;
	bstaticText1 = new wxStaticText( m_AxesPanel, wxID_ANY, wxT("min"), wxDefaultPosition, wxDefaultSize, 0 );
	bstaticText1->Wrap( -1 );
	bstaticText1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	bstaticText1->SetToolTip( wxT("Defines the minimum property value corresponding to the minimum axe position.") );
	
	m_AxesListSizer->Add( bstaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_AxesListSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxStaticText* bstaticText2;
	bstaticText2 = new wxStaticText( m_AxesPanel, wxID_ANY, wxT("max"), wxDefaultPosition, wxDefaultSize, 0 );
	bstaticText2->Wrap( -1 );
	bstaticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	bstaticText2->SetToolTip( wxT("Defines the maximum property value corresponding to the maximum axe position.") );
	
	m_AxesListSizer->Add( bstaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	sbSizer2->Add( m_AxesListSizer, 0, wxEXPAND, 5 );
	
	
	m_AxesPanel->SetSizer( sbSizer2 );
	m_AxesPanel->Layout();
	sbSizer2->Fit( m_AxesPanel );
	m_MainSizer->Add( m_AxesPanel, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( m_MainSizer );
	this->Layout();
	m_MainSizer->Fit( this );
	
	// Connect Events
	m_Enabled->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( JoystickPanel::onEnabled ), NULL, this );
}

JoystickPanel::~JoystickPanel()
{
	// Disconnect Events
	m_Enabled->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( JoystickPanel::onEnabled ), NULL, this );
	
}
