#----------------------------------------------------------------------------
# Name:         __init__.py
# Purpose:      The presence of this file turns this directory into a
#               Python package.
#
#----------------------------------------------------------------------------
import wx._core
import sys
sys.modules["_core"] = wx._core

from wxsvg import *

__all__ = [name for name in dir(wxsvg)
            if not (name.startswith('__') and name.endswith('__'))]

del wxsvg
