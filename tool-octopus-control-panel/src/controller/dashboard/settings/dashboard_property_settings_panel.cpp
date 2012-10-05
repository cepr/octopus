///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dashboard_property_settings_panel.h"

///////////////////////////////////////////////////////////////////////////

DashboardPropertySettingsPanel::DashboardPropertySettingsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerLayout;
	sbSizerLayout = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Layout") ), wxVERTICAL );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );
	
	
	gSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mLayoutVisible = new wxCheckBox( this, wxID_ANY, wxT("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( mLayoutVisible, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextChildrenLayout = new wxStaticText( this, wxID_ANY, wxT("Children orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextChildrenLayout->Wrap( -1 );
	gSizer2->Add( m_staticTextChildrenLayout, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mLayoutChildrenOrientationChoices[] = { wxT("Automatic"), wxT("Horizontal"), wxT("Vertical") };
	int mLayoutChildrenOrientationNChoices = sizeof( mLayoutChildrenOrientationChoices ) / sizeof( wxString );
	mLayoutChildrenOrientation = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mLayoutChildrenOrientationNChoices, mLayoutChildrenOrientationChoices, 0 );
	mLayoutChildrenOrientation->SetSelection( 0 );
	gSizer2->Add( mLayoutChildrenOrientation, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_staticTextLayoutProportion = new wxStaticText( this, wxID_ANY, wxT("Proportion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLayoutProportion->Wrap( -1 );
	gSizer2->Add( m_staticTextLayoutProportion, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLayoutProportion = new wxNumericTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( mLayoutProportion, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	gSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mLayoutStretch = new wxCheckBox( this, wxID_ANY, wxT("Stretch"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( mLayoutStretch, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerLayout->Add( gSizer2, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizerLayout, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizerControl;
	sbSizerControl = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Control") ), wxVERTICAL );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	gSizer3->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mControlTypeChoices[] = { wxT("Automatic"), wxT("Slider"), wxT("Gauge"), wxT("Check box"), wxT("Toggle button"), wxT("Plot"), wxT("None") };
	int mControlTypeNChoices = sizeof( mControlTypeChoices ) / sizeof( wxString );
	mControlType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mControlTypeNChoices, mControlTypeChoices, 0 );
	mControlType->SetSelection( 0 );
	gSizer3->Add( mControlType, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer3->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mControlOrientationChoices[] = { wxT("Horizontal"), wxT("Vertical") };
	int mControlOrientationNChoices = sizeof( mControlOrientationChoices ) / sizeof( wxString );
	mControlOrientation = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mControlOrientationNChoices, mControlOrientationChoices, 0 );
	mControlOrientation->SetSelection( 0 );
	gSizer3->Add( mControlOrientation, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	gSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mControlReverse = new wxCheckBox( this, wxID_ANY, wxT("Reverse"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( mControlReverse, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerControl->Add( gSizer3, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizerControl, 0, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizerRefresh;
	sbSizerRefresh = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Refresh") ), wxVERTICAL );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 0, 2, 0, 0 );
	
	
	gSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mRefreshPolling = new wxCheckBox( this, wxID_ANY, wxT("Polling"), wxDefaultPosition, wxDefaultSize, 0 );
	mRefreshPolling->SetToolTip( wxT("Activate this option if the remote device\ndoes not automatically reports new values.") );
	
	gSizer4->Add( mRefreshPolling, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Period (ms)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gSizer4->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRefreshPeriod = new wxNumericTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer4->Add( mRefreshPeriod, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerRefresh->Add( gSizer4, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizerRefresh, 0, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
}

DashboardPropertySettingsPanel::~DashboardPropertySettingsPanel()
{
}
