noinst_LTLIBRARIES = libwxsvg_agg.la

if USE_FREETYPE
INCLUDES = -I$(top_builddir)/include -I$(top_builddir)/include/wxSVG $(FREETYPE_CFLAGS)
libwxsvg_agg_la_SOURCES = SVGCanvasAgg.cpp SVGCanvasPathAgg.cpp
else
INCLUDES = -I$(top_builddir)/include -I$(top_builddir)/include/wxSVG
libwxsvg_agg_la_SOURCES = SVGCanvasAgg.cpp SVGCanvasPathAgg.cpp SVGCanvasTextAgg.cpp
endif