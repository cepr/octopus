
noinst_LTLIBRARIES = libwxsvg_freetype.la
libwxsvg_freetype_la_SOURCES = SVGCanvasTextFreetype.cpp
libwxsvg_freetype_la_LIBADD = $(FREETYPE_LIBS)

INCLUDES = -I$(top_builddir)/include -I$(top_builddir)/include/wxSVG\
 $(FREETYPE_CFLAGS) $(LIBART_CFLAGS) $(AGG_CFLAGS) $(CAIRO_CFLAGS)
