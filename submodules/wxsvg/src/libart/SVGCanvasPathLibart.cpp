//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasPathLibart.cpp
// Purpose:     Libart canvas path
// Author:      Alex Thuering
// Created:     2005/05/06
// RCS-ID:      $Id: SVGCanvasPathLibart.cpp,v 1.4 2006/02/28 16:52:29 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#include "SVGCanvasPathLibart.h"
#include <wx/log.h>

#include <libart_lgpl/libart.h>

wxSVGCanvasPathLibart::wxSVGCanvasPathLibart()
{
  m_count = 0;
  m_size = 16;
  m_moveto_idx = -1;
  m_bpath = art_new(ArtBpath, m_size);
}

wxSVGCanvasPathLibart::~wxSVGCanvasPathLibart()
{
  art_free(m_bpath);
}

ArtBpath& wxSVGCanvasPathLibart::AddBPath()
{
  if (m_count == m_size)
  {
	m_size *= 2;
	ArtBpath* bpath = art_new(ArtBpath, m_size);
	memcpy(bpath, m_bpath, m_count*sizeof(ArtBpath)); 
	art_free(m_bpath);
    m_bpath = bpath;
  }
  m_count++;
  return m_bpath[m_count-1];
}

void wxSVGCanvasPathLibart::End()
{
  if (!m_count)
    return;
  ArtBpath& bpath = AddBPath();
  bpath.code = ART_END;
}

ArtSVP* wxSVGCanvasPathLibart::CreateStrokeSVP(
  const wxCSSStyleDeclaration& style, ArtVpath* vec, double ratio)
{
  /* TODO:
  unsigned int dashLength;
  if (style.HasStrokeDasharray() && (dashLength = style.GetStrokeDasharray().Count()))
  {
    // there are dashes to be rendered
    ArtVpathDash dash;
    dash.offset = int(style.GetStrokeDashoffset())*ratio;
    dash.n_dash = dashLength;
    double *dashes = new double[dashLength];
    for(unsigned int i = 0; i < dashLength; i++)
      dashes[i] = style.GetStrokeDasharray().Item(i).GetValue()*ratio;
    dash.dash = dashes;
    
    // get the dashed VPath and use that for the stroke render operation
    ArtVpath *vec2 = art_vpath_dash(vec, &dash);
    art_free(vec);
    vec = vec2;
    delete[] dashes;
  }*/
  
  ArtPathStrokeJoinType joinType = ART_PATH_STROKE_JOIN_MITER;
  if (style.GetStrokeLinejoin() == wxCSS_VALUE_MITER)
    joinType = ART_PATH_STROKE_JOIN_MITER;
  else if (style.GetStrokeLinejoin() == wxCSS_VALUE_ROUND)
    joinType = ART_PATH_STROKE_JOIN_ROUND;
  else if (style.GetStrokeLinejoin() == wxCSS_VALUE_BEVEL)
    joinType = ART_PATH_STROKE_JOIN_BEVEL;
  
  ArtPathStrokeCapType capType = ART_PATH_STROKE_CAP_BUTT;
  if (style.GetStrokeLinecap() == wxCSS_VALUE_BUTT)
    capType = ART_PATH_STROKE_CAP_BUTT;
  else if (style.GetStrokeLinecap() == wxCSS_VALUE_ROUND)
    capType = ART_PATH_STROKE_CAP_ROUND;
  else if (style.GetStrokeLinecap() == wxCSS_VALUE_SQUARE)
    capType = ART_PATH_STROKE_CAP_SQUARE;

  double strokeWidth = style.GetStrokeWidth()*ratio;
  if (strokeWidth<0.25)
    strokeWidth = 0.25;
  
  return art_svp_vpath_stroke(vec, joinType,
    capType, strokeWidth, style.GetStrokeMiterlimit(), 0.25);
}

wxSVGRect wxSVGCanvasPathLibart::GetBBox(const wxSVGMatrix& matrix)
{
  if (!m_count)
    return wxSVGRect();
  ArtDRect rect;
  ArtBpath* bpath = m_bpath;
  if (&matrix)
  {
    double affine[6];
    affine[0] = matrix.GetA();
    affine[1] = matrix.GetB();
    affine[2] = matrix.GetC();
    affine[3] = matrix.GetD();
    affine[4] = matrix.GetE();
    affine[5] = matrix.GetF();
    bpath = art_bpath_affine_transform(m_bpath, affine);
  }
  ArtVpath* vec = art_bez_path_to_vec(bpath, 0.25);
  art_vpath_bbox_drect(vec, &rect);
  art_free(vec);
  if (&matrix)
    art_free(bpath);
  return wxSVGRect(rect.x0, rect.y0, rect.x1-rect.x0, rect.y1-rect.y0);
}

wxSVGRect wxSVGCanvasPathLibart::GetResultBBox(const wxCSSStyleDeclaration& style,
  const wxSVGMatrix& matrix)
{
  if (!m_count)
    return wxSVGRect();
  ArtDRect rect;
  ArtBpath* bpath = m_bpath;
  double ratio = 1;
  if (&matrix)
  {
    double affine[6];
    affine[0] = matrix.GetA();
    affine[1] = matrix.GetB();
    affine[2] = matrix.GetC();
    affine[3] = matrix.GetD();
    affine[4] = matrix.GetE();
    affine[5] = matrix.GetF();
    bpath = art_bpath_affine_transform(m_bpath, affine);
    ratio = art_affine_expansion(affine);
  }
  ArtVpath* vec = art_bez_path_to_vec(bpath, 0.25);
  ArtSVP* strokeSVP = CreateStrokeSVP(style, vec, ratio);
  art_drect_svp(&rect, strokeSVP);
  art_svp_free(strokeSVP);
  art_free(vec);
  if (&matrix)
    art_free(bpath);
  return wxSVGRect(rect.x0, rect.y0, rect.x1-rect.x0, rect.y1-rect.y0);
}

void wxSVGCanvasPathLibart::MoveToImpl(double x, double y)
{
  ArtBpath& bpath = AddBPath();
  bpath.code = ART_MOVETO_OPEN;
  bpath.x3 = x;
  bpath.y3 = y;
  m_moveto_idx = m_count - 1;
}

void wxSVGCanvasPathLibart::LineToImpl(double x, double y)
{
  ArtBpath& bpath = AddBPath();
  bpath.code = ART_LINETO;
  bpath.x3 = x;
  bpath.y3 = y;
}

void wxSVGCanvasPathLibart::CurveToCubicImpl(double x1, double y1,
 double x2, double y2, double x, double y)
{
  ArtBpath& bpath = AddBPath();
  bpath.code = ART_CURVETO;
  bpath.x1 = x1;
  bpath.y1 = y1;
  bpath.x2 = x2;
  bpath.y2 = y2;
  bpath.x3 = x;
  bpath.y3 = y;
}

bool wxSVGCanvasPathLibart::ClosePathImpl()
{
  if (!m_count || m_moveto_idx == -1)
	return false;
  
  bool end = false;
  if (m_bpath[m_count-1].code == ART_END)
  {
     m_count--;
     end = true;
     if (!m_count)
       return false;
  }
  
  if (m_bpath[m_moveto_idx].x3 != m_bpath[m_count-1].x3 ||
	  m_bpath[m_moveto_idx].y3 != m_bpath[m_count-1].y3)
	LineToImpl(m_bpath[m_moveto_idx].x3, m_bpath[m_moveto_idx].y3);
  m_bpath[m_moveto_idx].code = ART_MOVETO;
  
  if (end)
    End();
  
  return true;
}
