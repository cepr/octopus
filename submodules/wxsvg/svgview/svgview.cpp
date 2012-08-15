//////////////////////////////////////////////////////////////////////////////
// Name:        svgview.cpp
// Purpose:     
// Author:      Alex Thuering
// Created:     15/01/2005
// RCS-ID:      $Id: svgview.cpp,v 1.14 2012/04/01 20:37:00 ntalex Exp $
// Copyright:   (c) Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation
#pragma interface
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#ifndef __WXWINCE__
#include <locale.h>
#endif

#include "svgview.h"
#include <wxSVG/svg.h>
#ifdef USE_LIBAV
#include <wxSVG/mediadec_ffmpeg.h>
#endif

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Application /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

IMPLEMENT_APP(SVGViewApp)

bool SVGViewApp::OnInit()
{
#ifndef __WXWINCE__
  setlocale(LC_NUMERIC, "C");
#endif
  //wxLog::SetActiveTarget(new wxLogStderr);
  wxInitAllImageHandlers();
#ifdef USE_LIBAV
  wxFfmpegMediaDecoder::Init();
#endif
  
  new MainFrame(NULL, wxT("SVG Viewer"),
    wxDefaultPosition, wxSize(500, 400));
  return true;
}

//////////////////////////////////////////////////////////////////////////////
////////////////////////////////  MainFrame //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
enum
{
  wxID_FIT = 1,
  wxID_HITTEST,
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
  EVT_MENU(wxID_SAVE, MainFrame::OnSave)
  EVT_MENU(wxID_FIT, MainFrame::Fit)
  EVT_MENU(wxID_HITTEST, MainFrame::Hittest)
  EVT_MENU(wxID_EXIT, MainFrame::OnExit)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MySVGCanvas, wxSVGCtrl)
    EVT_LEFT_UP (MySVGCanvas::OnMouseLeftUp)
END_EVENT_TABLE()


MainFrame::MainFrame(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
		wxFrame(parent, wxID_ANY, title, pos, size, style) {
    // Make a menubar
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_OPEN, _T("&Open...\tCtrl-O"));
    fileMenu->Append(wxID_SAVE, _T("&Save as...\tCtrl-S"));
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, _T("&Exit\tAlt-X"));
    fileMenu->AppendSeparator();
    fileMenu->AppendCheckItem(wxID_FIT, _T("&FitToFrame"))->Check();
    fileMenu->AppendCheckItem(wxID_HITTEST, _T("&Hit-Test"));
    
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, _T("&File"));
    SetMenuBar(menuBar);

    m_svgCtrl = new MySVGCanvas(this);
    if (wxTheApp->argc > 1)
      m_svgCtrl->Load(wxTheApp->argv[1]);
    else
      m_svgCtrl->Load(_T("tiger.svg"));
    
    Center();
    Show(true);
}

void MainFrame::OnOpen(wxCommandEvent& event)
{
  wxString filename = wxFileSelector(_T("Choose a file to open"),
    _T(""), _T(""), _T(""), _T("SVG files (*.svg)|*.svg|All files (*.*)|*.*"));
  if (!filename.empty())
    m_svgCtrl->Load(filename);
}

void MainFrame::OnSave(wxCommandEvent& event)
{
  wxString filename = wxFileSelector(_T("Choose a file to save"),
    _T(""), _T(""), _T(""), _T("SVG files (*.svg)|*.svg|All files (*.*)|*.*"), wxFD_SAVE);
  if (!filename.empty())
    m_svgCtrl->GetSVG()->Save(filename);
}

void MainFrame::Hittest(wxCommandEvent& event)
{
  m_svgCtrl->SetShowHitPopup(event.IsChecked());
}

void MainFrame::Fit(wxCommandEvent& event)
{
  m_svgCtrl->SetFitToFrame(event.IsChecked());
  m_svgCtrl->Update();
}

void MainFrame::OnExit( wxCommandEvent& WXUNUSED(event) )
{
  Close(true);
}

MySVGCanvas::MySVGCanvas(wxWindow* parent):
 wxSVGCtrl(parent), m_ShowHitPopup(false)
{
}

void MySVGCanvas::SetShowHitPopup(bool show)
{
	m_ShowHitPopup = show;
}

void MySVGCanvas::OnMouseLeftUp (wxMouseEvent & event)
{	
  	if(m_ShowHitPopup)
  	{
	    wxSVGDocument* my_doc =  GetSVG();
	    wxSVGSVGElement* my_root = my_doc->GetRootElement();
	    wxSVGRect rect(event.m_x,event.m_y, 1, 1);
		wxNodeList clicked = my_root->GetIntersectionList(rect, *my_root);
		wxString message;
	    message.Printf(_T("Click : %d,%d                  \n"),event.m_x,event.m_y);
	    for(unsigned int i=0;  i<clicked.GetCount(); i++)
	    {
			wxString obj_desc;
	    	wxSVGElement* obj = clicked.Item(i);
	    	obj_desc.Printf(_T("Name : %s, Id : %s\n"), obj->GetName().c_str(), obj->GetId().c_str());
	    	message.Append(obj_desc);
	    }
	    wxMessageBox(message, _T("Hit Test (objects bounding box)"));
  	}
}