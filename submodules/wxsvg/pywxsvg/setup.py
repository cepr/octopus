#!/usr/bin/env python
#----------------------------------------------------------------------
# Name:        setup.py
# Purpose:     Distutils script for building PyWxSvg
#
# Author:      Edouard TISSERANT, 
#
# Licence:     wxWindows license
#----------------------------------------------------------------------

import sys, os

from wx.build.config import *

if WXPORT == 'msw':
    RENDER="AGG"
    RENDER_LIBPATH="/opt/agg/2.5/lib/"
    RENDER_LIBS=['aggfontwin32tt','agg']
else:
    RENDER="LIBART"
    RENDER_LIBPATH="/usr/lib/"
    RENDER_LIBS=['freetype', 'pangoft2-1.0', 'pango-1.0']

for option,islist in [
        ('RENDER',False),
        ('RENDER_LIBS',True),
        ('RENDER_LIBPATH',False)]:
    for x in range(len(sys.argv)):
        if sys.argv[x].split('=')[0] == option:
            pos = sys.argv[x].find('=') + 1
            if pos > 0:
                if not islist:
                    vars()[option] = sys.argv[x][pos:]
                else:
                    vars()[option] = sys.argv[x][pos:].split(',')
                sys.argv[x] = ''

sys.argv = filter(None, sys.argv)

sys.setup_is_main =  __name__ == "__main__"  # an icky hack!

BUILD_OPTIONS = { 'build_base' : BUILD_BASE }
if WXPORT == 'msw':
    BUILD_OPTIONS[ 'compiler' ] = COMPILER

#----------------------------------------------------------------------
# Define the WXSVG extension module
#----------------------------------------------------------------------

PKGDIR='wx/wxsvg'

msg('Preparing WXSVG...')
location = '.'

other_includes = [os.path.join('..','include'), os.path.join(WXPY_SRC,'include')]

swig_sources = run_swig(['wxsvg.i'], location, GENDIR, PKGDIR,
                        USE_SWIG, swig_force, swig_args, swig_deps)

ext = Extension('_wxsvg',
                swig_sources,

                include_dirs =  includes + other_includes,
                define_macros = defines,

                library_dirs = libdirs + ['../src/.libs/','../src/'+RENDER.lower()+'/.libs/', RENDER_LIBPATH],
                libraries = ['wxsvg','wxsvg_'+RENDER.lower()] + libs + RENDER_LIBS,

                #extra_compile_args = cflags + ['-DUSE_RENDER_LIBART'],
                extra_compile_args = cflags + ['-DUSE_RENDER_'+RENDER],
                extra_link_args = lflags,
                #extra_link_args = ['../src/libwxsvg.la'] + lflags,
                )

wxpExtensions.append(ext)


#----------------------------------------------------------------------
# Tools, scripts data files, etc.
#----------------------------------------------------------------------
if NO_HEADERS:
    HEADERS = None
else:
    h_files = []
    i_files = glob.glob(opj("src/*.i"))   + \
              glob.glob(opj("src/_*.py"))

    HEADERS = zip(h_files, ["/wxPython"]*len(h_files)) + \
              zip(i_files, ["/wxPython/i_files"]*len(i_files))

#----------------------------------------------------------------------
# Do the Setup/Build/Install/Whatever
#----------------------------------------------------------------------

if INSTALL_MULTIVERSION:
    EXTRA_PATH = getExtraPath(addOpts=EP_ADD_OPTS, shortVer=not EP_FULL_VER)
else:
    EXTRA_PATH = None
       
       
if __name__ == "__main__":
    setup(name             = 'wxsvg',
          version          = "1.0.0.0-beta7",
          description      = "wxPython bindings for wxSVG",
          long_description = "wxPython bindings for wxSVG",
          author           = "Edouard Tisserant, Alex Thuering",
          author_email     = "edouard.tisserant@lolitech.fr, alex.thuering@web.de",
          url              = "http://wxsvg.sourceforge.net/",
          download_url     = "http://sourceforge.net/project/showfiles.php?group_id=124832",
          license          = LICENSE,
          platforms        = PLATFORMS,
          classifiers      = filter(None, CLASSIFIERS.split("\n")),
          keywords         = KEYWORDS + ",SVG,wxSVG",

          packages = [ 'wx.wxsvg' ],

          extra_path = EXTRA_PATH,

          ext_package = PKGDIR,
          ext_modules = wxpExtensions,

          options = { 'build'            : BUILD_OPTIONS,
                      },

          scripts =    None,
          data_files = None,
          headers =    HEADERS,

          # Override some of the default distutils command classes with my own
          cmdclass = { 'install' :        wx_install,
                       'install_data':    wx_smart_install_data,
                       'install_headers': wx_install_headers,
                       'clean':           wx_extra_clean,
                       },
          )


#----------------------------------------------------------------------
#----------------------------------------------------------------------
