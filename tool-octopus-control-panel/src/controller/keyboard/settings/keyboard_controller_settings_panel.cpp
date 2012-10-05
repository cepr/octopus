///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "keyboard_controller_settings_panel.h"

///////////////////////////////////////////////////////////////////////////

KeyboardControllerSettingsPanel::KeyboardControllerSettingsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerKeyA;
	sbSizerKeyA = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Key A") ), wxVERTICAL );
	
	wxGridSizer* gSizerKeyA;
	gSizerKeyA = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticTextKeyA = new wxStaticText( this, wxID_ANY, wxT("Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextKeyA->Wrap( -1 );
	gSizerKeyA->Add( m_staticTextKeyA, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mKeyboardKeyAChoices[] = { wxT("Unused"), wxT("Up"), wxT("Down"), wxT("Left"), wxT("Right") };
	int mKeyboardKeyANChoices = sizeof( mKeyboardKeyAChoices ) / sizeof( wxString );
	mKeyboardKeyA = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mKeyboardKeyANChoices, mKeyboardKeyAChoices, 0 );
	mKeyboardKeyA->SetSelection( 0 );
	gSizerKeyA->Add( mKeyboardKeyA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextValueA = new wxStaticText( this, wxID_ANY, wxT("Value to set on key press"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextValueA->Wrap( -1 );
	gSizerKeyA->Add( m_staticTextValueA, 0, wxALL, 5 );
	
	mKeyboardValueA = new wxNumericTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizerKeyA->Add( mKeyboardValueA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextReleaseA = new wxStaticText( this, wxID_ANY, wxT("Value to set on key release"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextReleaseA->Wrap( -1 );
	gSizerKeyA->Add( m_staticTextReleaseA, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mKeyboardReleaseA = new wxNumericTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizerKeyA->Add( mKeyboardReleaseA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	
	sbSizerKeyA->Add( gSizerKeyA, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizerKeyA, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizerKeyB;
	sbSizerKeyB = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Key B") ), wxVERTICAL );
	
	wxGridSizer* gSizerKeyB;
	gSizerKeyB = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticTextKeyB = new wxStaticText( this, wxID_ANY, wxT("Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextKeyB->Wrap( -1 );
	gSizerKeyB->Add( m_staticTextKeyB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mKeyboardKeyBChoices[] = { wxT("Unused"), wxT("Up"), wxT("Down"), wxT("Left"), wxT("Right") };
	int mKeyboardKeyBNChoices = sizeof( mKeyboardKeyBChoices ) / sizeof( wxString );
	mKeyboardKeyB = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mKeyboardKeyBNChoices, mKeyboardKeyBChoices, 0 );
	mKeyboardKeyB->SetSelection( 0 );
	gSizerKeyB->Add( mKeyboardKeyB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextValueB = new wxStaticText( this, wxID_ANY, wxT("Value to set on key press"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextValueB->Wrap( -1 );
	gSizerKeyB->Add( m_staticTextValueB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mKeyboardValueB = new wxNumericTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizerKeyB->Add( mKeyboardValueB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextReleaseB = new wxStaticText( this, wxID_ANY, wxT("Value to set on key release"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextReleaseB->Wrap( -1 );
	gSizerKeyB->Add( m_staticTextReleaseB, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mKeyboardReleaseB = new wxNumericTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizerKeyB->Add( mKeyboardReleaseB, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerKeyB->Add( gSizerKeyB, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizerKeyB, 0, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

KeyboardControllerSettingsPanel::~KeyboardControllerSettingsPanel()
{
}
