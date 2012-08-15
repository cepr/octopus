//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasTextFreetype.h
// Purpose:     Freetype canvas text
// Author:      Alex Thuering
// Created:     2005/05/23
// RCS-ID:      $Id: SVGCanvasTextFreetype.h,v 1.6 2006/01/08 11:54:16 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_CANVAS_TEXT_FREETYPE_H
#define WX_SVG_CANVAS_TEXT_FREETYPE_H

#include "SVGCanvasItem.h"

#include <pango/pangoft2.h>

class wxSVGCanvasTextFreetype: public wxSVGCanvasText
{
  public:
	wxSVGCanvasTextFreetype(wxSVGCanvas* canvas);
	~wxSVGCanvasTextFreetype();
	
	void Init(wxSVGTextElement& element,
	  const wxCSSStyleDeclaration& style);
	
  public:
	double m_dpi_x;
	double m_dpi_y;
    static PangoFT2FontMap* s_fontmap;
	PangoContext* m_pango_context;
	PangoLayout* m_layout;
	char* m_font_family;
	double m_offset_x;
	double m_offset_y;
	bool m_endpath;
	virtual void InitText(const wxString& text, const wxCSSStyleDeclaration& style);
	void RenderLine(PangoLayoutLine *line, int x, int y);
	int RenderGlyphs(PangoFont* font, PangoGlyphString* glyphs, int x, int y);
};

#endif // WX_SVG_CANVAS_TEXT_FREETYPE_H
