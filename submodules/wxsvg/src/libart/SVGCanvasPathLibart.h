//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasPathLibart.h
// Purpose:     Libart canvas path
// Author:      Alex Thuering
// Created:     2005/05/06
// RCS-ID:      $Id: SVGCanvasPathLibart.h,v 1.4 2006/01/08 12:27:04 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_CANVAS_PATH_LIBART_H
#define WX_SVG_CANVAS_PATH_LIBART_H

#include "SVGCanvas.h"
#include <libart_lgpl/libart.h>

class wxSVGCanvasPathLibart: public wxSVGCanvasPath
{
  protected:
	ArtBpath* m_bpath;
	int m_count;
	int m_size;
	int m_moveto_idx;
	
  public:
	wxSVGCanvasPathLibart();
	virtual ~wxSVGCanvasPathLibart();
    
	ArtBpath& AddBPath();
	void End();
	ArtBpath* GetBPath() { return m_bpath; }
	int GetCount() { return m_count; }
    ArtSVP* CreateStrokeSVP(const wxCSSStyleDeclaration& style,
      ArtVpath* vpath, double ratio = 1);
	
	wxSVGRect GetBBox(const wxSVGMatrix& matrix = *(wxSVGMatrix*)NULL);
    wxSVGRect GetResultBBox(const wxCSSStyleDeclaration& style,
      const wxSVGMatrix& matrix = *(wxSVGMatrix*)NULL);
	
	void MoveToImpl(double x, double y);
	void LineToImpl(double x, double y);
	void CurveToCubicImpl(double x1, double y1, double x2, double y2, double x, double y);
	bool ClosePathImpl();
};

#endif // WX_SVG_CANVAS_PATH_LIBART_H
