///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 12 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dashboard_property.h"

#include "res/preferences.png.h"
#include "res/reload.png.h"

///////////////////////////////////////////////////////////////////////////

DashboardProperty::DashboardProperty( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	mTitleBar = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	mTitleBar->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_CAPTIONTEXT ) );
	mTitleBar->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVECAPTION ) );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	mStaticTextName = new wxStaticText( mTitleBar, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	mStaticTextName->Wrap( -1 );
	mStaticTextName->SetFont( wxFont( 16, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer3->Add( mStaticTextName, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	mStaticTextDescription = new wxStaticText( mTitleBar, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0 );
	mStaticTextDescription->Wrap( -1 );
	mStaticTextDescription->SetFont( wxFont( 10, 70, 93, 90, false, wxEmptyString ) );
	
	bSizer3->Add( mStaticTextDescription, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	mToolBar = new wxToolBar( mTitleBar, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	mToolBar->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_CAPTIONTEXT ) );
	mToolBar->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVECAPTION ) );
	
	mToolBar->AddTool( wxID_REFRESH, wxT("Refresh"), reload_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Refresh property"), NULL ); 
	mToolBar->AddTool( wxID_PREFERENCES, wxT("Preferences"), preferences_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Display property preferences"), NULL ); 
	mToolBar->Realize(); 
	
	bSizer2->Add( mToolBar, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	mTitleBar->SetSizer( bSizer2 );
	mTitleBar->Layout();
	bSizer2->Fit( mTitleBar );
	bSizer1->Add( mTitleBar, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxID_REFRESH, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( DashboardProperty::onRefreshClick ) );
	this->Connect( wxID_PREFERENCES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( DashboardProperty::onPreferencesClick ) );
}

DashboardProperty::~DashboardProperty()
{
	// Disconnect Events
	this->Disconnect( wxID_REFRESH, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( DashboardProperty::onRefreshClick ) );
	this->Disconnect( wxID_PREFERENCES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( DashboardProperty::onPreferencesClick ) );
	
}
