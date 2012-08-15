/////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasAgg.h
// Purpose:     Ag render
// Author:      Alex Thuering
// Created:     2005/05/04
// RCS-ID:      $Id: SVGCanvasAgg.h,v 1.8 2011/06/27 21:14:14 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_CANVAS_AGG_H
#define WX_SVG_CANVAS_AGG_H

#include "SVGCanvas.h"
class wxSVGCanvasPathAgg;

#include <agg_pixfmt_rgb.h>
#include <agg_rendering_buffer.h>
#include <agg_renderer_scanline.h>
#include <agg_rasterizer_scanline_aa.h>

typedef agg::rendering_buffer RenderingBuffer;
typedef agg::pixfmt_rgb24 PixFmt;
typedef agg::renderer_base<PixFmt> RendererBase;
typedef agg::renderer_scanline_aa_solid<RendererBase> RendererSolid;

class wxSVGCanvasAgg: public wxSVGCanvas
{
  public:
	wxSVGCanvasAgg();
	~wxSVGCanvasAgg();
	
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
	RenderingBuffer* m_rbuf;
	PixFmt* m_pixf;
	RendererBase* m_rendererBase;
	RendererSolid* m_rendererSolid;
	void DrawCanvasPath(wxSVGCanvasPathAgg& canvasPath, wxSVGMatrix& matrix,
      const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem);
    void DrawCanvasImage(wxSVGCanvasImage& canvasImage, wxSVGMatrix& matrix,
      const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem);
    
    agg::rgba8 m_colorProfile[256];
    int m_r, m_g, m_b, m_a;
    double m_offset;
    void SetStopValue(unsigned int index, float offset, float opacity,
      const wxRGBColor& rgbColor);
	void AllocateGradientStops(unsigned int stop_count);
    void PaintRasterizer(agg::rasterizer_scanline_aa<>& ras,
      const wxSVGPaint& paint, float opacity, wxSVGMatrix& matrix,
      const wxSVGSVGElement& svgElem, wxSVGCanvasPath& path);
};

#endif // WX_SVG_CANVAS_AGG_H
