/////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasAgg.cpp
// Purpose:     Agg render
// Author:      Alex Thuering
// Created:     2005/05/04
// RCS-ID:      $Id: SVGCanvasAgg.cpp,v 1.17 2011/06/27 21:14:14 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "SVGCanvasAgg.h"
#include "SVGCanvasPathAgg.h"
#ifdef __WXMSW__
#include "SVGCanvasTextAgg.h"
#else
#include "../freetype/SVGCanvasTextFreetype.h"
#endif

#include <wx/log.h>
#include <agg_scanline_p.h>
#include <agg_scanline_u.h>
#include <agg_span_converter.h>
#include <agg_span_gradient.h>
#include <agg_span_interpolator_linear.h>
#include <agg_span_interpolator_trans.h>
#include <agg_span_image_filter_rgb.h>
#include <agg_span_image_filter_rgba.h>
#include <agg_span_allocator.h>
#include <agg_image_accessors.h>
#include <agg_pixfmt_rgba.h>
#include <agg_blur.h>

	
wxSVGCanvasAgg::wxSVGCanvasAgg(): m_rbuf(NULL), m_pixf(NULL), m_rendererBase(NULL), m_rendererSolid(NULL) {
}

wxSVGCanvasAgg::~wxSVGCanvasAgg() {
  delete m_rbuf;
  delete m_pixf;
  delete m_rendererBase;
  delete m_rendererSolid;
}

void wxSVGCanvasAgg::Init(int width, int height, bool alpha) {
  m_image.Create(width, height);
  m_rbuf = new RenderingBuffer(m_image.GetData(), 
	 m_image.GetWidth(), m_image.GetHeight(), m_image.GetWidth()*3);
  m_pixf = new PixFmt(*m_rbuf);
  m_rendererBase = new RendererBase(*m_pixf);
  m_rendererSolid = new RendererSolid(*m_rendererBase);
}

wxImage wxSVGCanvasAgg::GetImage() {
  return m_image;
}

void wxSVGCanvasAgg::Clear(wxRGBColor color) {
  if (!m_rendererBase)
    return;
  m_rendererBase->clear(agg::rgba(
    color.Red()/255, color.Green()/255, color.Blue()/255));
}

wxSVGCanvasPath* wxSVGCanvasAgg::CreateCanvasPath() {
  return new wxSVGCanvasPathAgg();
}

wxSVGCanvasItem* wxSVGCanvasAgg::CreateItem(wxSVGTextElement* element, const wxCSSStyleDeclaration* style) {
#ifdef __WXMSW__
  wxSVGCanvasText* canvasText = new wxSVGCanvasTextAgg(this);
#else
  wxSVGCanvasText* canvasText = new wxSVGCanvasTextFreetype(this);
#endif
  if (style == NULL)
	style = (wxCSSStyleDeclaration*) &element->GetStyle();
  canvasText->Init(*element, *style);
  return canvasText;
}

void wxSVGCanvasAgg::DrawItem(wxSVGCanvasItem& item, wxSVGMatrix& matrix,
  const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem) {
  switch (item.GetType())   {
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_PATH:
	  DrawCanvasPath((wxSVGCanvasPathAgg&) item, matrix, style, svgElem);
	  break;
    case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_TEXT:
      DrawCanvasText((wxSVGCanvasText&) item, matrix, style, svgElem);
	  break;
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_IMAGE:
	  DrawCanvasImage((wxSVGCanvasImage&) item, matrix, style, svgElem);
	  break;
	#ifdef USE_FFMPEG
	case wxSVGCanvasItem::wxSVG_CANVAS_ITEM_VIDEO:
	  DrawCanvasImage((wxSVGCanvasVideo&) item, matrix, style, svgElem);
	  break;
	#endif
  }
}

void wxSVGCanvasAgg::DrawCanvasPath(wxSVGCanvasPathAgg& canvasPath,
 wxSVGMatrix& matrix, const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem) {
  if (!m_rendererBase)
    return;
  rasterizer_scanline_aa<> ras;
  
  const rect_i& cb = m_rendererBase->clip_box();
  ras.clip_box(cb.x1, cb.y1, cb.x2+1, cb.y2+1);
	  
  canvasPath.m_transform = trans_affine(matrix.GetA(), matrix.GetB(),
	matrix.GetC(), matrix.GetD(), matrix.GetE(), matrix.GetF());
	  
  if (style.GetFill().Ok()) {
	ras.reset();
	ras.filling_rule(
	  style.GetFillRule() == wxCSS_VALUE_EVENODD ? fill_even_odd : fill_non_zero);
	if (fabs(canvasPath.m_curved_trans_contour.width()) < 0.0001)
	  ras.add_path(canvasPath.m_curved_trans);
	else
	{
	  canvasPath.m_curved_trans_contour.miter_limit(style.GetStrokeMiterlimit());
	  ras.add_path(canvasPath.m_curved_trans_contour);
	}
    
    PaintRasterizer(ras, style.GetFill(),
      style.GetOpacity()*style.GetFillOpacity(), matrix, svgElem, canvasPath);
  }

  if (style.GetStroke().Ok() && style.GetStrokeWidth()>0) {
	canvasPath.SetStrokeStyle(style);
    
	ras.reset();
	ras.filling_rule(fill_non_zero);
	ras.add_path(canvasPath.m_curved_stroked_trans);
    
    PaintRasterizer(ras, style.GetStroke(),
      style.GetOpacity()*style.GetStrokeOpacity(), matrix, svgElem, canvasPath);
  }
  
//  if (style.GetFilter().GetCSSPrimitiveType() == wxCSS_URI && style.GetFilter().GetStringValue().length() > 1) {
//	  wxSVGElement* filterElem = (wxSVGSVGElement*) svgElem.GetElementById(style.GetFilter().GetStringValue().substr(1));
//	  // feGaussianBlur
//	  if (filterElem && filterElem->GetDtd() == wxSVG_FILTER_ELEMENT && filterElem->GetFirstChild() != NULL
//			  && ((wxSVGSVGElement*)filterElem->GetFirstChild())->GetDtd() == wxSVG_FEGAUSSIANBLUR_ELEMENT) {
//		  float radius = ((wxSVGFEGaussianBlurElement*) filterElem->GetFirstChild())->GetStdDeviationX().GetAnimVal()*2;
//		  // Calculate the bounding box and extend it by the blur radius
//		  agg::rect_d bbox;
//		  agg::bounding_rect_single(canvasPath.m_curved_trans, 0, &bbox.x1, &bbox.y1, &bbox.x2, &bbox.y2);
//		  bbox.x1 -= radius;
//		  bbox.y1 -= radius;
//		  bbox.x2 += radius*2;
//		  bbox.y2 += radius*2;
//		  
//		  PixFmt pixf2(*m_rbuf);
//		  if(pixf2.attach(*m_pixf, int(bbox.x1), int(bbox.y1), int(bbox.x2), int(bbox.y2))) {
//			  agg::recursive_blur<agg::rgba8, agg::recursive_blur_calc_rgb<> > recursive_blur;
//			  recursive_blur.blur(pixf2, radius);
//		  }
//	  }
//  }
}


class GradientPolymorphicWrapperBase
{
  public:
    virtual int calculate(int x, int y, int) const = 0;
};

template<class GradientF> 
class GradientPolymorphicWrapper : public GradientPolymorphicWrapperBase
{
  public:
    GradientPolymorphicWrapper() {}

    virtual int calculate(int x, int y, int d) const
    {
        return m_gradient.calculate(x, y, d);
    }
    GradientF m_gradient;
};


struct ColorFunctionProfile
{
  ColorFunctionProfile() {}
  ColorFunctionProfile(const rgba8* colors): m_colors(colors) {}

  static unsigned size() { return 256; }
  const rgba8& operator [] (unsigned v) const
  { 
      return m_colors[v]; 
  }

  const rgba8* m_colors;
};

void wxSVGCanvasAgg::AllocateGradientStops(unsigned int stop_count)
{
  m_r = m_g = m_b = 0;
  m_a = 255;
  m_offset = -1;
}

void wxSVGCanvasAgg::SetStopValue(unsigned int index, float offset,
  float opacity, const wxRGBColor& rgbColor)
{
  int r = rgbColor.Red();
  int g = rgbColor.Green();
  int b = rgbColor.Blue();
  int a = int(floor(int(opacity * 255.0) + 0.5));
  unsigned int start = m_offset == -1 ? 0 : int(m_offset * 255);
  int end = int(offset * 255);
  if (m_offset == -1)
  {
      m_r = r;
      m_g = g;
      m_b = b;
      m_a = a;
  }
  int diffr = r - m_r;
  int diffg = g - m_g;
  int diffb = b - m_b;
  int diffa = a - m_a;
  unsigned int nsteps = end - start;
  for (unsigned int i = 0; i <= nsteps; i++)
  {
      double diff = double(i) / double(nsteps);
      m_colorProfile[start + i].r = int(m_r + diff * diffr);
      m_colorProfile[start + i].g = int(m_g + diff * diffg);
      m_colorProfile[start + i].b = int(m_b + diff * diffb);
      m_colorProfile[start + i].a = int(m_a + diff * diffa);
  }
  m_r = r;
  m_g = g;
  m_b = b;
  m_a = a;
  m_offset = offset;
}

void wxSVGCanvasAgg::PaintRasterizer(rasterizer_scanline_aa<>& ras,
  const wxSVGPaint& paint, float opacity, wxSVGMatrix& matrix,
  const wxSVGSVGElement& svgElem, wxSVGCanvasPath& path)
{
  scanline_p8 sl;
  
  if (paint.GetPaintType() >= wxSVG_PAINTTYPE_URI_NONE &&
      paint.GetPaintType() <= wxSVG_PAINTTYPE_URI)
  {
	wxSVGGradientElement* gradElem = GetGradientElement(svgElem, paint.GetUri());
    int m_nstops = GetGradientStops(svgElem, gradElem, opacity);
    if (m_nstops)
    {
      for (unsigned int i = int(m_offset * 255); i <= 255; i++)
      {
        m_colorProfile[i].r = m_r;
        m_colorProfile[i].g = m_g;
        m_colorProfile[i].b = m_b;
        m_colorProfile[i].a = m_a;
      }
      GradientPolymorphicWrapper<gradient_x>      gr_x;
      GradientPolymorphicWrapper<gradient_circle> gr_circle;

      GradientPolymorphicWrapperBase* gr_ptr = &gr_x;
      
      wxSVGMatrix rgMatrix = matrix;
      double length = 0;
      switch (gradElem->GetDtd())
      {
        case wxSVG_LINEARGRADIENT_ELEMENT:
        {
          wxSVGPoint p1, p2;
          GetLinearGradientVector(p1, p2, (wxSVGLinearGradientElement&) *gradElem, path);
          double dx = p2.GetX() - p1.GetX();
          double dy = p2.GetY() - p1.GetY();
          rgMatrix = rgMatrix.Translate(p1.GetX(), p1.GetY());
          rgMatrix = rgMatrix.Rotate(atan2(dy, dx)*180/M_PI);
          length = sqrt(dx * dx + dy * dy);
          break;
        }
        case wxSVG_RADIALGRADIENT_ELEMENT:
        {
          gr_ptr = &gr_circle;
          wxSVGPoint focus;
          GetRadialGradientTransform(focus, rgMatrix, (wxSVGRadialGradientElement&) *gradElem, path);
          length = gradElem->GetR().GetAnimVal();
          break;
        }
        default:
          break;
      }
      
      
      rgMatrix = rgMatrix.Inverse();
      trans_affine mtx_g1(rgMatrix.GetA(), rgMatrix.GetB(), rgMatrix.GetC(),
          rgMatrix.GetD(), rgMatrix.GetE(), rgMatrix.GetF());
      
      typedef span_interpolator_linear<> InterpolatorType;
      typedef span_gradient<rgba8, 
                            InterpolatorType,
                            GradientPolymorphicWrapperBase,
                            ColorFunctionProfile> GradientSpanGen;
      typedef span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;
      typedef renderer_scanline_aa<RendererBase,GradientSpanAlloc, GradientSpanGen> RendererGradient;
      
      GradientSpanAlloc    spanAlloc;
      ColorFunctionProfile colors(m_colorProfile);
      InterpolatorType     inter(mtx_g1);
      GradientSpanGen      spanGen(inter, *gr_ptr, colors, 0, length);
      RendererGradient     r1(*m_rendererBase, spanAlloc, spanGen);

      agg::render_scanlines(ras, sl, r1);
      return;
    }
    if (paint.GetPaintType() == wxSVG_PAINTTYPE_URI_NONE)
      return;
  }
  
  const wxRGBColor& c = paint.GetRGBColor();
  rgba8 color(c.Red(), c.Green(), c.Blue());
  color.opacity(opacity);
  m_rendererSolid->color(color);
  agg::render_scanlines(ras, sl, *m_rendererSolid);
}

class SpanConvAlpha
{
  public:
	SpanConvAlpha(double alpha)
	{
	  m_alpha = alpha;
	}
	typedef rgba8 color_type;
	typedef int8u alpha_type;

	void prepare() {}
    
	void generate(color_type* colors, int x, int y, unsigned len) const
	{
	  while (len)
	  {
		colors->a = (unsigned char) (m_alpha*colors->a);
		colors++;
		len--;
	  }
	}
  
  protected:
	double m_alpha;
};

typedef span_interpolator_linear<> InterpolatorType;
typedef span_allocator<rgba8> SpanAlloc;

typedef image_accessor_clip<PixFmt> ImageSourceType;
typedef span_image_filter_rgb_bilinear<ImageSourceType, InterpolatorType> SpanGenType;
typedef span_converter<SpanGenType, SpanConvAlpha> SpanConv;

typedef agg::pixfmt_rgba32 PixFmtAlpha;
typedef image_accessor_clip<PixFmtAlpha> ImageSourceTypeA;
typedef span_image_filter_rgba_bilinear<ImageSourceTypeA, InterpolatorType> SpanGenTypeA;
typedef span_converter<SpanGenTypeA, SpanConvAlpha> SpanConvA;

void wxSVGCanvasAgg::DrawCanvasImage(wxSVGCanvasImage& canvasImage, wxSVGMatrix& matrix,
		const wxCSSStyleDeclaration& style, wxSVGSVGElement& svgElem) {
	wxImage img = canvasImage.m_image;
	if (!img.Ok() || img.GetWidth() == 0 || img.GetHeight() == 0)
		return;

	// source_buffer
	rendering_buffer source_buffer;
	unsigned char* buf = NULL;
	if (img.HasAlpha()) {
		buf = new unsigned char[img.GetWidth() * img.GetHeight() * 4];
		unsigned char* src = img.GetData();
		unsigned char* srca = img.GetAlpha();
		unsigned char* dst = buf;
		for (int i = 0; i < img.GetWidth() * img.GetHeight(); i++) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = srca[0];
			dst += 4;
			src += 3;
			srca++;
		}
		source_buffer.attach(buf, img.GetWidth(), img.GetHeight(), img.GetWidth() * 4);
	} else
		source_buffer.attach(img.GetData(), img.GetWidth(), img.GetHeight(), img.GetWidth() * 3);

	//transform
	wxSVGMatrix transMatrix =
			matrix.Translate(canvasImage.m_x, canvasImage.m_y);
	transMatrix = transMatrix.ScaleNonUniform(canvasImage.m_width / img.GetWidth(),
			canvasImage.m_height / img.GetHeight());
	trans_affine transform(transMatrix.GetA(), transMatrix.GetB(), transMatrix.GetC(),
			transMatrix.GetD(), transMatrix.GetE(), transMatrix.GetF());
	double x1 = 0;
	double y1 = 0;
	double x2 = img.GetWidth();
	double y2 = img.GetHeight();
	transform.transform(&x1, &y1);
	transform.transform(&x2, &y2);
	transform.invert();

	scanline_u8 sl; // better as scanline_p8 because the number of spans
	rasterizer_scanline_aa<> ras;
	const rect_i& cb = m_rendererBase->clip_box();
	ras.clip_box(cb.x1, cb.y1, cb.x2 + 1, cb.y2 + 1);

	path_storage imgRect;
	imgRect.move_to(x1, y1);
	imgRect.line_to(x1, y2);
	imgRect.line_to(x2, y2);
	imgRect.line_to(x2, y1);
	imgRect.close_polygon();
	ras.add_path(imgRect);

	if (img.HasAlpha()) {
		PixFmtAlpha img_pixf(source_buffer);
		ImageSourceTypeA img_src(img_pixf, agg::rgba(0, 0, 0, 0));
		InterpolatorType interpolator(transform);
		SpanAlloc sa;
		SpanGenTypeA sg(img_src, interpolator);

		double opacity = style.GetOpacity();
		if (opacity == 1) {
			render_scanlines_aa(ras, sl, *m_rendererBase, sa, sg);
		} else {
			SpanConvAlpha spanConvAlpha(opacity);
			SpanConvA sc(sg, spanConvAlpha);
			render_scanlines_aa(ras, sl, *m_rendererBase, sa, sc);
		}
		delete[] buf;
	} else {
		PixFmt img_pixf(source_buffer);
		ImageSourceType img_src(img_pixf, agg::rgba(0, 0, 0, 0));
		InterpolatorType interpolator(transform);
		SpanAlloc sa;
		SpanGenType sg(img_src, interpolator);

		double opacity = style.GetOpacity();
		if (opacity == 1) {
			render_scanlines_aa(ras, sl, *m_rendererBase, sa, sg);
		} else {
			SpanConvAlpha spanConvAlpha(opacity);
			SpanConv sc(sg, spanConvAlpha);
			render_scanlines_aa(ras, sl, *m_rendererBase, sa, sc);
		}
	}
}
