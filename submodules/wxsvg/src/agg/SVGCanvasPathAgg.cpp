//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasPathAgg.cpp
// Purpose:     Agg canvas path
// Author:      Alex Thuering
// Created:     2005/05/20
// RCS-ID:      $Id: SVGCanvasPathAgg.cpp,v 1.5 2006/10/13 16:14:01 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#include "SVGCanvasPathAgg.h"
#include <wx/log.h>

wxSVGCanvasPathAgg::wxSVGCanvasPathAgg():
  m_curved(m_storage),
  m_curved_stroked(m_curved),
  m_curved_stroked_trans(m_curved_stroked, m_transform),
  m_curved_trans(m_curved, m_transform),
  m_curved_trans_contour(m_curved_trans)
{
  m_curved_trans_contour.auto_detect_orientation(false);
  m_curved_trans_contour.width(0);
  m_storage.start_new_path();
}

wxSVGCanvasPathAgg::wxSVGCanvasPathAgg(const wxSVGCanvasPathAgg& path):
  m_curved(m_storage),
  m_curved_stroked(m_curved),
  m_curved_stroked_trans(m_curved_stroked, m_transform),
  m_curved_trans(m_curved, m_transform),
  m_curved_trans_contour(m_curved_trans)
{
  m_curved_trans_contour.auto_detect_orientation(false);
  m_curved_trans_contour.width(0);
  m_storage.start_new_path();
  //m_storage.add_path(path.m_storage);
}

void wxSVGCanvasPathAgg::SetStrokeStyle(const wxCSSStyleDeclaration& style)
{
  m_curved_stroked.width(style.GetStrokeWidth());
  
  if (style.GetStrokeLinejoin() == wxCSS_VALUE_MITER)
    m_curved_stroked.line_join(miter_join);
  else if (style.GetStrokeLinejoin() == wxCSS_VALUE_ROUND)
    m_curved_stroked.line_join(round_join);
  else if (style.GetStrokeLinejoin() == wxCSS_VALUE_BEVEL)
    m_curved_stroked.line_join(bevel_join);
  
  if (style.GetStrokeLinecap() == wxCSS_VALUE_BUTT)
    m_curved_stroked.line_cap(butt_cap);
  else if (style.GetStrokeLinecap() == wxCSS_VALUE_ROUND)
    m_curved_stroked.line_cap(round_cap);
  else if (style.GetStrokeLinecap() == wxCSS_VALUE_SQUARE)
    m_curved_stroked.line_cap(square_cap);
  
  m_curved_stroked.miter_limit(style.GetStrokeMiterlimit());
}

wxSVGRect wxSVGCanvasPathAgg::GetBBox(const wxSVGMatrix& matrix)
{
  if (!m_storage.total_vertices())
    return wxSVGRect();
  double x1, y1, x2, y2;
  if (&matrix)
  {
    m_transform = trans_affine(matrix.GetA(), matrix.GetB(),
      matrix.GetC(), matrix.GetD(), matrix.GetE(), matrix.GetF());
    bounding_rect(m_curved_trans, *this, 0, 1, &x1, &y1, &x2, &y2);
  }
  else
    bounding_rect(m_curved, *this, 0, 1, &x1, &y1, &x2, &y2);
  return wxSVGRect(x1, y1, x2-x1, y2-y1);
}

wxSVGRect wxSVGCanvasPathAgg::GetResultBBox(const wxCSSStyleDeclaration& style,
  const wxSVGMatrix& matrix)
{
  SetStrokeStyle(style);
  double x1, y1, x2, y2;
  if (&matrix)
  {
    m_transform = trans_affine(matrix.GetA(), matrix.GetB(),
      matrix.GetC(), matrix.GetD(), matrix.GetE(), matrix.GetF());
    bounding_rect(m_curved_stroked_trans, *this, 0, 1, &x1, &y1, &x2, &y2);
  }
  else
    bounding_rect(m_curved_stroked, *this, 0, 1, &x1, &y1, &x2, &y2);
  return wxSVGRect(x1, y1, x2-x1, y2-y1);
}

void wxSVGCanvasPathAgg::MoveToImpl(double x, double y)
{
  m_storage.move_to(x, y);
}

void wxSVGCanvasPathAgg::LineToImpl(double x, double y)
{
  m_storage.line_to(x, y);
}

void wxSVGCanvasPathAgg::CurveToCubicImpl(double x1, double y1,
 double x2, double y2, double x, double y)
{
  m_storage.curve4(x1, y1, x2, y2, x, y);
}

bool wxSVGCanvasPathAgg::ClosePathImpl()
{
  m_storage.end_poly(path_flags_close);
  return true;
}
