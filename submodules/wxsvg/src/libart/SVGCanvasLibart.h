//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasLibart.h
// Purpose:     Libart render
// Author:      Alex Thuering
// Created:     2005/05/06
// RCS-ID:      $Id: SVGCanvasLibart.h,v 1.11 2011/06/27 21:14:14 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_CANVAS_LIBART_H
#define WX_SVG_CANVAS_LIBART_H

#include "SVGCanvas.h"

#ifndef LIBART_H
class ArtSVP;
class ArtGradientStop;
class ArtGradientLinear;
class ArtGradientRadial;
#endif

class wxSVGCanvasPathLibart;
class wxSVGCanvasTextFreetype;

class wxSVGCanvasLibart: public wxSVGCanvas
{
  public:
	wxSVGCanvasLibart() { }
	
	void Init(int width, int height, bool alpha = false);
    int GetWidth() { return m_image.GetWidth(); }
    int GetHeight() { return m_image.GetHeight(); }
    wxImage GetImage();
	void Clear(wxRGBColor color = wxRGBColor(0xFF,0xFF,0xFF));
	
	wxSVGCanvasPath* CreateCanvasPath();
	wxSVGCanvasItem* CreateItem(wxSVGTextElement* element,
	  const wxCSSStyleDeclaration* style = NULL);
	
	void DrawItem(wxSVGCanvasItem& item, wxSVGMatrix& matrix,
      const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem);
  
  protected:
	wxImage m_image;
	ArtGradientStop* m_stops;
	unsigned int m_nstops;
    
	void DrawCanvasPath(wxSVGCanvasPathLibart& canvasPath, wxSVGMatrix& matrix,
      const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem);
	void DrawSVP(ArtSVP* svp, const wxRGBColor& color, double opacity);
	void DrawSVPLinearGradient(ArtSVP* svp, ArtGradientLinear& gradient);
	void DrawSVPRadialGradient(ArtSVP* svp, ArtGradientRadial& gradient);
	virtual void SetStopValue(unsigned int index, float offset, float opacity,
      const wxRGBColor& rgbColor);
	virtual void AllocateGradientStops(unsigned int stop_count);     
	void PaintSVP(ArtSVP* fillSVP, const wxSVGPaint& paint, float opacity,
      wxSVGMatrix& matrix, const wxSVGSVGElement& svgElem, wxSVGCanvasPath& path);
    
    void DrawCanvasImage(wxSVGCanvasImage& canvasImage, wxSVGMatrix& matrix,
      const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem);
};

#endif // WX_SVG_CANVAS_LIBART_H
