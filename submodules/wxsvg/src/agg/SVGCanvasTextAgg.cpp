//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasTextAgg.cpp
// Purpose:     Agg canvas text
// Author:      Alex Thuering
// Created:     2005/05/20
// RCS-ID:      $Id: SVGCanvasTextAgg.cpp,v 1.12 2011/08/01 20:16:59 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#include "SVGCanvasTextAgg.h"
#include <wx/log.h>

wxSVGCanvasTextAgg::wxSVGCanvasTextAgg(wxSVGCanvas* canvas):
 wxSVGCanvasText(canvas)
{
  #ifdef __WXMSW__
  m_dc = ::GetDC(0);
  m_feng = new font_engine_type(m_dc);
  #else
  m_feng = new font_engine_type();
  #endif 
  m_fman = new font_manager_type(*m_feng);
}

wxSVGCanvasTextAgg::~wxSVGCanvasTextAgg()
{
  delete m_fman;
  delete m_feng;
  #ifdef __WXMSW__
  ::ReleaseDC(0, m_dc);
  #endif 
}

void wxSVGCanvasTextAgg::InitText(const wxString& text,
  const wxCSSStyleDeclaration& style)
{
  wxSVGCanvasTextChunk& chunk = m_chunks[m_chunks.GetCount()-1];
  // set font
  if (style.GetFontSize()<40 && style.GetFontSize()>0)
  {
    m_feng->height(40);
    m_scale = style.GetFontSize()/40;
    chunk.matrix = chunk.matrix.Scale(m_scale);
  }
  else
  {
    m_scale = 1;        
    m_feng->height(style.GetFontSize());
  }
  #ifdef __WXMSW__
  m_feng->italic(style.GetFontStyle() == wxCSS_VALUE_ITALIC);
  
  if (style.GetFontWeight() == wxCSS_VALUE_BOLD)
	m_feng->weight(FW_BOLD);
  else if (style.GetFontWeight() == wxCSS_VALUE_BOLDER)
	m_feng->weight(FW_EXTRABOLD);
  else if (style.GetFontWeight() == wxCSS_VALUE_LIGHTER)
	m_feng->weight(FW_LIGHT);
  else
	m_feng->weight(FW_NORMAL);
  #endif
  m_feng->flip_y(true);
  #ifdef __WXMSW__
  if (!m_feng->create_font(style.GetFontFamily().ToAscii(), glyph_ren_outline))
    m_feng->create_font("", glyph_ren_outline);
  
  // init text
  if (!m_feng->prepare_glyph(127))
    m_feng->create_font("", glyph_ren_outline);
  #else 
  if (!m_feng->load_font(style.GetFontFamily().ToAscii(), 0, glyph_ren_outline))
    m_feng->load_font("", 0, glyph_ren_outline);
  
  // init text
  if (!m_feng->prepare_glyph(127))
    m_feng->load_font("", 0,glyph_ren_outline);
  #endif
  m_fman->precache(' ', 127);
  const char* p = (const char*) text.wc_str();

  while(*p || *(p+1))
  {
    const agg::glyph_cache* glyph = m_fman->glyph(*(const unsigned*)p);
    if(glyph)
    {
      BeginChar();
      double dx = 0, dy = 0;         
      m_fman->add_kerning(&dx, &dy); m_tx += dx*m_scale; m_ty += dy*m_scale;
	  m_fman->init_embedded_adaptors(glyph, m_tx/m_scale, m_ty/m_scale);
      
	  ((wxSVGCanvasPathAgg*)m_char->path)->m_storage.concat_path(m_fman->path_adaptor());
      ((wxSVGCanvasPathAgg*)m_char->path)->m_storage.end_poly(path_flags_close);
	  
	  m_char->bbox = wxSVGRect(m_tx/m_scale, m_ty/m_scale, glyph->advance_x, 0);
	  
      m_tx += glyph->advance_x*m_scale;
      m_ty += glyph->advance_y*m_scale;
      EndChar();
    }
    p += 2;
  }
}

void wxSVGCanvasTextAgg::EndTextAnchor()
{
  if (m_textAnchor != wxCSS_VALUE_START)
  {
	for (int i=m_textAnchorBeginIndex; i<(int)m_chunks.Count(); i++)
	{
	  wxSVGCanvasTextChunk& chunk = m_chunks[i];
	  if (m_textAnchor == wxCSS_VALUE_END)
		chunk.matrix = chunk.matrix.Translate((m_textAnchorBeginPos-m_tx)/m_scale, 0);
	  else if (m_textAnchor == wxCSS_VALUE_MIDDLE)
		chunk.matrix = chunk.matrix.Translate((m_textAnchorBeginPos-m_tx)/2/m_scale, 0);
	}
	if (m_textAnchor == wxCSS_VALUE_END)
	  m_tx = m_textAnchorBeginPos;
	else if (m_textAnchor == wxCSS_VALUE_MIDDLE)
	  m_tx -= (m_textAnchorBeginPos-m_tx)/2;
	m_textAnchor = wxCSS_VALUE_START;
  }
  if (m_dominantBaseline != wxCSS_VALUE_AUTO
  		&& m_dominantBaseline != wxCSS_VALUE_ALPHABETIC)
  {
	for (int i=m_dominantBaselineBeginIndex; i<(int)m_chunks.Count(); i++)
	{
		wxSVGCanvasTextChunk& chunk = m_chunks[i];
		wxSVGRect chunkBBox = chunk.GetBBox();
		if (chunkBBox.IsEmpty())
			continue;
		if (m_dominantBaseline == wxCSS_VALUE_MIDDLE
	  			|| m_dominantBaseline == wxCSS_VALUE_CENTRAL)
			chunk.matrix = chunk.matrix.Translate(0,
					(m_ty/m_scale - chunkBBox.GetY() - chunkBBox.GetHeight()/2));
		else if (m_dominantBaseline == wxCSS_VALUE_TEXT_AFTER_EDGE)
			chunk.matrix = chunk.matrix.Translate(0,
					(m_ty - chunkBBox.GetY())/m_scale);
		else if (m_dominantBaseline == wxCSS_VALUE_TEXT_BEFORE_EDGE)
			chunk.matrix = chunk.matrix.Translate(0,
					(m_ty - chunkBBox.GetY() - chunkBBox.GetHeight())/m_scale);
	}
	m_dominantBaseline = wxCSS_VALUE_AUTO;
  }
}
