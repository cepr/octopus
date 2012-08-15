//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasTextAgg.h
// Purpose:     Agg canvas text
// Author:      Alex Thuering
// Created:     2005/05/20
// RCS-ID:      $Id: SVGCanvasTextAgg.h,v 1.8 2008/01/15 12:59:31 etisserant Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_CANVAS_TEXT_AGG_H
#define WX_SVG_CANVAS_TEXT_AGG_H

#include "SVGCanvasItem.h"
#include "SVGCanvasPathAgg.h"

#ifdef __WXMSW__
#include <agg_font_win32_tt.h>
#else
#include <agg_font_freetype.h>
#include <platform/agg_platform_support.h>
#endif

#include <agg_path_storage.h>
#include <agg_conv_transform.h>
#include <agg_conv_curve.h>
#include <agg_conv_contour.h>

using namespace agg;

#ifdef __WXMSW__
typedef agg::font_engine_win32_tt_int32 font_engine_type;
#else
typedef agg::font_engine_freetype_int32 font_engine_type;
#endif

typedef agg::font_cache_manager<font_engine_type> font_manager_type; 

class wxSVGCanvasTextAgg: public wxSVGCanvasText
{
  public:
	wxSVGCanvasTextAgg(wxSVGCanvas* canvas);
	~wxSVGCanvasTextAgg();
	
  public:
	#ifdef __WXMSW__
	HDC m_dc;
	#endif
	font_engine_type* m_feng;
	font_manager_type* m_fman;
	double m_scale; // for text with font size <40
	virtual void InitText(const wxString& text, const wxCSSStyleDeclaration& style);
	virtual void EndTextAnchor();
};

#endif
