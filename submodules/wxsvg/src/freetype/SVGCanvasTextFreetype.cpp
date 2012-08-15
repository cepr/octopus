//////////////////////////////////////////////////////////////////////////////
// Name:        SVGCanvasTextFreetype.cpp
// Purpose:     Freetype canvas text
// Author:      Alex Thuering
// Created:     2005/05/23
// RCS-ID:      $Id: SVGCanvasTextFreetype.cpp,v 1.10 2010/07/22 20:41:41 ntalex Exp $
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////

#include "SVGCanvasTextFreetype.h"
#include <wx/log.h>

#include <ft2build.h>
#include FT_GLYPH_H
#include FT_OUTLINE_H

PangoFT2FontMap* wxSVGCanvasTextFreetype::s_fontmap = NULL;

void text_ft2_subst_func(FcPattern *pattern, gpointer data)
{
  FcPatternAddBool(pattern, FC_HINTING, 0);
  FcPatternAddBool(pattern, FC_ANTIALIAS, 0);
  FcPatternAddBool(pattern, FC_AUTOHINT, 0);	
  FcPatternAddBool(pattern, FC_SCALABLE, 1);
}

wxSVGCanvasTextFreetype::wxSVGCanvasTextFreetype(wxSVGCanvas* canvas):
 wxSVGCanvasText(canvas)
{
  m_dpi_x = m_dpi_y = 90;
  if (!s_fontmap)
  {
    g_type_init();
    s_fontmap = PANGO_FT2_FONT_MAP(pango_ft2_font_map_new());
    pango_ft2_font_map_set_resolution(s_fontmap, m_dpi_x, m_dpi_y);
    pango_ft2_font_map_set_default_substitute(
	  s_fontmap, text_ft2_subst_func, NULL, (GDestroyNotify) NULL);
  }
  m_pango_context = pango_ft2_font_map_create_context(s_fontmap);
  m_font_family = NULL;
  m_layout = pango_layout_new(m_pango_context);
}

wxSVGCanvasTextFreetype::~wxSVGCanvasTextFreetype()
{
  g_object_unref(G_OBJECT(m_layout));
  g_object_unref(m_pango_context);
  if (m_font_family)
    g_free(m_font_family);
}

void wxSVGCanvasTextFreetype::Init(wxSVGTextElement& element,
	  const wxCSSStyleDeclaration& style)
{
  wxSVGCanvasText::Init(element, style);
}

void wxSVGCanvasTextFreetype::InitText(const wxString& text,
  const wxCSSStyleDeclaration& style)
{
  // set font
  PangoFontDescription* font_desc = pango_font_description_copy(
    pango_context_get_font_description(m_pango_context));
  
  if (style.HasFontFamily() && style.GetFontFamily().length())
  {
    if (m_font_family)
      g_free(m_font_family);
    m_font_family = g_strdup(style.GetFontFamily().ToAscii());
    pango_font_description_set_family_static(font_desc, m_font_family);
  }
  
  if (style.GetFontStyle() == wxCSS_VALUE_OBLIQUE)
	pango_font_description_set_style(font_desc, PANGO_STYLE_OBLIQUE);
  else if (style.GetFontStyle() == wxCSS_VALUE_ITALIC)
	pango_font_description_set_style(font_desc, PANGO_STYLE_ITALIC);
  else
	pango_font_description_set_style(font_desc, PANGO_STYLE_NORMAL);
  
  if (style.GetFontVariant() == wxCSS_VALUE_SMALL_CAPS)
	pango_font_description_set_variant(font_desc, PANGO_VARIANT_SMALL_CAPS);
  else
	pango_font_description_set_variant(font_desc, PANGO_VARIANT_NORMAL);
  
  if (style.GetFontWeight() == wxCSS_VALUE_BOLD)
	pango_font_description_set_weight(font_desc, PANGO_WEIGHT_BOLD);
  else if (style.GetFontWeight() == wxCSS_VALUE_BOLDER)
	pango_font_description_set_weight(font_desc, PANGO_WEIGHT_ULTRABOLD);
  else if (style.GetFontWeight() == wxCSS_VALUE_LIGHTER)
	pango_font_description_set_weight(font_desc, PANGO_WEIGHT_LIGHT);
  else
	pango_font_description_set_weight(font_desc, PANGO_WEIGHT_NORMAL);
  
  if (style.GetFontStretch() == wxCSS_VALUE_ULTRA_CONDENSED)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_ULTRA_CONDENSED);
  else if (style.GetFontStretch() == wxCSS_VALUE_EXTRA_CONDENSED)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_EXTRA_CONDENSED);
  else if (style.GetFontStretch() == wxCSS_VALUE_CONDENSED ||
		   style.GetFontStretch() == wxCSS_VALUE_NARROWER)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_CONDENSED);
  else if (style.GetFontStretch() == wxCSS_VALUE_SEMI_CONDENSED)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_SEMI_CONDENSED);
  else if (style.GetFontStretch() == wxCSS_VALUE_SEMI_EXPANDED)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_SEMI_EXPANDED);
  else if (style.GetFontStretch() == wxCSS_VALUE_EXPANDED ||
		   style.GetFontStretch() == wxCSS_VALUE_WIDER)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_EXPANDED);
  else if (style.GetFontStretch() == wxCSS_VALUE_EXTRA_EXPANDED)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_EXTRA_EXPANDED);
  else if (style.GetFontStretch() == wxCSS_VALUE_ULTRA_EXPANDED)
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_ULTRA_EXPANDED);
  else
	pango_font_description_set_stretch(font_desc, PANGO_STRETCH_NORMAL);
  
  pango_font_description_set_size(font_desc,
	(int) (style.GetFontSize()*PANGO_SCALE/m_dpi_y*72));
	
  pango_layout_set_font_description(m_layout, font_desc);
  pango_font_description_free(font_desc);
  
  // init text
  pango_layout_set_text(m_layout, text.mb_str(wxConvUTF8), -1);
  
  m_endpath = false;
  int offx = 0, offy = 0;
  PangoRectangle ink;
  PangoRectangle logical;
  pango_layout_get_pixel_extents(m_layout, &ink, &logical);
  if (ink.width >= 1 && ink.height >= 1)
  {
	offx = wxMin(ink.x, logical.x);
	offy = wxMin(ink.y, logical.y);
  }
  double x = m_tx + offx;
  double y = m_ty + offy;
  x *= PANGO_SCALE;
  y *= PANGO_SCALE;
  PangoLayoutIter* iter = pango_layout_get_iter(m_layout);
  if (iter)
  {
	PangoLayoutLine* line = pango_layout_iter_get_line(iter);
	PangoRectangle rect;
	pango_layout_iter_get_line_extents(iter, NULL, &rect);
	int baseline = pango_layout_iter_get_baseline(iter);
	RenderLine(line, (int)x + rect.x, (int)y + baseline);
	m_tx += rect.width/PANGO_SCALE + offx;
  }
  pango_layout_iter_free(iter);
  if (m_endpath)
	m_char->path->ClosePath();
}

void wxSVGCanvasTextFreetype::RenderLine(PangoLayoutLine *line, int x, int y)
{
  PangoRectangle rect;
  int x_off = 0;
  for (GSList* list = line->runs; list; list = list->next)
  {
	PangoLayoutRun* run = (PangoLayoutRun*)list->data;
	pango_glyph_string_extents (run->glyphs, run->item->analysis.font, NULL, &rect);
	x_off += RenderGlyphs(run->item->analysis.font, run->glyphs, x + x_off, y);
  }
}

#if FREETYPE_MAJOR > 2 || (FREETYPE_MAJOR == 2 && FREETYPE_MINOR > 1)
#define constFT_Vector const FT_Vector
#else
#define constFT_Vector FT_Vector
#endif

static int moveto(constFT_Vector* to, gpointer data)
{
  wxSVGCanvasTextFreetype* canvasText = (wxSVGCanvasTextFreetype*) data;
  
  if (canvasText->m_endpath)
	canvasText->m_char->path->ClosePath();
  else
	canvasText->m_endpath = true;

  double x = canvasText->m_offset_x + (double)to->x / 64;
  double y = canvasText->m_offset_y - (double)to->y / 64;
  canvasText->m_char->path->MoveTo(x, y);

  return 0;
}

static int lineto (constFT_Vector* to, gpointer data)
{
  wxSVGCanvasTextFreetype* canvasText = (wxSVGCanvasTextFreetype*) data;
  if (!canvasText->m_endpath)
	  return 0;
  
  double x = canvasText->m_offset_x + (double)to->x / 64;
  double y = canvasText->m_offset_y - (double)to->y / 64;
  canvasText->m_char->path->LineTo(x, y);
  
  return 0;
}

static int conicto(constFT_Vector* ftcontrol, constFT_Vector* to, gpointer data)
{
  wxSVGCanvasTextFreetype* canvasText = (wxSVGCanvasTextFreetype*) data;
  if (!canvasText->m_endpath)
	  return 0;
  
  double x1 = canvasText->m_offset_x + (double)ftcontrol->x / 64;
  double y1 = canvasText->m_offset_y - (double)ftcontrol->y / 64;
  double x = canvasText->m_offset_x + (double)to->x / 64;
  double y = canvasText->m_offset_y - (double)to->y / 64;
  canvasText->m_char->path->CurveToQuadratic(x1, y1, x, y);
  
  return 0;
}

static int cubicto(constFT_Vector* ftcontrol1, constFT_Vector* ftcontrol2,
 constFT_Vector* to, gpointer data)
{
  wxSVGCanvasTextFreetype* canvasText = (wxSVGCanvasTextFreetype*) data;
  if (!canvasText->m_endpath)
	  return 0;
  
  double x1 = canvasText->m_offset_x + (double)ftcontrol1->x / 64;
  double y1 = canvasText->m_offset_y - (double)ftcontrol1->y / 64;
  double x2 = canvasText->m_offset_x + (double)ftcontrol2->x / 64;
  double y2 = canvasText->m_offset_y - (double)ftcontrol2->y / 64;
  double x = canvasText->m_offset_x + (double)to->x / 64;
  double y = canvasText->m_offset_y - (double)to->y / 64;
  canvasText->m_char->path->CurveToCubic(x1, y1, x2, y2, x, y);
  
  return 0;
}

static const FT_Outline_Funcs outline_funcs = {
  moveto, lineto, conicto, cubicto, 0, 0
};

int wxSVGCanvasTextFreetype::RenderGlyphs(PangoFont* font, PangoGlyphString* glyphs, int x, int y) {
  int x_position = 0;
  PangoGlyphInfo* gi = glyphs->glyphs;
  for (int i = 0; i < glyphs->num_glyphs; i++, gi++)
  {
	if (gi->glyph)
	{
	  BeginChar();
	  double pos_x = x + x_position + gi->geometry.x_offset;
	  double pos_y = y + gi->geometry.y_offset;
	  
	  FT_Face face = pango_ft2_font_get_face(font);
	  if (FT_Load_Glyph(face, (FT_UInt) gi->glyph, FT_LOAD_NO_BITMAP|FT_LOAD_TARGET_MONO|FT_LOAD_NO_HINTING) == 0) {
		  FT_Glyph glyph;
		  if (FT_Get_Glyph(face->glyph, &glyph) == 0) {
			  if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
			  {
				FT_OutlineGlyph outline_glyph = (FT_OutlineGlyph) glyph;
				m_offset_x = pos_x / PANGO_SCALE;
				m_offset_y = pos_y / PANGO_SCALE - (int)face->size->metrics.ascender / 64;
				FT_Outline_Decompose(&outline_glyph->outline, &outline_funcs, this);			
			  }
			  FT_Done_Glyph (glyph);
			  m_char->bbox = wxSVGRect(m_offset_x, m_offset_y, glyphs->glyphs[i].geometry.width / PANGO_SCALE, 0);
		  }
	  }
	  EndChar();
	}
	x_position += glyphs->glyphs[i].geometry.width;
  }
  return x_position;
}

