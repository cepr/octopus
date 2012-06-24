///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 11 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "main_frame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemAttach;
	m_menuItemAttach = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("&Attach to device...") ) + wxT('\t') + wxT("CTRL+A"), wxT("Attach to an Octopus compatible device."), wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemAttach );
	
	wxMenuItem* m_menuItemDetach;
	m_menuItemDetach = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Detach") ) + wxT('\t') + wxT("CTRL+D"), wxT("Detach the connected device."), wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemDetach );
	m_menuItemDetach->Enable( false );
	
	m_menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( wxT("E&xit") ) + wxT('\t') + wxT("ALT+F4"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemExit );
	
	m_menubar->Append( m_menuFile, wxT("&File") ); 
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItemAbout;
	m_menuItemAbout = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( wxT("&About...") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemAbout );
	
	m_menubar->Append( m_menuHelp, wxT("&Help") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	m_scrolledWindow1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWFRAME ) );
	
	m_RootPropertySizer = new wxBoxSizer( wxVERTICAL );
	
	
	m_scrolledWindow1->SetSizer( m_RootPropertySizer );
	m_scrolledWindow1->Layout();
	m_RootPropertySizer->Fit( m_scrolledWindow1 );
	bSizer1->Add( m_scrolledWindow1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}
