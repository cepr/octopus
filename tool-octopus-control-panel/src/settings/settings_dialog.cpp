///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "settings_dialog.h"

///////////////////////////////////////////////////////////////////////////

SettingsDialog::SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_TitlePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_TitlePanel->SetForegroundColour( wxColour( 255, 255, 255 ) );
	m_TitlePanel->SetBackgroundColour( wxColour( 217, 176, 134 ) );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextName = new wxStaticText( m_TitlePanel, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextName->Wrap( -1 );
	m_staticTextName->SetFont( wxFont( 16, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer4->Add( m_staticTextName, 0, wxALL, 5 );
	
	m_staticTextDescription = new wxStaticText( m_TitlePanel, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDescription->Wrap( -1 );
	m_staticTextDescription->SetFont( wxFont( 10, 70, 93, 90, false, wxEmptyString ) );
	
	bSizer4->Add( m_staticTextDescription, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );
	
	m_staticTextProperties = new wxStaticText( m_TitlePanel, wxID_ANY, wxT("Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextProperties->Wrap( -1 );
	m_staticTextProperties->SetFont( wxFont( 24, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer3->Add( m_staticTextProperties, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	m_TitlePanel->SetSizer( bSizer3 );
	m_TitlePanel->Layout();
	bSizer3->Fit( m_TitlePanel );
	bSizer2->Add( m_TitlePanel, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND, 5 );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_LEFT );
	m_AppearanceTab = new wxScrolledWindow( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_AppearanceTab->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerLayout;
	sbSizerLayout = new wxStaticBoxSizer( new wxStaticBox( m_AppearanceTab, wxID_ANY, wxT("Layout") ), wxVERTICAL );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 2, 0, 0 );
	
	
	gSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mLayoutVisible = new wxCheckBox( m_AppearanceTab, wxID_ANY, wxT("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( mLayoutVisible, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextChildrenLayout = new wxStaticText( m_AppearanceTab, wxID_ANY, wxT("Children orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextChildrenLayout->Wrap( -1 );
	gSizer7->Add( m_staticTextChildrenLayout, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mLayoutChildrenOrientationChoices[] = { wxT("Automatic"), wxT("Horizontal"), wxT("Vertical") };
	int mLayoutChildrenOrientationNChoices = sizeof( mLayoutChildrenOrientationChoices ) / sizeof( wxString );
	mLayoutChildrenOrientation = new wxChoice( m_AppearanceTab, wxID_ANY, wxDefaultPosition, wxDefaultSize, mLayoutChildrenOrientationNChoices, mLayoutChildrenOrientationChoices, 0 );
	mLayoutChildrenOrientation->SetSelection( 0 );
	gSizer7->Add( mLayoutChildrenOrientation, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextLayoutProportion = new wxStaticText( m_AppearanceTab, wxID_ANY, wxT("Proportion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLayoutProportion->Wrap( -1 );
	gSizer7->Add( m_staticTextLayoutProportion, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLayoutProportion = new wxNumericTextCtrl( m_AppearanceTab, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( mLayoutProportion, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	gSizer7->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mLayoutStretch = new wxCheckBox( m_AppearanceTab, wxID_ANY, wxT("Stretch"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer7->Add( mLayoutStretch, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerLayout->Add( gSizer7, 0, wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizerLayout, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizerControl;
	sbSizerControl = new wxStaticBoxSizer( new wxStaticBox( m_AppearanceTab, wxID_ANY, wxT("Control") ), wxVERTICAL );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText10 = new wxStaticText( m_AppearanceTab, wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	gSizer3->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mControlTypeChoices[] = { wxT("Automatic"), wxT("Slider"), wxT("Gauge"), wxT("Check box"), wxT("Toggle button"), wxT("Plot"), wxT("None") };
	int mControlTypeNChoices = sizeof( mControlTypeChoices ) / sizeof( wxString );
	mControlType = new wxChoice( m_AppearanceTab, wxID_ANY, wxDefaultPosition, wxDefaultSize, mControlTypeNChoices, mControlTypeChoices, 0 );
	mControlType->SetSelection( 0 );
	gSizer3->Add( mControlType, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( m_AppearanceTab, wxID_ANY, wxT("Orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer3->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mControlOrientationChoices[] = { wxT("Horizontal"), wxT("Vertical") };
	int mControlOrientationNChoices = sizeof( mControlOrientationChoices ) / sizeof( wxString );
	mControlOrientation = new wxChoice( m_AppearanceTab, wxID_ANY, wxDefaultPosition, wxDefaultSize, mControlOrientationNChoices, mControlOrientationChoices, 0 );
	mControlOrientation->SetSelection( 0 );
	gSizer3->Add( mControlOrientation, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	gSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mControlReverse = new wxCheckBox( m_AppearanceTab, wxID_ANY, wxT("Reverse"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( mControlReverse, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerControl->Add( gSizer3, 0, wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizerControl, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizerRefresh;
	sbSizerRefresh = new wxStaticBoxSizer( new wxStaticBox( m_AppearanceTab, wxID_ANY, wxT("Refresh") ), wxVERTICAL );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );
	
	
	gSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mRefreshPolling = new wxCheckBox( m_AppearanceTab, wxID_ANY, wxT("Polling"), wxDefaultPosition, wxDefaultSize, 0 );
	mRefreshPolling->SetToolTip( wxT("Activate this option if the remote device\ndoes not automatically reports new values.") );
	
	gSizer2->Add( mRefreshPolling, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( m_AppearanceTab, wxID_ANY, wxT("Period (ms)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gSizer2->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRefreshPeriod = new wxNumericTextCtrl( m_AppearanceTab, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( mRefreshPeriod, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerRefresh->Add( gSizer2, 0, wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizerRefresh, 0, wxEXPAND|wxALL, 5 );
	
	
	m_AppearanceTab->SetSizer( bSizer5 );
	m_AppearanceTab->Layout();
	bSizer5->Fit( m_AppearanceTab );
	m_notebook1->AddPage( m_AppearanceTab, wxT("Appearance"), false );
	m_KeyboardTab = new wxScrolledWindow( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_KeyboardTab->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_KeyboardTab, wxID_ANY, wxT("Key A") ), wxVERTICAL );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText11 = new wxStaticText( m_KeyboardTab, wxID_ANY, wxT("Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gSizer4->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mKeyboardKeyAChoices[] = { wxT("Unused"), wxT("Up"), wxT("Down"), wxT("Left"), wxT("Right") };
	int mKeyboardKeyANChoices = sizeof( mKeyboardKeyAChoices ) / sizeof( wxString );
	mKeyboardKeyA = new wxChoice( m_KeyboardTab, wxID_ANY, wxDefaultPosition, wxDefaultSize, mKeyboardKeyANChoices, mKeyboardKeyAChoices, 0 );
	mKeyboardKeyA->SetSelection( 0 );
	gSizer4->Add( mKeyboardKeyA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticText19 = new wxStaticText( m_KeyboardTab, wxID_ANY, wxT("Value to set on key press"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	gSizer4->Add( m_staticText19, 0, wxALL, 5 );
	
	mKeyboardValueA = new wxNumericTextCtrl( m_KeyboardTab, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer4->Add( mKeyboardValueA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticText20 = new wxStaticText( m_KeyboardTab, wxID_ANY, wxT("Value to set on key release"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	gSizer4->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mKeyboardReleaseA = new wxNumericTextCtrl( m_KeyboardTab, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer4->Add( mKeyboardReleaseA, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	
	sbSizer10->Add( gSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer19->Add( sbSizer10, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_KeyboardTab, wxID_ANY, wxT("Key B") ), wxVERTICAL );
	
	wxGridSizer* gSizer91;
	gSizer91 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText21 = new wxStaticText( m_KeyboardTab, wxID_ANY, wxT("Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	gSizer91->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mKeyboardKeyBChoices[] = { wxT("Unused"), wxT("Up"), wxT("Down"), wxT("Left"), wxT("Right") };
	int mKeyboardKeyBNChoices = sizeof( mKeyboardKeyBChoices ) / sizeof( wxString );
	mKeyboardKeyB = new wxChoice( m_KeyboardTab, wxID_ANY, wxDefaultPosition, wxDefaultSize, mKeyboardKeyBNChoices, mKeyboardKeyBChoices, 0 );
	mKeyboardKeyB->SetSelection( 0 );
	gSizer91->Add( mKeyboardKeyB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticText22 = new wxStaticText( m_KeyboardTab, wxID_ANY, wxT("Value to set on key press"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	gSizer91->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mKeyboardValueB = new wxNumericTextCtrl( m_KeyboardTab, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer91->Add( mKeyboardValueB, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticText23 = new wxStaticText( m_KeyboardTab, wxID_ANY, wxT("Value to set on key release"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	gSizer91->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mKeyboardReleaseB = new wxNumericTextCtrl( m_KeyboardTab, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer91->Add( mKeyboardReleaseB, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizer9->Add( gSizer91, 0, wxEXPAND, 5 );
	
	
	bSizer19->Add( sbSizer9, 0, wxEXPAND|wxALL, 5 );
	
	
	m_KeyboardTab->SetSizer( bSizer19 );
	m_KeyboardTab->Layout();
	bSizer19->Fit( m_KeyboardTab );
	m_notebook1->AddPage( m_KeyboardTab, wxT("Keyboard"), false );
	
	bSizer2->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline2, 0, wxEXPAND, 5 );
	
	mOkCancel = new wxStdDialogButtonSizer();
	mOkCancelOK = new wxButton( this, wxID_OK );
	mOkCancel->AddButton( mOkCancelOK );
	mOkCancelApply = new wxButton( this, wxID_APPLY );
	mOkCancel->AddButton( mOkCancelApply );
	mOkCancelCancel = new wxButton( this, wxID_CANCEL );
	mOkCancel->AddButton( mOkCancelCancel );
	mOkCancel->Realize();
	
	bSizer2->Add( mOkCancel, 0, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	mOkCancelApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::onApplyButtonClick ), NULL, this );
	mOkCancelCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::onCancelButtonClick ), NULL, this );
	mOkCancelOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::onOKButtonClick ), NULL, this );
}

SettingsDialog::~SettingsDialog()
{
	// Disconnect Events
	mOkCancelApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::onApplyButtonClick ), NULL, this );
	mOkCancelCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::onCancelButtonClick ), NULL, this );
	mOkCancelOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::onOKButtonClick ), NULL, this );
	
}
