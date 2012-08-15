//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasPathAgg.h
// Purpose:     Agg canvas path
// Author:      Alex Thuering
// Created:     2005/05/20
// RCS-ID:      $Id: SVGCanvasPathAgg.h,v 1.5 2007/10/30 21:59:22 etisserant Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_CANVAS_PATH_AGG_H
#define WX_SVG_CANVAS_PATH_AGG_H

#include "SVGCanvas.h"

#include <agg_basics.h>
#include <agg_path_storage.h>
#include <agg_conv_transform.h>
#include <agg_conv_stroke.h>
#include <agg_conv_contour.h>
#include <agg_conv_curve.h>
#include <agg_color_rgba.h>
#include <agg_array.h>
#include <agg_bounding_rect.h>

using namespace agg;

class wxSVGCanvasPathAgg: public wxSVGCanvasPath
{
  public:	
	path_storage   m_storage;
	trans_affine   m_transform;
	
	typedef conv_curve<path_storage>                curved;
	typedef conv_stroke<curved>                     curved_stroked;
	typedef conv_transform<curved_stroked>          curved_stroked_trans;
	typedef conv_transform<curved>                  curved_trans;
	typedef conv_contour<curved_trans>              curved_trans_contour;
	
	curved               m_curved;
	curved_stroked       m_curved_stroked;
	curved_stroked_trans m_curved_stroked_trans;
	curved_trans         m_curved_trans;
	curved_trans_contour m_curved_trans_contour;
	
  public:
	wxSVGCanvasPathAgg();
	wxSVGCanvasPathAgg(const wxSVGCanvasPathAgg& path);
    
	void End() {}
    void SetStrokeStyle(const wxCSSStyleDeclaration& style);
	
	unsigned operator [](unsigned) const { return 0; }
    wxSVGRect GetBBox(const wxSVGMatrix& matrix = *(wxSVGMatrix*)NULL);
    wxSVGRect GetResultBBox(const wxCSSStyleDeclaration& style,
      const wxSVGMatrix& matrix = *(wxSVGMatrix*)NULL);
	
	void MoveToImpl(double x, double y);
	void LineToImpl(double x, double y);
	void CurveToCubicImpl(double x1, double y1, double x2, double y2, double x, double y);
	bool ClosePathImpl();
};

#endif // WX_SVG_CANVAS_PATH_AGG_H
