noinst_LTLIBRARIES = libwxsvg_agg.la

if USE_FREETYPE
INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/include/wxSVG $(FREETYPE_CFLAGS)
libwxsvg_agg_la_SOURCES = SVGCanvasAgg.cpp SVGCanvasPathAgg.cpp
else
INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/include/wxSVG
libwxsvg_agg_la_SOURCES = SVGCanvasAgg.cpp SVGCanvasPathAgg.cpp SVGCanvasTextAgg.cpp
endif
