//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasLibart.cpp
// Purpose:     Libart render
// Author:      Alex Thuering
// Created:     2005/05/06
// RCS-ID:      $Id: SVGCanvasLibart.cpp,v 1.22 2011/06/27 21:14:14 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////


#include <libart_lgpl/libart.h>
#include <libart_lgpl/art_render_gradient.h>
#include <libart_lgpl/art_render_svp.h>
#ifndef __WXMSW__
#include <libart_lgpl/art_svp_intersect.h>
#endif

#include "SVGCanvasLibart.h"
#include "SVGCanvasPathLibart.h"
#include "../freetype/SVGCanvasTextFreetype.h"
#include <wx/log.h>

void wxSVGCanvasLibart::Init(int width, int height, bool alpha) {
  m_image.Create(width, height);
}

wxImage wxSVGCanvasLibart::GetImage() {
  return m_image;
}

void wxSVGCanvasLibart::Clear(wxRGBColor color) {
  if (!m_image.Ok())
    return;
  art_rgb_fill_run(m_image.GetData(), color.Red(), color.Green(), color.Blue(),
    m_image.GetWidth()*m_image.GetHeight());
}

wxSVGCanvasPath* wxSVGCanvasLibart::CreateCanvasPath() {
  return new wxSVGCanvasPathLibart();
}

wxSVGCanvasItem* wxSVGCanvasLibart::CreateItem(wxSVGTextElement* element, const wxCSSStyleDeclaration* style) {
  wxSVGCanvasText* canvasText = new wxSVGCanvasTextFreetype(this);
  if (style == NULL)
	style = &element->GetStyle();
  canvasText->Init(*element, *style);
  return canvasText;
}

void wxSVGCanvasLibart::DrawItem(wxSVGCanvasItem& item, wxSVGMatrix& matrix,
  const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem)
{
  switch (item.GetType())
  {
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_PATH:
	  DrawCanvasPath((wxSVGCanvasPathLibart&) item, matrix, style, svgElem);
	  break;
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_TEXT:
      DrawCanvasText((wxSVGCanvasText&) item, matrix, style, svgElem);
	  break;
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_IMAGE:
	  DrawCanvasImage((wxSVGCanvasImage&) item, matrix, style, svgElem);
	  break;
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_VIDEO:
#ifdef USE_FFMPEG
	  DrawCanvasImage((wxSVGCanvasVideo&) item, matrix, style, svgElem);
#endif
	  break;
  }
}

void wxSVGCanvasLibart::DrawCanvasPath(wxSVGCanvasPathLibart& canvasPath,
 wxSVGMatrix& matrix, const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem)
{
  if (!m_image.Ok() || !canvasPath.GetCount())
    return;
  double affine[6];
  affine[0] = matrix.GetA();
  affine[1] = matrix.GetB();
  affine[2] = matrix.GetC();
  affine[3] = matrix.GetD();
  affine[4] = matrix.GetE();
  affine[5] = matrix.GetF();
  ArtBpath* bpath = art_bpath_affine_transform(canvasPath.GetBPath(), affine);
  ArtVpath* vec = art_bez_path_to_vec(bpath, 0.25);
  art_free(bpath);
  
  // Filling
  if (canvasPath.GetFill() && style.GetFill().Ok())
  {
    ArtVpath* fillVec = vec;
    if (canvasPath.ClosePath()) // path must be closed
    {
      bpath = art_bpath_affine_transform(canvasPath.GetBPath(), affine);
      fillVec = art_bez_path_to_vec(bpath, 0.25);
      art_free(bpath);
    }
    
    ArtSVP *temp = art_svp_from_vpath(fillVec);
    if (fillVec != vec)
      art_free(fillVec);

#ifndef __WXMSW__	
    ArtSvpWriter *swr;
    if (style.GetFillRule() == wxCSS_VALUE_EVENODD)
      swr = art_svp_writer_rewind_new(ART_WIND_RULE_ODDEVEN);
    else
      swr = art_svp_writer_rewind_new(ART_WIND_RULE_NONZERO);
    art_svp_intersector(temp, swr);
    ArtSVP* fillSVP = art_svp_writer_rewind_reap(swr);
    art_svp_free(temp);
#else
    ArtSVP* fillSVP = temp;
#endif

    PaintSVP(fillSVP, style.GetFill(),
      style.GetOpacity()*style.GetFillOpacity(), matrix, svgElem, canvasPath);
	art_svp_free(fillSVP);
  }
	
  // Stroking
  if (style.GetStroke().Ok() && style.GetStrokeWidth()>0)
  {
    double ratio = art_affine_expansion(affine);
	ArtSVP* strokeSVP = canvasPath.CreateStrokeSVP(style, vec, ratio);
	PaintSVP(strokeSVP, style.GetStroke(),
      style.GetOpacity()*style.GetStrokeOpacity(), matrix, svgElem, canvasPath);
	art_svp_free(strokeSVP);
  }
  art_free(vec);
}

void wxSVGCanvasLibart::AllocateGradientStops(unsigned int stop_count)
{
  // Allocate enough stops
  m_stops = new ArtGradientStop[stop_count];
}

void wxSVGCanvasLibart::PaintSVP(ArtSVP* fillSVP, const wxSVGPaint& paint,
  float opacity, wxSVGMatrix& matrix, const wxSVGSVGElement& svgElem,
  wxSVGCanvasPath& path)
{
    if (paint.GetPaintType() >= wxSVG_PAINTTYPE_URI_NONE &&
        paint.GetPaintType() <= wxSVG_PAINTTYPE_URI)
    {
    	wxSVGGradientElement* gradElem = GetGradientElement(svgElem, paint.GetUri());
        m_nstops = GetGradientStops(svgElem, gradElem, opacity);
        if (m_nstops)
        {
            switch (gradElem->GetDtd())
            {
                case wxSVG_LINEARGRADIENT_ELEMENT:
                {
                    ArtGradientLinear gradient;
                    gradient.n_stops = m_nstops;
                    gradient.stops = m_stops;
                    double dx, dy;
                    wxSVGPoint p1,p2;
                    GetLinearGradientVector(p1, p2, (wxSVGLinearGradientElement&) *gradElem, path);
                    p1 = p1.MatrixTransform(matrix);
                    p2 = p2.MatrixTransform(matrix);
                    /* solve a, b, c so ax1 + by1 + c = 0 and ax2 + by2 + c = 1, maximum
                       gradient is in x1,y1 to x2,y2 dir */
                    dx = p2.GetX() - p1.GetX();
                    dy = p2.GetY() - p1.GetY();
  
                
                    /* workaround for an evil devide by 0 bug - not sure if this is sufficient */
                    float length = (dx * dx + dy * dy);
                    if (length > 0.0000001)
                    {
                        gradient.a = dx / length;
                        gradient.b = dy / length;
                        gradient.c = -(p1.GetX() * gradient.a + p1.GetY() * gradient.b);
                    
                        gradient.spread = ART_GRADIENT_PAD;
                        DrawSVPLinearGradient(fillSVP, gradient);
                    }
                }
                break;
                case wxSVG_RADIALGRADIENT_ELEMENT:
                {
                    ArtGradientRadial gradient;
                    gradient.n_stops = m_nstops;
                    gradient.stops = m_stops;
                    
                    // Get Gradient transformation
                    wxSVGPoint focus;
                    wxSVGMatrix rgMatrix = matrix;
                    GetRadialGradientTransform(focus, rgMatrix, (wxSVGRadialGradientElement&) *gradElem, path, true);
                    rgMatrix = rgMatrix.Inverse();
                    
                    gradient.affine[0] = rgMatrix.GetA();
                    gradient.affine[1] = rgMatrix.GetB();
                    gradient.affine[2] = rgMatrix.GetC();
                    gradient.affine[3] = rgMatrix.GetD();
                    gradient.affine[4] = rgMatrix.GetE();
                    gradient.affine[5] = rgMatrix.GetF();
  
                    gradient.fx = focus.GetX();
                    gradient.fy = focus.GetY();
                    
                    // Draw
                    DrawSVPRadialGradient(fillSVP, gradient);
                }
                break;
                default:
                break;
            }
            delete[] m_stops;
            return;
        }
        if (paint.GetPaintType() == wxSVG_PAINTTYPE_URI_NONE)
            return;
    }
    
    DrawSVP(fillSVP, paint.GetRGBColor(), opacity);
}

void wxSVGCanvasLibart::SetStopValue(unsigned int i, float offset,
  float opacity, const wxRGBColor& rgbColor)
{
    unsigned int r, g, b, a;
    m_stops[i].offset = offset;
    /* convert from separated to premultiplied alpha */
    a = (unsigned int)(opacity * 255);
    r = (rgbColor.Red()) * a + 0x80;
    r = (r + (r >> 8)) >> 8;
    g = (rgbColor.Green()) * a + 0x80;
    g = (g + (g >> 8)) >> 8;
    b = (rgbColor.Blue()) * a + 0x80;
    b = (b + (b >> 8)) >> 8;
    m_stops[i].color[0] = ART_PIX_MAX_FROM_8(r);
    m_stops[i].color[1] = ART_PIX_MAX_FROM_8(g);
    m_stops[i].color[2] = ART_PIX_MAX_FROM_8(b);
    m_stops[i].color[3] = ART_PIX_MAX_FROM_8(a);
}

void wxSVGCanvasLibart::DrawSVP(ArtSVP* svp, const wxRGBColor& color, double opacity)
{
  art_u32 c = (color.Red() << 24) | (color.Green() <<16) | (color.Blue()<<8) | ((int)(opacity*255)) ;
  art_rgb_svp_alpha(svp, 0, 0, m_image.GetWidth(), m_image.GetHeight(), 
	c, m_image.GetData(), m_image.GetWidth()*3, NULL);
}

void wxSVGCanvasLibart::DrawSVPLinearGradient(ArtSVP* svp, ArtGradientLinear& gradient)
{
  ArtRender *render = art_render_new (0, 0, m_image.GetWidth(), m_image.GetHeight(), 
	   m_image.GetData(), m_image.GetWidth()*3, 3, 8, ART_ALPHA_NONE, NULL);
  art_render_svp(render, svp);
  art_render_gradient_linear (render, &gradient, ART_FILTER_NEAREST);
  art_render_invoke (render);	
}

void wxSVGCanvasLibart::DrawSVPRadialGradient(ArtSVP* svp, ArtGradientRadial& gradient)
{
  ArtRender *render = art_render_new (0, 0, m_image.GetWidth(), m_image.GetHeight(), 
	   m_image.GetData(), m_image.GetWidth()*3, 3, 8, ART_ALPHA_NONE, NULL);
  art_render_svp(render, svp);
  art_render_gradient_radial (render, &gradient, ART_FILTER_NEAREST);
  art_render_invoke (render);	
}

void wxSVGCanvasLibart::DrawCanvasImage(wxSVGCanvasImage& canvasImage,
  wxSVGMatrix& matrix, const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem)
{
  if (!canvasImage.m_image.Ok() || !m_image.Ok())
	  return;
  double opacity = style.GetOpacity();
  
  int width = canvasImage.m_image.GetWidth();
  int height = canvasImage.m_image.GetHeight();
  unsigned char* srcPix = canvasImage.m_image.GetData();
  int srcStride = canvasImage.m_image.GetWidth()*3;
  unsigned char* srcAlpha = canvasImage.m_image.GetAlpha();
  
  int dstWidth = m_image.GetWidth();
  int dstHeight = m_image.GetHeight();
  unsigned char* dstPix = m_image.GetData();
  int dstStride = dstWidth*3;
  //unsigned char* dstAlpha = m_image.GetAlpha();
  
  // trnslate
  wxSVGMatrix rawMatrix = matrix.Translate(canvasImage.m_x, canvasImage.m_y);
  wxSVGMatrix rawInvMatrix = rawMatrix.Inverse();
  // scale
  wxSVGMatrix invMatrix(canvasImage.m_width, 0, 0, canvasImage.m_height, 0, 0);
  invMatrix = rawMatrix.Multiply(invMatrix).Inverse();
  
  // calc boundariy box (x0,y0 - x1,y1)
  wxSVGPoint p[4];
  p[0] = wxSVGPoint(0,0).MatrixTransform(rawMatrix);
  p[1] = wxSVGPoint(canvasImage.m_width, 0).MatrixTransform(rawMatrix);
  p[2] = wxSVGPoint(canvasImage.m_width, canvasImage.m_height).MatrixTransform(rawMatrix);
  p[3] = wxSVGPoint(0, canvasImage.m_height).MatrixTransform(rawMatrix);
  int x0 = (int) p[0].GetX();
  int y0 = (int) p[0].GetY();
  int x1 = (int) p[0].GetX();
  int y1 = (int) p[0].GetY();
  for (int k=1; k<4; k++)
  {
	if (x0 > p[k].GetX())
	  x0 = (int) p[k].GetX();
	if (y0 > p[k].GetY())
	  y0 = (int) p[k].GetY();
	if (x1 < p[k].GetX())
	  x1 = (int) p[k].GetX();
	if (y1 < p[k].GetY())
	  y1 = (int) p[k].GetY();
  }
  x1++; y1++;
  x0 = x0<0 ? 0 : x0;
  y0 = y0<0 ? 0 : y0;
  x1 = x1>dstWidth ? dstWidth : x1;
  y1 = y1>dstHeight ? dstHeight : y1;
  
  // apply the transformation
  for (int i=x0; i<x1; i++)
  {
	for (int j=y0; j<y1; j++)
	{
	  double fSrcX = (invMatrix.GetA()*i + invMatrix.GetC()*j + invMatrix.GetE())*width;
	  double fSrcY = (invMatrix.GetB()*i + invMatrix.GetD()*j + invMatrix.GetF())*height;
	  int srcX = (int) floor(fSrcX);
	  int srcY = (int) floor(fSrcY);
	  double rawX = rawInvMatrix.GetA()*i + rawInvMatrix.GetC()*j + rawInvMatrix.GetE();
	  double rawY = rawInvMatrix.GetB()*i + rawInvMatrix.GetD()*j + rawInvMatrix.GetF();
	  if (rawX >= 0 && rawY >= 0 && rawX < canvasImage.m_width && rawY < canvasImage.m_height &&
		  srcX >= 0 && srcY >= 0 && srcX < width && srcY < height)
	  {
		bool xrunnoff = srcX < 0 || srcX + 1 >= width;
		bool yrunnoff = srcY < 0 || srcY + 1 >= height;
		
		double pixsum[4];
		for (int k = 0; k < 4; k++)
		  pixsum[k] = 0;
		
		int srcIndex = srcY*srcStride + srcX*3;
		for (int jj = 0; jj < 2; jj++)
		{
		  for (int ii = 0; ii < 2; ii++)
		  {
			  if (srcX + ii >= 0 && srcY + jj >= 0 &&
				  srcX + ii < width && srcY + jj < height)
			  {
				double f =
				  (xrunnoff ? 1 : fabs(fSrcX - (double)(srcX + (1 - ii))))*
				  (yrunnoff ? 1 : fabs(fSrcY - (double)(srcY + (1 - jj))));
				for (int k = 0; k < 3; k++)
				{
				  pixsum[k] += (double)	srcPix[srcIndex]*f;
				  srcIndex++;
				}
				if (srcAlpha)
				  pixsum[3] += (double) srcAlpha[(srcY+jj)*width+srcX+ii]*f;
			  }
		  }
		  srcIndex += srcStride - 6;
		}
		int a = i*3 + j*dstStride;
		if (opacity == 1 && (!srcAlpha || pixsum[3] == 255))
		{
		  for (int k = 0; k<3; k++)
			dstPix[a+k] = (unsigned char) pixsum[k];
		}
		else
		{
		  unsigned char alpha = (unsigned char) (srcAlpha ? opacity*pixsum[3] : opacity*255);
		  for (int k = 0; k<3; k++)
		  {
			unsigned char n = (unsigned char) pixsum[k];
			unsigned char& v = dstPix[a+k]; 
			dstPix[a+k] = v + (((n - v) * alpha + 0x80) >> 8);
		  }
		}
		//if (!dstAlpha)
			//dstAlpha[i + j*dstWidth] = 255;
	  }
	}
  }
}
