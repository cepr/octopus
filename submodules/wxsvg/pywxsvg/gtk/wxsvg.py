# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

"""
wxSVG wrapper

"""

import _wxsvg
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


def _swig_setattr_nondynamic_method(set):
    def set_attr(self,name,value):
        if (name == "thisown"): return self.this.own(value)
        if hasattr(self,name) or (name == "this"):
            set(self,name,value)
        else:
            raise AttributeError("You cannot add attributes to %s" % self)
    return set_attr


import _core
import wx 
__docfilter__ = wx._core.__DocFilter(globals()) 
SVG_COORDINATES_USER = _wxsvg.SVG_COORDINATES_USER
SVG_COORDINATES_VIEWPORT = _wxsvg.SVG_COORDINATES_VIEWPORT
SVG_COORDINATES_SCREEN = _wxsvg.SVG_COORDINATES_SCREEN
class SvgXmlNode(object):
    """Proxy of C++ SvgXmlNode class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def CloneNode(*args, **kwargs):
        """CloneNode(self, bool deep=True) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_CloneNode(*args, **kwargs)

    def __init__(self, *args): 
        """
        __init__(self) -> SvgXmlNode
        __init__(self, SvgXmlNode parent, wxSvgXmlNodeType type, String name, 
            String content, wxSvgXmlProperty props, SvgXmlNode next) -> SvgXmlNode
        __init__(self, SvgXmlNode node) -> SvgXmlNode
        __init__(self, wxSvgXmlNodeType type, String name, String content=wxEmptyString) -> SvgXmlNode
        """
        _wxsvg.SvgXmlNode_swiginit(self,_wxsvg.new_SvgXmlNode(*args))
        self._setOORInfo(self)

    def AddChild(*args, **kwargs):
        """AddChild(self, SvgXmlNode child)"""
        return _wxsvg.SvgXmlNode_AddChild(*args, **kwargs)

    def AppendChild(*args, **kwargs):
        """AppendChild(self, SvgXmlNode child) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_AppendChild(*args, **kwargs)

    def InsertChild(*args, **kwargs):
        """InsertChild(self, SvgXmlNode child, SvgXmlNode before_node)"""
        return _wxsvg.SvgXmlNode_InsertChild(*args, **kwargs)

    def InsertBefore(*args, **kwargs):
        """InsertBefore(self, SvgXmlNode newChild, SvgXmlNode refChild) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_InsertBefore(*args, **kwargs)

    def RemoveChild(*args, **kwargs):
        """RemoveChild(self, SvgXmlNode child) -> bool"""
        return _wxsvg.SvgXmlNode_RemoveChild(*args, **kwargs)

    def DeleteProperty(*args, **kwargs):
        """DeleteProperty(self, String name) -> bool"""
        return _wxsvg.SvgXmlNode_DeleteProperty(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _wxsvg.SvgXmlNode_GetName(*args, **kwargs)

    def GetContent(*args, **kwargs):
        """GetContent(self) -> String"""
        return _wxsvg.SvgXmlNode_GetContent(*args, **kwargs)

    def GetOwnerDocument(*args, **kwargs):
        """GetOwnerDocument(self) -> SvgXmlDocument"""
        return _wxsvg.SvgXmlNode_GetOwnerDocument(*args, **kwargs)

    def GetParent(*args, **kwargs):
        """GetParent(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetParent(*args, **kwargs)

    def GetNext(*args, **kwargs):
        """GetNext(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetNext(*args, **kwargs)

    def GetChildren(*args, **kwargs):
        """GetChildren(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetChildren(*args, **kwargs)

    def GetParentNode(*args, **kwargs):
        """GetParentNode(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetParentNode(*args, **kwargs)

    def GetChildNodes(*args, **kwargs):
        """GetChildNodes(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetChildNodes(*args, **kwargs)

    def GetFirstChild(*args, **kwargs):
        """GetFirstChild(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetFirstChild(*args, **kwargs)

    def GetLastChild(*args, **kwargs):
        """GetLastChild(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetLastChild(*args, **kwargs)

    def GetPreviousSibling(*args, **kwargs):
        """GetPreviousSibling(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetPreviousSibling(*args, **kwargs)

    def GetNextSibling(*args, **kwargs):
        """GetNextSibling(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlNode_GetNextSibling(*args, **kwargs)

    def GetProperties(*args, **kwargs):
        """GetProperties(self) -> wxSvgXmlProperty"""
        return _wxsvg.SvgXmlNode_GetProperties(*args, **kwargs)

    def GetPropVal(*args, **kwargs):
        """GetPropVal(self, String propName, String defaultVal) -> String"""
        return _wxsvg.SvgXmlNode_GetPropVal(*args, **kwargs)

    def HasProp(*args, **kwargs):
        """HasProp(self, String propName) -> bool"""
        return _wxsvg.SvgXmlNode_HasProp(*args, **kwargs)

    def SetType(*args, **kwargs):
        """SetType(self, wxSvgXmlNodeType type)"""
        return _wxsvg.SvgXmlNode_SetType(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _wxsvg.SvgXmlNode_SetName(*args, **kwargs)

    def SetContent(*args, **kwargs):
        """SetContent(self, String con)"""
        return _wxsvg.SvgXmlNode_SetContent(*args, **kwargs)

    def SetParent(*args, **kwargs):
        """SetParent(self, SvgXmlNode parent)"""
        return _wxsvg.SvgXmlNode_SetParent(*args, **kwargs)

    def SetNext(*args, **kwargs):
        """SetNext(self, SvgXmlNode next)"""
        return _wxsvg.SvgXmlNode_SetNext(*args, **kwargs)

    def SetChildren(*args, **kwargs):
        """SetChildren(self, SvgXmlNode child)"""
        return _wxsvg.SvgXmlNode_SetChildren(*args, **kwargs)

    def SetProperties(*args, **kwargs):
        """SetProperties(self, wxSvgXmlProperty prop)"""
        return _wxsvg.SvgXmlNode_SetProperties(*args, **kwargs)

    def AddProperty(*args):
        """
        AddProperty(self, String name, String value)
        AddProperty(self, wxSvgXmlProperty prop)
        """
        return _wxsvg.SvgXmlNode_AddProperty(*args)

    def GetAttribute(*args, **kwargs):
        """GetAttribute(self, String name) -> String"""
        return _wxsvg.SvgXmlNode_GetAttribute(*args, **kwargs)

    def GetAttributeNS(*args, **kwargs):
        """GetAttributeNS(self, String namespaceURI, String localName) -> String"""
        return _wxsvg.SvgXmlNode_GetAttributeNS(*args, **kwargs)

    def SetAttribute(*args, **kwargs):
        """SetAttribute(self, String name, String value) -> bool"""
        return _wxsvg.SvgXmlNode_SetAttribute(*args, **kwargs)

    def SetAttributeNS(*args, **kwargs):
        """SetAttributeNS(self, String namespaceURI, String qualifiedName, String value) -> bool"""
        return _wxsvg.SvgXmlNode_SetAttributeNS(*args, **kwargs)

    def RemoveAttribute(*args, **kwargs):
        """RemoveAttribute(self, String name)"""
        return _wxsvg.SvgXmlNode_RemoveAttribute(*args, **kwargs)

    def RemoveAttributeNS(*args, **kwargs):
        """RemoveAttributeNS(self, String namespaceURI, String localName)"""
        return _wxsvg.SvgXmlNode_RemoveAttributeNS(*args, **kwargs)

    def HasAttribute(*args, **kwargs):
        """HasAttribute(self, String name) -> bool"""
        return _wxsvg.SvgXmlNode_HasAttribute(*args, **kwargs)

    def HasAttributeNS(*args, **kwargs):
        """HasAttributeNS(self, String namespaceURI, String localName) -> bool"""
        return _wxsvg.SvgXmlNode_HasAttributeNS(*args, **kwargs)

    def SetOwnerDocument(*args, **kwargs):
        """SetOwnerDocument(self, SvgXmlDocument ownerDocument)"""
        return _wxsvg.SvgXmlNode_SetOwnerDocument(*args, **kwargs)

_wxsvg.SvgXmlNode_swigregister(SvgXmlNode)
cvar = _wxsvg.cvar
SVGControlNameStr = cvar.SVGControlNameStr

def PreSvgXmlNode(*args, **kwargs):
    """PreSvgXmlNode() -> SvgXmlNode"""
    val = _wxsvg.new_PreSvgXmlNode(*args, **kwargs)
    return val

class SvgXmlDocument(object):
    """Proxy of C++ SvgXmlDocument class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """
        __init__(self) -> SvgXmlDocument
        __init__(self, String filename, String encoding=wxT("UTF-8")) -> SvgXmlDocument
        """
        _wxsvg.SvgXmlDocument_swiginit(self,_wxsvg.new_SvgXmlDocument(*args))
        self._setOORInfo(self)

    def Load(*args, **kwargs):
        """Load(self, String filename, String encoding=wxT("UTF-8")) -> bool"""
        return _wxsvg.SvgXmlDocument_Load(*args, **kwargs)

    def Save(*args, **kwargs):
        """Save(self, String filename) -> bool"""
        return _wxsvg.SvgXmlDocument_Save(*args, **kwargs)

    def IsOk(*args, **kwargs):
        """IsOk(self) -> bool"""
        return _wxsvg.SvgXmlDocument_IsOk(*args, **kwargs)

    def GetRoot(*args, **kwargs):
        """GetRoot(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlDocument_GetRoot(*args, **kwargs)

    def GetVersion(*args, **kwargs):
        """GetVersion(self) -> String"""
        return _wxsvg.SvgXmlDocument_GetVersion(*args, **kwargs)

    def GetFileEncoding(*args, **kwargs):
        """GetFileEncoding(self) -> String"""
        return _wxsvg.SvgXmlDocument_GetFileEncoding(*args, **kwargs)

    def SetRoot(*args, **kwargs):
        """SetRoot(self, SvgXmlNode node)"""
        return _wxsvg.SvgXmlDocument_SetRoot(*args, **kwargs)

    def SetVersion(*args, **kwargs):
        """SetVersion(self, String version)"""
        return _wxsvg.SvgXmlDocument_SetVersion(*args, **kwargs)

    def SetFileEncoding(*args, **kwargs):
        """SetFileEncoding(self, String encoding)"""
        return _wxsvg.SvgXmlDocument_SetFileEncoding(*args, **kwargs)

    def CreateElement(*args, **kwargs):
        """CreateElement(self, String tagName) -> SvgXmlElement"""
        return _wxsvg.SvgXmlDocument_CreateElement(*args, **kwargs)

    def CreateElementNS(*args, **kwargs):
        """CreateElementNS(self, String namespaceURI, String qualifiedName) -> SvgXmlElement"""
        return _wxsvg.SvgXmlDocument_CreateElementNS(*args, **kwargs)

    def AppendChild(*args, **kwargs):
        """AppendChild(self, SvgXmlNode child) -> SvgXmlNode"""
        return _wxsvg.SvgXmlDocument_AppendChild(*args, **kwargs)

    def RemoveChild(*args, **kwargs):
        """RemoveChild(self, SvgXmlNode child) -> SvgXmlNode"""
        return _wxsvg.SvgXmlDocument_RemoveChild(*args, **kwargs)

    def GetFirstChild(*args, **kwargs):
        """GetFirstChild(self) -> SvgXmlNode"""
        return _wxsvg.SvgXmlDocument_GetFirstChild(*args, **kwargs)

_wxsvg.SvgXmlDocument_swigregister(SvgXmlDocument)

def PreSvgXmlDocument(*args, **kwargs):
    """PreSvgXmlDocument() -> SvgXmlDocument"""
    val = _wxsvg.new_PreSvgXmlDocument(*args, **kwargs)
    return val

class SVGLocatable(object):
    """Proxy of C++ SVGLocatable class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetNearestViewportElement(*args, **kwargs):
        """GetNearestViewportElement(self) -> SVGElement"""
        return _wxsvg.SVGLocatable_GetNearestViewportElement(*args, **kwargs)

    def SetNearestViewportElement(*args, **kwargs):
        """SetNearestViewportElement(self, SVGElement n)"""
        return _wxsvg.SVGLocatable_SetNearestViewportElement(*args, **kwargs)

    def GetFarthestViewportElement(*args, **kwargs):
        """GetFarthestViewportElement(self) -> SVGElement"""
        return _wxsvg.SVGLocatable_GetFarthestViewportElement(*args, **kwargs)

    def SetFarthestViewportElement(*args, **kwargs):
        """SetFarthestViewportElement(self, SVGElement n)"""
        return _wxsvg.SVGLocatable_SetFarthestViewportElement(*args, **kwargs)

    def GetBBox(*args, **kwargs):
        """GetBBox(self, int coordinates=SVG_COORDINATES_USER) -> SVGRect"""
        return _wxsvg.SVGLocatable_GetBBox(*args, **kwargs)

    def GetResultBBox(*args, **kwargs):
        """GetResultBBox(self, int coordinates=SVG_COORDINATES_USER) -> SVGRect"""
        return _wxsvg.SVGLocatable_GetResultBBox(*args, **kwargs)

    def GetElementBBox(*args, **kwargs):
        """GetElementBBox(SVGElement element, int coordinates=SVG_COORDINATES_USER) -> SVGRect"""
        return _wxsvg.SVGLocatable_GetElementBBox(*args, **kwargs)

    GetElementBBox = staticmethod(GetElementBBox)
    def GetElementResultBBox(*args, **kwargs):
        """GetElementResultBBox(SVGElement element, int coordinates=SVG_COORDINATES_USER) -> SVGRect"""
        return _wxsvg.SVGLocatable_GetElementResultBBox(*args, **kwargs)

    GetElementResultBBox = staticmethod(GetElementResultBBox)
    def GetCTM(*args):
        """
        GetCTM() -> wxSVGMatrix
        GetCTM(SVGElement element) -> wxSVGMatrix
        """
        return _wxsvg.SVGLocatable_GetCTM(*args)

    GetCTM = staticmethod(GetCTM)
    def GetScreenCTM(*args):
        """
        GetScreenCTM() -> wxSVGMatrix
        GetScreenCTM(SVGElement element) -> wxSVGMatrix
        """
        return _wxsvg.SVGLocatable_GetScreenCTM(*args)

    GetScreenCTM = staticmethod(GetScreenCTM)
    def GetTransformToElement(*args, **kwargs):
        """GetTransformToElement(self, SVGElement element) -> wxSVGMatrix"""
        return _wxsvg.SVGLocatable_GetTransformToElement(*args, **kwargs)

_wxsvg.SVGLocatable_swigregister(SVGLocatable)

def SVGLocatable_GetElementBBox(*args, **kwargs):
  """SVGLocatable_GetElementBBox(SVGElement element, int coordinates=SVG_COORDINATES_USER) -> SVGRect"""
  return _wxsvg.SVGLocatable_GetElementBBox(*args, **kwargs)

def SVGLocatable_GetElementResultBBox(*args, **kwargs):
  """SVGLocatable_GetElementResultBBox(SVGElement element, int coordinates=SVG_COORDINATES_USER) -> SVGRect"""
  return _wxsvg.SVGLocatable_GetElementResultBBox(*args, **kwargs)

def SVGLocatable_GetCTM(*args):
  """
    GetCTM() -> wxSVGMatrix
    SVGLocatable_GetCTM(SVGElement element) -> wxSVGMatrix
    """
  return _wxsvg.SVGLocatable_GetCTM(*args)

def SVGLocatable_GetScreenCTM(*args):
  """
    GetScreenCTM() -> wxSVGMatrix
    SVGLocatable_GetScreenCTM(SVGElement element) -> wxSVGMatrix
    """
  return _wxsvg.SVGLocatable_GetScreenCTM(*args)

class SVGElement(SvgXmlNode,SVGLocatable):
    """Proxy of C++ SVGElement class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetId(*args, **kwargs):
        """GetId(self) -> String"""
        return _wxsvg.SVGElement_GetId(*args, **kwargs)

    def SetId(*args, **kwargs):
        """SetId(self, String n)"""
        return _wxsvg.SVGElement_SetId(*args, **kwargs)

    def GetXmlbase(*args, **kwargs):
        """GetXmlbase(self) -> String"""
        return _wxsvg.SVGElement_GetXmlbase(*args, **kwargs)

    def SetXmlbase(*args, **kwargs):
        """SetXmlbase(self, String n)"""
        return _wxsvg.SVGElement_SetXmlbase(*args, **kwargs)

    def GetOwnerSVGElement(*args, **kwargs):
        """GetOwnerSVGElement(self) -> SVGSVGElement"""
        return _wxsvg.SVGElement_GetOwnerSVGElement(*args, **kwargs)

    def SetOwnerSVGElement(*args, **kwargs):
        """SetOwnerSVGElement(self, SVGSVGElement n)"""
        return _wxsvg.SVGElement_SetOwnerSVGElement(*args, **kwargs)

    def GetViewportElement(*args, **kwargs):
        """GetViewportElement(self) -> SVGElement"""
        return _wxsvg.SVGElement_GetViewportElement(*args, **kwargs)

    def SetViewportElement(*args, **kwargs):
        """SetViewportElement(self, SVGElement n)"""
        return _wxsvg.SVGElement_SetViewportElement(*args, **kwargs)

    def GetDtd(*args, **kwargs):
        """GetDtd(self) -> wxSVGDTD"""
        return _wxsvg.SVGElement_GetDtd(*args, **kwargs)

    def GetAttributes(*args, **kwargs):
        """GetAttributes(self) -> wxSvgXmlAttrHash"""
        return _wxsvg.SVGElement_GetAttributes(*args, **kwargs)

_wxsvg.SVGElement_swigregister(SVGElement)

class NodeListCls(object):
    """Proxy of C++ NodeListCls class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, wxNodeList m_list) -> NodeListCls"""
        _wxsvg.NodeListCls_swiginit(self,_wxsvg.new_NodeListCls(*args, **kwargs))
    def GetFirstElement(*args, **kwargs):
        """GetFirstElement(self) -> SVGElement"""
        return _wxsvg.NodeListCls_GetFirstElement(*args, **kwargs)

    def GetElement(*args, **kwargs):
        """GetElement(self, int i) -> SVGElement"""
        return _wxsvg.NodeListCls_GetElement(*args, **kwargs)

    def GetSize(*args, **kwargs):
        """GetSize(self) -> int"""
        return _wxsvg.NodeListCls_GetSize(*args, **kwargs)

_wxsvg.NodeListCls_swigregister(NodeListCls)

def PreNodeListCls(*args, **kwargs):
    """PreNodeListCls() -> NodeListCls"""
    val = _wxsvg.new_PreNodeListCls(*args, **kwargs)
    return val

class DocumentEvent(object):
    """Proxy of C++ DocumentEvent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
_wxsvg.DocumentEvent_swigregister(DocumentEvent)

class SVGDocument(SvgXmlDocument,DocumentEvent):
    """Proxy of C++ SVGDocument class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, String filename, String encoding=wxT("UTF-8")) -> SVGDocument"""
        _wxsvg.SVGDocument_swiginit(self,_wxsvg.new_SVGDocument(*args, **kwargs))
    __swig_destroy__ = _wxsvg.delete_SVGDocument
    __del__ = lambda self : None;
    def GetRootElement(*args, **kwargs):
        """GetRootElement(self) -> SVGSVGElement"""
        return _wxsvg.SVGDocument_GetRootElement(*args, **kwargs)

    def SetRootElement(*args, **kwargs):
        """SetRootElement(self, SVGSVGElement n)"""
        return _wxsvg.SVGDocument_SetRootElement(*args, **kwargs)

    def GetElementById(*args, **kwargs):
        """GetElementById(self, String id) -> SVGElement"""
        return _wxsvg.SVGDocument_GetElementById(*args, **kwargs)

    def Render(*args, **kwargs):
        """Render(self, int width=-1, int height=-1, SVGRect rect=None) -> Image"""
        return _wxsvg.SVGDocument_Render(*args, **kwargs)

    def RenderElementById(*args, **kwargs):
        """RenderElementById(self, String id) -> Image"""
        return _wxsvg.SVGDocument_RenderElementById(*args, **kwargs)

_wxsvg.SVGDocument_swigregister(SVGDocument)

def PreSVGDocument(*args, **kwargs):
    """PreSVGDocument() -> SVGDocument"""
    val = _wxsvg.new_PreSVGDocument(*args, **kwargs)
    return val

class SVGRect(object):
    """Proxy of C++ SVGRect class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def GetX(*args, **kwargs):
        """GetX(self) -> double"""
        return _wxsvg.SVGRect_GetX(*args, **kwargs)

    def SetX(*args, **kwargs):
        """SetX(self, double n)"""
        return _wxsvg.SVGRect_SetX(*args, **kwargs)

    def GetY(*args, **kwargs):
        """GetY(self) -> double"""
        return _wxsvg.SVGRect_GetY(*args, **kwargs)

    def SetY(*args, **kwargs):
        """SetY(self, double n)"""
        return _wxsvg.SVGRect_SetY(*args, **kwargs)

    def GetWidth(*args, **kwargs):
        """GetWidth(self) -> double"""
        return _wxsvg.SVGRect_GetWidth(*args, **kwargs)

    def SetWidth(*args, **kwargs):
        """SetWidth(self, double n)"""
        return _wxsvg.SVGRect_SetWidth(*args, **kwargs)

    def GetHeight(*args, **kwargs):
        """GetHeight(self) -> double"""
        return _wxsvg.SVGRect_GetHeight(*args, **kwargs)

    def SetHeight(*args, **kwargs):
        """SetHeight(self, double n)"""
        return _wxsvg.SVGRect_SetHeight(*args, **kwargs)

    def IsEmpty(*args, **kwargs):
        """IsEmpty(self) -> bool"""
        return _wxsvg.SVGRect_IsEmpty(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _wxsvg.SVGRect_Clear(*args, **kwargs)

    def __init__(self, *args): 
        """
        __init__(self) -> SVGRect
        __init__(self, double x, double y, double width, double height) -> SVGRect
        """
        _wxsvg.SVGRect_swiginit(self,_wxsvg.new_SVGRect(*args))
    __swig_destroy__ = _wxsvg.delete_SVGRect
    __del__ = lambda self : None;
    def GetValueAsString(*args, **kwargs):
        """GetValueAsString(self) -> String"""
        return _wxsvg.SVGRect_GetValueAsString(*args, **kwargs)

    def SetValueAsString(*args, **kwargs):
        """SetValueAsString(self, String value)"""
        return _wxsvg.SVGRect_SetValueAsString(*args, **kwargs)

    def MatrixTransform(*args, **kwargs):
        """MatrixTransform(self, wxSVGMatrix matrix) -> SVGRect"""
        return _wxsvg.SVGRect_MatrixTransform(*args, **kwargs)

_wxsvg.SVGRect_swigregister(SVGRect)

class SVGSVGElement(object):
    """Proxy of C++ SVGSVGElement class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetX(*args, **kwargs):
        """GetX(self) -> SVGAnimatedLength"""
        return _wxsvg.SVGSVGElement_GetX(*args, **kwargs)

    def SetX(*args):
        """
        SetX(self, SVGAnimatedLength n)
        SetX(self, SVGLength n)
        """
        return _wxsvg.SVGSVGElement_SetX(*args)

    def GetY(*args, **kwargs):
        """GetY(self) -> SVGAnimatedLength"""
        return _wxsvg.SVGSVGElement_GetY(*args, **kwargs)

    def SetY(*args):
        """
        SetY(self, SVGAnimatedLength n)
        SetY(self, SVGLength n)
        """
        return _wxsvg.SVGSVGElement_SetY(*args)

    def GetWidth(*args, **kwargs):
        """GetWidth(self) -> SVGAnimatedLength"""
        return _wxsvg.SVGSVGElement_GetWidth(*args, **kwargs)

    def SetWidth(*args):
        """
        SetWidth(self, SVGAnimatedLength n)
        SetWidth(self, SVGLength n)
        """
        return _wxsvg.SVGSVGElement_SetWidth(*args)

    def GetHeight(*args, **kwargs):
        """GetHeight(self) -> SVGAnimatedLength"""
        return _wxsvg.SVGSVGElement_GetHeight(*args, **kwargs)

    def SetHeight(*args):
        """
        SetHeight(self, SVGAnimatedLength n)
        SetHeight(self, SVGLength n)
        """
        return _wxsvg.SVGSVGElement_SetHeight(*args)

    def GetContentScriptType(*args, **kwargs):
        """GetContentScriptType(self) -> String"""
        return _wxsvg.SVGSVGElement_GetContentScriptType(*args, **kwargs)

    def SetContentScriptType(*args, **kwargs):
        """SetContentScriptType(self, String n)"""
        return _wxsvg.SVGSVGElement_SetContentScriptType(*args, **kwargs)

    def GetContentStyleType(*args, **kwargs):
        """GetContentStyleType(self) -> String"""
        return _wxsvg.SVGSVGElement_GetContentStyleType(*args, **kwargs)

    def SetContentStyleType(*args, **kwargs):
        """SetContentStyleType(self, String n)"""
        return _wxsvg.SVGSVGElement_SetContentStyleType(*args, **kwargs)

    def GetViewport(*args, **kwargs):
        """GetViewport(self) -> SVGRect"""
        return _wxsvg.SVGSVGElement_GetViewport(*args, **kwargs)

    def SetViewport(*args, **kwargs):
        """SetViewport(self, SVGRect n)"""
        return _wxsvg.SVGSVGElement_SetViewport(*args, **kwargs)

    def GetPixelUnitToMillimeterX(*args, **kwargs):
        """GetPixelUnitToMillimeterX(self) -> double"""
        return _wxsvg.SVGSVGElement_GetPixelUnitToMillimeterX(*args, **kwargs)

    def SetPixelUnitToMillimeterX(*args, **kwargs):
        """SetPixelUnitToMillimeterX(self, double n)"""
        return _wxsvg.SVGSVGElement_SetPixelUnitToMillimeterX(*args, **kwargs)

    def GetPixelUnitToMillimeterY(*args, **kwargs):
        """GetPixelUnitToMillimeterY(self) -> double"""
        return _wxsvg.SVGSVGElement_GetPixelUnitToMillimeterY(*args, **kwargs)

    def SetPixelUnitToMillimeterY(*args, **kwargs):
        """SetPixelUnitToMillimeterY(self, double n)"""
        return _wxsvg.SVGSVGElement_SetPixelUnitToMillimeterY(*args, **kwargs)

    def GetScreenPixelToMillimeterX(*args, **kwargs):
        """GetScreenPixelToMillimeterX(self) -> double"""
        return _wxsvg.SVGSVGElement_GetScreenPixelToMillimeterX(*args, **kwargs)

    def SetScreenPixelToMillimeterX(*args, **kwargs):
        """SetScreenPixelToMillimeterX(self, double n)"""
        return _wxsvg.SVGSVGElement_SetScreenPixelToMillimeterX(*args, **kwargs)

    def GetScreenPixelToMillimeterY(*args, **kwargs):
        """GetScreenPixelToMillimeterY(self) -> double"""
        return _wxsvg.SVGSVGElement_GetScreenPixelToMillimeterY(*args, **kwargs)

    def SetScreenPixelToMillimeterY(*args, **kwargs):
        """SetScreenPixelToMillimeterY(self, double n)"""
        return _wxsvg.SVGSVGElement_SetScreenPixelToMillimeterY(*args, **kwargs)

    def GetUseCurrentView(*args, **kwargs):
        """GetUseCurrentView(self) -> bool"""
        return _wxsvg.SVGSVGElement_GetUseCurrentView(*args, **kwargs)

    def SetUseCurrentView(*args, **kwargs):
        """SetUseCurrentView(self, bool n)"""
        return _wxsvg.SVGSVGElement_SetUseCurrentView(*args, **kwargs)

    def GetCurrentView(*args, **kwargs):
        """GetCurrentView(self) -> SVGViewSpec"""
        return _wxsvg.SVGSVGElement_GetCurrentView(*args, **kwargs)

    def SetCurrentView(*args, **kwargs):
        """SetCurrentView(self, SVGViewSpec n)"""
        return _wxsvg.SVGSVGElement_SetCurrentView(*args, **kwargs)

    def GetCurrentScale(*args, **kwargs):
        """GetCurrentScale(self) -> double"""
        return _wxsvg.SVGSVGElement_GetCurrentScale(*args, **kwargs)

    def SetCurrentScale(*args, **kwargs):
        """SetCurrentScale(self, double n)"""
        return _wxsvg.SVGSVGElement_SetCurrentScale(*args, **kwargs)

    def GetCurrentTranslate(*args, **kwargs):
        """GetCurrentTranslate(self) -> SVGPoint"""
        return _wxsvg.SVGSVGElement_GetCurrentTranslate(*args, **kwargs)

    def SetCurrentTranslate(*args, **kwargs):
        """SetCurrentTranslate(self, SVGPoint n)"""
        return _wxsvg.SVGSVGElement_SetCurrentTranslate(*args, **kwargs)

    def GetElementById(*args, **kwargs):
        """GetElementById(self, String elementId) -> SvgXmlElement"""
        return _wxsvg.SVGSVGElement_GetElementById(*args, **kwargs)

    def GetIntersectionList(*args, **kwargs):
        """GetIntersectionList(self, SVGRect rect, SVGElement referenceElement) -> wxNodeList"""
        return _wxsvg.SVGSVGElement_GetIntersectionList(*args, **kwargs)

    def GetEnclosureList(*args, **kwargs):
        """GetEnclosureList(self, SVGRect rect, SVGElement referenceElement) -> wxNodeList"""
        return _wxsvg.SVGSVGElement_GetEnclosureList(*args, **kwargs)

    def CheckIntersection(*args, **kwargs):
        """CheckIntersection(self, SVGElement element, SVGRect rect) -> bool"""
        return _wxsvg.SVGSVGElement_CheckIntersection(*args, **kwargs)

    def CheckEnclosure(*args, **kwargs):
        """CheckEnclosure(self, SVGElement element, SVGRect rect) -> bool"""
        return _wxsvg.SVGSVGElement_CheckEnclosure(*args, **kwargs)

    def HasAttribute(*args, **kwargs):
        """HasAttribute(self, String name) -> bool"""
        return _wxsvg.SVGSVGElement_HasAttribute(*args, **kwargs)

    def GetAttribute(*args, **kwargs):
        """GetAttribute(self, String name) -> String"""
        return _wxsvg.SVGSVGElement_GetAttribute(*args, **kwargs)

    def SetAttribute(*args, **kwargs):
        """SetAttribute(self, String name, String value) -> bool"""
        return _wxsvg.SVGSVGElement_SetAttribute(*args, **kwargs)

    def GetAttributes(*args, **kwargs):
        """GetAttributes(self) -> wxSvgXmlAttrHash"""
        return _wxsvg.SVGSVGElement_GetAttributes(*args, **kwargs)

    def GetDtd(*args, **kwargs):
        """GetDtd(self) -> wxSVGDTD"""
        return _wxsvg.SVGSVGElement_GetDtd(*args, **kwargs)

_wxsvg.SVGSVGElement_swigregister(SVGSVGElement)

class SVGCtrl(_core.Control):
    """Proxy of C++ SVGCtrl class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, Window parent, int id=ID_ANY, Point pos=DefaultPosition, 
            Size size=DefaultSize, long style=0, String name=SVGControlNameStr) -> SVGCtrl
        """
        _wxsvg.SVGCtrl_swiginit(self,_wxsvg.new_SVGCtrl(*args, **kwargs))
        self._setOORInfo(self)

    def SetFitToFrame(*args, **kwargs):
        """SetFitToFrame(self, bool fit=True)"""
        return _wxsvg.SVGCtrl_SetFitToFrame(*args, **kwargs)

    def GetScale(*args, **kwargs):
        """GetScale(self) -> double"""
        return _wxsvg.SVGCtrl_GetScale(*args, **kwargs)

    def GetSVG(*args, **kwargs):
        """GetSVG(self) -> SVGDocument"""
        return _wxsvg.SVGCtrl_GetSVG(*args, **kwargs)

    def Load(*args, **kwargs):
        """Load(self, String filename) -> bool"""
        return _wxsvg.SVGCtrl_Load(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _wxsvg.SVGCtrl_Clear(*args, **kwargs)

    def MoveElement(*args, **kwargs):
        """MoveElement(self, SVGElement elem, double Xposition, double Yposition)"""
        return _wxsvg.SVGCtrl_MoveElement(*args, **kwargs)

_wxsvg.SVGCtrl_swigregister(SVGCtrl)

def PreSVGCtrl(*args, **kwargs):
    """PreSVGCtrl() -> SVGCtrl"""
    val = _wxsvg.new_PreSVGCtrl(*args, **kwargs)
    return val

class SVGPoint(object):
    """Proxy of C++ SVGPoint class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def GetX(*args, **kwargs):
        """GetX(self) -> double"""
        return _wxsvg.SVGPoint_GetX(*args, **kwargs)

    def SetX(*args, **kwargs):
        """SetX(self, double n)"""
        return _wxsvg.SVGPoint_SetX(*args, **kwargs)

    def GetY(*args, **kwargs):
        """GetY(self) -> double"""
        return _wxsvg.SVGPoint_GetY(*args, **kwargs)

    def SetY(*args, **kwargs):
        """SetY(self, double n)"""
        return _wxsvg.SVGPoint_SetY(*args, **kwargs)

    def __init__(self, *args): 
        """
        __init__(self) -> SVGPoint
        __init__(self, double x, double y) -> SVGPoint
        """
        _wxsvg.SVGPoint_swiginit(self,_wxsvg.new_SVGPoint(*args))
    def MatrixTransform(*args, **kwargs):
        """MatrixTransform(self, wxSVGMatrix matrix) -> SVGPoint"""
        return _wxsvg.SVGPoint_MatrixTransform(*args, **kwargs)

_wxsvg.SVGPoint_swigregister(SVGPoint)

class SVGFitToViewBox(object):
    """Proxy of C++ SVGFitToViewBox class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetViewBox(*args, **kwargs):
        """GetViewBox(self) -> SVGAnimatedRect"""
        return _wxsvg.SVGFitToViewBox_GetViewBox(*args, **kwargs)

    def SetViewBox(*args):
        """
        SetViewBox(self, SVGAnimatedRect n)
        SetViewBox(self, SVGRect n)
        """
        return _wxsvg.SVGFitToViewBox_SetViewBox(*args)

    def GetPreserveAspectRatio(*args, **kwargs):
        """GetPreserveAspectRatio(self) -> wxSVGAnimatedPreserveAspectRatio"""
        return _wxsvg.SVGFitToViewBox_GetPreserveAspectRatio(*args, **kwargs)

    def SetPreserveAspectRatio(*args):
        """
        SetPreserveAspectRatio(self, wxSVGAnimatedPreserveAspectRatio n)
        SetPreserveAspectRatio(self, wxSVGPreserveAspectRatio n)
        """
        return _wxsvg.SVGFitToViewBox_SetPreserveAspectRatio(*args)

    def UpdateMatrix(*args, **kwargs):
        """UpdateMatrix(self, wxSVGMatrix matrix, SVGLength width, SVGLength height)"""
        return _wxsvg.SVGFitToViewBox_UpdateMatrix(*args, **kwargs)

    def HasAttribute(*args, **kwargs):
        """HasAttribute(self, String name) -> bool"""
        return _wxsvg.SVGFitToViewBox_HasAttribute(*args, **kwargs)

    def GetAttribute(*args, **kwargs):
        """GetAttribute(self, String name) -> String"""
        return _wxsvg.SVGFitToViewBox_GetAttribute(*args, **kwargs)

    def SetAttribute(*args, **kwargs):
        """SetAttribute(self, String name, String value) -> bool"""
        return _wxsvg.SVGFitToViewBox_SetAttribute(*args, **kwargs)

    def GetAttributes(*args, **kwargs):
        """GetAttributes(self) -> wxSvgXmlAttrHash"""
        return _wxsvg.SVGFitToViewBox_GetAttributes(*args, **kwargs)

_wxsvg.SVGFitToViewBox_swigregister(SVGFitToViewBox)

class SVGViewSpec(SVGFitToViewBox):
    """Proxy of C++ SVGViewSpec class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def GetTransform(*args, **kwargs):
        """GetTransform(self) -> wxSVGTransformList"""
        return _wxsvg.SVGViewSpec_GetTransform(*args, **kwargs)

    def SetTransform(*args, **kwargs):
        """SetTransform(self, wxSVGTransformList n)"""
        return _wxsvg.SVGViewSpec_SetTransform(*args, **kwargs)

    def GetViewTarget(*args, **kwargs):
        """GetViewTarget(self) -> SVGElement"""
        return _wxsvg.SVGViewSpec_GetViewTarget(*args, **kwargs)

    def SetViewTarget(*args, **kwargs):
        """SetViewTarget(self, SVGElement n)"""
        return _wxsvg.SVGViewSpec_SetViewTarget(*args, **kwargs)

    def GetViewBoxString(*args, **kwargs):
        """GetViewBoxString(self) -> String"""
        return _wxsvg.SVGViewSpec_GetViewBoxString(*args, **kwargs)

    def SetViewBoxString(*args, **kwargs):
        """SetViewBoxString(self, String n)"""
        return _wxsvg.SVGViewSpec_SetViewBoxString(*args, **kwargs)

    def GetPreserveAspectRatioString(*args, **kwargs):
        """GetPreserveAspectRatioString(self) -> String"""
        return _wxsvg.SVGViewSpec_GetPreserveAspectRatioString(*args, **kwargs)

    def SetPreserveAspectRatioString(*args, **kwargs):
        """SetPreserveAspectRatioString(self, String n)"""
        return _wxsvg.SVGViewSpec_SetPreserveAspectRatioString(*args, **kwargs)

    def GetTransformString(*args, **kwargs):
        """GetTransformString(self) -> String"""
        return _wxsvg.SVGViewSpec_GetTransformString(*args, **kwargs)

    def SetTransformString(*args, **kwargs):
        """SetTransformString(self, String n)"""
        return _wxsvg.SVGViewSpec_SetTransformString(*args, **kwargs)

    def GetViewTargetString(*args, **kwargs):
        """GetViewTargetString(self) -> String"""
        return _wxsvg.SVGViewSpec_GetViewTargetString(*args, **kwargs)

    def SetViewTargetString(*args, **kwargs):
        """SetViewTargetString(self, String n)"""
        return _wxsvg.SVGViewSpec_SetViewTargetString(*args, **kwargs)

    def __init__(self, *args, **kwargs): 
        """__init__(self) -> SVGViewSpec"""
        _wxsvg.SVGViewSpec_swiginit(self,_wxsvg.new_SVGViewSpec(*args, **kwargs))
    def HasAttribute(*args, **kwargs):
        """HasAttribute(self, String name) -> bool"""
        return _wxsvg.SVGViewSpec_HasAttribute(*args, **kwargs)

    def GetAttribute(*args, **kwargs):
        """GetAttribute(self, String name) -> String"""
        return _wxsvg.SVGViewSpec_GetAttribute(*args, **kwargs)

    def SetAttribute(*args, **kwargs):
        """SetAttribute(self, String name, String value) -> bool"""
        return _wxsvg.SVGViewSpec_SetAttribute(*args, **kwargs)

    def GetAttributes(*args, **kwargs):
        """GetAttributes(self) -> wxSvgXmlAttrHash"""
        return _wxsvg.SVGViewSpec_GetAttributes(*args, **kwargs)

_wxsvg.SVGViewSpec_swigregister(SVGViewSpec)

class SVGAnimatedRect(object):
    """Proxy of C++ SVGAnimatedRect class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """
        __init__(self) -> SVGAnimatedRect
        __init__(self, SVGRect value) -> SVGAnimatedRect
        __init__(self, SVGAnimatedRect value) -> SVGAnimatedRect
        """
        _wxsvg.SVGAnimatedRect_swiginit(self,_wxsvg.new_SVGAnimatedRect(*args))
        self._setOORInfo(self)

    def GetBaseVal(*args):
        """
        GetBaseVal(self) -> SVGRect
        GetBaseVal(self) -> SVGRect
        """
        return _wxsvg.SVGAnimatedRect_GetBaseVal(*args)

    def SetBaseVal(*args, **kwargs):
        """SetBaseVal(self, SVGRect value)"""
        return _wxsvg.SVGAnimatedRect_SetBaseVal(*args, **kwargs)

    def GetAnimVal(*args):
        """
        GetAnimVal(self) -> SVGRect
        GetAnimVal(self) -> SVGRect
        """
        return _wxsvg.SVGAnimatedRect_GetAnimVal(*args)

    def SetAnimVal(*args, **kwargs):
        """SetAnimVal(self, SVGRect value)"""
        return _wxsvg.SVGAnimatedRect_SetAnimVal(*args, **kwargs)

    def ResetAnimVal(*args, **kwargs):
        """ResetAnimVal(self)"""
        return _wxsvg.SVGAnimatedRect_ResetAnimVal(*args, **kwargs)

_wxsvg.SVGAnimatedRect_swigregister(SVGAnimatedRect)

class SVGAnimatedLength(object):
    """Proxy of C++ SVGAnimatedLength class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """
        __init__(self) -> SVGAnimatedLength
        __init__(self, SVGLength value) -> SVGAnimatedLength
        __init__(self, SVGAnimatedLength value) -> SVGAnimatedLength
        """
        _wxsvg.SVGAnimatedLength_swiginit(self,_wxsvg.new_SVGAnimatedLength(*args))
        self._setOORInfo(self)

    def GetBaseVal(*args):
        """
        GetBaseVal(self) -> SVGLength
        GetBaseVal(self) -> SVGLength
        """
        return _wxsvg.SVGAnimatedLength_GetBaseVal(*args)

    def SetBaseVal(*args, **kwargs):
        """SetBaseVal(self, SVGLength value)"""
        return _wxsvg.SVGAnimatedLength_SetBaseVal(*args, **kwargs)

    def GetAnimVal(*args):
        """
        GetAnimVal(self) -> SVGLength
        GetAnimVal(self) -> SVGLength
        """
        return _wxsvg.SVGAnimatedLength_GetAnimVal(*args)

    def SetAnimVal(*args, **kwargs):
        """SetAnimVal(self, SVGLength value)"""
        return _wxsvg.SVGAnimatedLength_SetAnimVal(*args, **kwargs)

    def ResetAnimVal(*args, **kwargs):
        """ResetAnimVal(self)"""
        return _wxsvg.SVGAnimatedLength_ResetAnimVal(*args, **kwargs)

_wxsvg.SVGAnimatedLength_swigregister(SVGAnimatedLength)

class SVGLength(object):
    """Proxy of C++ SVGLength class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def GetUnitType(*args, **kwargs):
        """GetUnitType(self) -> wxSVG_LENGTHTYPE"""
        return _wxsvg.SVGLength_GetUnitType(*args, **kwargs)

    def SetUnitType(*args, **kwargs):
        """SetUnitType(self, wxSVG_LENGTHTYPE n)"""
        return _wxsvg.SVGLength_SetUnitType(*args, **kwargs)

    def __init__(self, *args): 
        """
        __init__(self) -> SVGLength
        __init__(self, double v) -> SVGLength
        __init__(self, wxSVG_LENGTHTYPE unitType, double v) -> SVGLength
        __init__(self, SVGLength l) -> SVGLength
        """
        _wxsvg.SVGLength_swiginit(self,_wxsvg.new_SVGLength(*args))
    def GetValue(*args, **kwargs):
        """GetValue(self) -> double"""
        return _wxsvg.SVGLength_GetValue(*args, **kwargs)

    def SetValue(*args, **kwargs):
        """SetValue(self, double n)"""
        return _wxsvg.SVGLength_SetValue(*args, **kwargs)

    def GetValueInSpecifiedUnits(*args, **kwargs):
        """GetValueInSpecifiedUnits(self) -> double"""
        return _wxsvg.SVGLength_GetValueInSpecifiedUnits(*args, **kwargs)

    def SetValueInSpecifiedUnits(*args, **kwargs):
        """SetValueInSpecifiedUnits(self, double n)"""
        return _wxsvg.SVGLength_SetValueInSpecifiedUnits(*args, **kwargs)

    def GetValueAsString(*args, **kwargs):
        """GetValueAsString(self) -> String"""
        return _wxsvg.SVGLength_GetValueAsString(*args, **kwargs)

    def SetValueAsString(*args, **kwargs):
        """SetValueAsString(self, String n)"""
        return _wxsvg.SVGLength_SetValueAsString(*args, **kwargs)

    def ToViewportWidth(*args, **kwargs):
        """ToViewportWidth(self, float viewportWidth)"""
        return _wxsvg.SVGLength_ToViewportWidth(*args, **kwargs)

    def ToViewportHeight(*args, **kwargs):
        """ToViewportHeight(self, float viewportHeight)"""
        return _wxsvg.SVGLength_ToViewportHeight(*args, **kwargs)

    def ToViewportSize(*args, **kwargs):
        """ToViewportSize(self, float viewportWidth, float viewportHeight)"""
        return _wxsvg.SVGLength_ToViewportSize(*args, **kwargs)

    def NewValueSpecifiedUnits(*args, **kwargs):
        """NewValueSpecifiedUnits(self, wxSVG_LENGTHTYPE unitType, double valueInSpecifiedUnits)"""
        return _wxsvg.SVGLength_NewValueSpecifiedUnits(*args, **kwargs)

    def ConvertToSpecifiedUnits(*args, **kwargs):
        """ConvertToSpecifiedUnits(self, wxSVG_LENGTHTYPE unitType)"""
        return _wxsvg.SVGLength_ConvertToSpecifiedUnits(*args, **kwargs)

_wxsvg.SVGLength_swigregister(SVGLength)

class SVGUIElement(SvgXmlNode):
    """Proxy of C++ SVGUIElement class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _wxsvg.delete_SVGUIElement
    __del__ = lambda self : None;
    def GetId(*args, **kwargs):
        """GetId(self) -> String"""
        return _wxsvg.SVGUIElement_GetId(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _wxsvg.SVGUIElement_GetName(*args, **kwargs)

    def Initialize(*args, **kwargs):
        """Initialize(self)"""
        return _wxsvg.SVGUIElement_Initialize(*args, **kwargs)

    def HitTest(*args, **kwargs):
        """HitTest(self, Point pt) -> bool"""
        return _wxsvg.SVGUIElement_HitTest(*args, **kwargs)

    def GetBBox(*args, **kwargs):
        """GetBBox(self) -> SVGRect"""
        return _wxsvg.SVGUIElement_GetBBox(*args, **kwargs)

    def Update_Elements(*args, **kwargs):
        """Update_Elements(self)"""
        return _wxsvg.SVGUIElement_Update_Elements(*args, **kwargs)

    def SetSelected(*args, **kwargs):
        """SetSelected(self, bool selected)"""
        return _wxsvg.SVGUIElement_SetSelected(*args, **kwargs)

    def IsVisible(*args, **kwargs):
        """IsVisible(self) -> bool"""
        return _wxsvg.SVGUIElement_IsVisible(*args, **kwargs)

    def IsEnabled(*args, **kwargs):
        """IsEnabled(self) -> bool"""
        return _wxsvg.SVGUIElement_IsEnabled(*args, **kwargs)

    def Hide(*args, **kwargs):
        """Hide(self)"""
        return _wxsvg.SVGUIElement_Hide(*args, **kwargs)

    def Show(*args, **kwargs):
        """Show(self)"""
        return _wxsvg.SVGUIElement_Show(*args, **kwargs)

    def Enable(*args, **kwargs):
        """Enable(self)"""
        return _wxsvg.SVGUIElement_Enable(*args, **kwargs)

    def Disable(*args, **kwargs):
        """Disable(self)"""
        return _wxsvg.SVGUIElement_Disable(*args, **kwargs)

_wxsvg.SVGUIElement_swigregister(SVGUIElement)

class SVGUIControl(SVGUIElement):
    """Proxy of C++ SVGUIControl class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _wxsvg.delete_SVGUIControl
    __del__ = lambda self : None;
    def Refresh(*args, **kwargs):
        """Refresh(self)"""
        return _wxsvg.SVGUIControl_Refresh(*args, **kwargs)

    def OnLeftDown(*args, **kwargs):
        """OnLeftDown(self, MouseEvent event)"""
        return _wxsvg.SVGUIControl_OnLeftDown(*args, **kwargs)

    def OnLeftUp(*args, **kwargs):
        """OnLeftUp(self, MouseEvent event)"""
        return _wxsvg.SVGUIControl_OnLeftUp(*args, **kwargs)

    def OnMotion(*args, **kwargs):
        """OnMotion(self, MouseEvent event)"""
        return _wxsvg.SVGUIControl_OnMotion(*args, **kwargs)

    def OnChar(*args, **kwargs):
        """OnChar(self, KeyEvent event)"""
        return _wxsvg.SVGUIControl_OnChar(*args, **kwargs)

_wxsvg.SVGUIControl_swigregister(SVGUIControl)

class SVGUIContainer(SVGUIElement):
    """Proxy of C++ SVGUIContainer class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """
        __init__(self) -> SVGUIContainer
        __init__(self, SVGDocument doc) -> SVGUIContainer
        """
        _wxsvg.SVGUIContainer_swiginit(self,_wxsvg.new_SVGUIContainer(*args))
    __swig_destroy__ = _wxsvg.delete_SVGUIContainer
    __del__ = lambda self : None;
    def GetFocusedElement(*args, **kwargs):
        """GetFocusedElement(self) -> String"""
        return _wxsvg.SVGUIContainer_GetFocusedElement(*args, **kwargs)

    def GetFocusedElementName(*args, **kwargs):
        """GetFocusedElementName(self) -> String"""
        return _wxsvg.SVGUIContainer_GetFocusedElementName(*args, **kwargs)

    def Hide(*args, **kwargs):
        """Hide(self)"""
        return _wxsvg.SVGUIContainer_Hide(*args, **kwargs)

    def Show(*args, **kwargs):
        """Show(self)"""
        return _wxsvg.SVGUIContainer_Show(*args, **kwargs)

    def Enable(*args, **kwargs):
        """Enable(self)"""
        return _wxsvg.SVGUIContainer_Enable(*args, **kwargs)

    def Disable(*args, **kwargs):
        """Disable(self)"""
        return _wxsvg.SVGUIContainer_Disable(*args, **kwargs)

    def OnLeftDown(*args, **kwargs):
        """OnLeftDown(self, MouseEvent event)"""
        return _wxsvg.SVGUIContainer_OnLeftDown(*args, **kwargs)

    def OnLeftUp(*args, **kwargs):
        """OnLeftUp(self, MouseEvent event)"""
        return _wxsvg.SVGUIContainer_OnLeftUp(*args, **kwargs)

    def OnMotion(*args, **kwargs):
        """OnMotion(self, MouseEvent event)"""
        return _wxsvg.SVGUIContainer_OnMotion(*args, **kwargs)

    def OnChar(*args, **kwargs):
        """OnChar(self, KeyEvent event)"""
        return _wxsvg.SVGUIContainer_OnChar(*args, **kwargs)

_wxsvg.SVGUIContainer_swigregister(SVGUIContainer)

class SVGUIScrollBar(SVGUIControl):
    """Proxy of C++ SVGUIScrollBar class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc, EvtHandler window) -> SVGUIScrollBar"""
        _wxsvg.SVGUIScrollBar_swiginit(self,_wxsvg.new_SVGUIScrollBar(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUIScrollBar
    __del__ = lambda self : None;
    def Init_ScrollBar(*args, **kwargs):
        """Init_ScrollBar(self, unsigned int position, unsigned int thumb, unsigned int range)"""
        return _wxsvg.SVGUIScrollBar_Init_ScrollBar(*args, **kwargs)

    def GetThumbPosition(*args, **kwargs):
        """GetThumbPosition(self) -> unsigned int"""
        return _wxsvg.SVGUIScrollBar_GetThumbPosition(*args, **kwargs)

    def GetThumbSize(*args, **kwargs):
        """GetThumbSize(self) -> unsigned int"""
        return _wxsvg.SVGUIScrollBar_GetThumbSize(*args, **kwargs)

    def GetRange(*args, **kwargs):
        """GetRange(self) -> unsigned int"""
        return _wxsvg.SVGUIScrollBar_GetRange(*args, **kwargs)

    def MoveThumbByUnit(*args, **kwargs):
        """MoveThumbByUnit(self, int direction)"""
        return _wxsvg.SVGUIScrollBar_MoveThumbByUnit(*args, **kwargs)

    def MoveThumbByPage(*args, **kwargs):
        """MoveThumbByPage(self, int direction)"""
        return _wxsvg.SVGUIScrollBar_MoveThumbByPage(*args, **kwargs)

_wxsvg.SVGUIScrollBar_swigregister(SVGUIScrollBar)

class SVGUINoteBookContent(SVGUIContainer):
    """Proxy of C++ SVGUINoteBookContent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc) -> SVGUINoteBookContent"""
        _wxsvg.SVGUINoteBookContent_swiginit(self,_wxsvg.new_SVGUINoteBookContent(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUINoteBookContent
    __del__ = lambda self : None;
    def GetTabElement(*args, **kwargs):
        """GetTabElement(self) -> SVGElement"""
        return _wxsvg.SVGUINoteBookContent_GetTabElement(*args, **kwargs)

    def GetContentElement(*args, **kwargs):
        """GetContentElement(self) -> SVGElement"""
        return _wxsvg.SVGUINoteBookContent_GetContentElement(*args, **kwargs)

_wxsvg.SVGUINoteBookContent_swigregister(SVGUINoteBookContent)

class SVGUINoteBook(SVGUIControl):
    """Proxy of C++ SVGUINoteBook class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc, EvtHandler window) -> SVGUINoteBook"""
        _wxsvg.SVGUINoteBook_swiginit(self,_wxsvg.new_SVGUINoteBook(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUINoteBook
    __del__ = lambda self : None;
    def GetCurrentPage(*args, **kwargs):
        """GetCurrentPage(self) -> unsigned int"""
        return _wxsvg.SVGUINoteBook_GetCurrentPage(*args, **kwargs)

    def SetCurrentPage(*args, **kwargs):
        """SetCurrentPage(self, int page)"""
        return _wxsvg.SVGUINoteBook_SetCurrentPage(*args, **kwargs)

_wxsvg.SVGUINoteBook_swigregister(SVGUINoteBook)

class SVGUIRotatingCtrl(SVGUIControl):
    """Proxy of C++ SVGUIRotatingCtrl class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc, EvtHandler window) -> SVGUIRotatingCtrl"""
        _wxsvg.SVGUIRotatingCtrl_swiginit(self,_wxsvg.new_SVGUIRotatingCtrl(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUIRotatingCtrl
    __del__ = lambda self : None;
    def GetAngle(*args, **kwargs):
        """GetAngle(self) -> double"""
        return _wxsvg.SVGUIRotatingCtrl_GetAngle(*args, **kwargs)

    def GetMinAngle(*args, **kwargs):
        """GetMinAngle(self) -> double"""
        return _wxsvg.SVGUIRotatingCtrl_GetMinAngle(*args, **kwargs)

    def GetMaxAngle(*args, **kwargs):
        """GetMaxAngle(self) -> double"""
        return _wxsvg.SVGUIRotatingCtrl_GetMaxAngle(*args, **kwargs)

    def SetAngle(*args, **kwargs):
        """SetAngle(self, double angle)"""
        return _wxsvg.SVGUIRotatingCtrl_SetAngle(*args, **kwargs)

    def DefineCenter(*args, **kwargs):
        """DefineCenter(self, SVGPoint center)"""
        return _wxsvg.SVGUIRotatingCtrl_DefineCenter(*args, **kwargs)

    def GetCenter(*args, **kwargs):
        """GetCenter(self) -> SVGPoint"""
        return _wxsvg.SVGUIRotatingCtrl_GetCenter(*args, **kwargs)

    def DefineLimits(*args, **kwargs):
        """DefineLimits(self, double min_angle, double max_angle)"""
        return _wxsvg.SVGUIRotatingCtrl_DefineLimits(*args, **kwargs)

    def Rotate(*args, **kwargs):
        """Rotate(self, double angle)"""
        return _wxsvg.SVGUIRotatingCtrl_Rotate(*args, **kwargs)

_wxsvg.SVGUIRotatingCtrl_swigregister(SVGUIRotatingCtrl)

class SVGUIButton(SVGUIControl):
    """Proxy of C++ SVGUIButton class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc, EvtHandler window) -> SVGUIButton"""
        _wxsvg.SVGUIButton_swiginit(self,_wxsvg.new_SVGUIButton(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUIButton
    __del__ = lambda self : None;
_wxsvg.SVGUIButton_swigregister(SVGUIButton)

class SVGUITextCtrl(SVGUIControl):
    """Proxy of C++ SVGUITextCtrl class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc, EvtHandler window) -> SVGUITextCtrl"""
        _wxsvg.SVGUITextCtrl_swiginit(self,_wxsvg.new_SVGUITextCtrl(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUITextCtrl
    __del__ = lambda self : None;
    def HitTest(*args, **kwargs):
        """HitTest(self, Point pt) -> bool"""
        return _wxsvg.SVGUITextCtrl_HitTest(*args, **kwargs)

    def GetValue(*args, **kwargs):
        """GetValue(self) -> String"""
        return _wxsvg.SVGUITextCtrl_GetValue(*args, **kwargs)

    def SetValue(*args, **kwargs):
        """SetValue(self, String value)"""
        return _wxsvg.SVGUITextCtrl_SetValue(*args, **kwargs)

    def SetStyle(*args, **kwargs):
        """SetStyle(self, long style)"""
        return _wxsvg.SVGUITextCtrl_SetStyle(*args, **kwargs)

    def GetStyle(*args, **kwargs):
        """GetStyle(self) -> long"""
        return _wxsvg.SVGUITextCtrl_GetStyle(*args, **kwargs)

    def SetSelected(*args, **kwargs):
        """SetSelected(self, bool selected)"""
        return _wxsvg.SVGUITextCtrl_SetSelected(*args, **kwargs)

    def AddCharInText(*args, **kwargs):
        """AddCharInText(self, String character)"""
        return _wxsvg.SVGUITextCtrl_AddCharInText(*args, **kwargs)

    def DelCharInText(*args, **kwargs):
        """DelCharInText(self, bool backward=False)"""
        return _wxsvg.SVGUITextCtrl_DelCharInText(*args, **kwargs)

    def MoveCursor(*args, **kwargs):
        """MoveCursor(self, int direction)"""
        return _wxsvg.SVGUITextCtrl_MoveCursor(*args, **kwargs)

    def FindCursorIndex(*args, **kwargs):
        """FindCursorIndex(self, SVGPoint point)"""
        return _wxsvg.SVGUITextCtrl_FindCursorIndex(*args, **kwargs)

_wxsvg.SVGUITextCtrl_swigregister(SVGUITextCtrl)

class SVGUITransform(SVGUIControl):
    """Proxy of C++ SVGUITransform class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, SVGDocument doc, EvtHandler window) -> SVGUITransform"""
        _wxsvg.SVGUITransform_swiginit(self,_wxsvg.new_SVGUITransform(*args, **kwargs))
        self._setOORInfo(self)

    __swig_destroy__ = _wxsvg.delete_SVGUITransform
    __del__ = lambda self : None;
    def GetX(*args, **kwargs):
        """GetX(self) -> double"""
        return _wxsvg.SVGUITransform_GetX(*args, **kwargs)

    def GetY(*args, **kwargs):
        """GetY(self) -> double"""
        return _wxsvg.SVGUITransform_GetY(*args, **kwargs)

    def GetXScale(*args, **kwargs):
        """GetXScale(self) -> double"""
        return _wxsvg.SVGUITransform_GetXScale(*args, **kwargs)

    def GetYScale(*args, **kwargs):
        """GetYScale(self) -> double"""
        return _wxsvg.SVGUITransform_GetYScale(*args, **kwargs)

    def GetAngle(*args, **kwargs):
        """GetAngle(self) -> double"""
        return _wxsvg.SVGUITransform_GetAngle(*args, **kwargs)

    def Move(*args, **kwargs):
        """Move(self, double x, double y)"""
        return _wxsvg.SVGUITransform_Move(*args, **kwargs)

    def Scale(*args, **kwargs):
        """Scale(self, double x, double y)"""
        return _wxsvg.SVGUITransform_Scale(*args, **kwargs)

    def Rotate(*args, **kwargs):
        """Rotate(self, double angle)"""
        return _wxsvg.SVGUITransform_Rotate(*args, **kwargs)

_wxsvg.SVGUITransform_swigregister(SVGUITransform)

class SVGUIWindow(SvgXmlDocument,SVGCtrl):
    """Proxy of C++ SVGUIWindow class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, Window parent, int id=ID_ANY, Point pos=DefaultPosition, 
            Size size=DefaultSize, long style=0, String name=wxPanelNameStr) -> SVGUIWindow
        """
        _wxsvg.SVGUIWindow_swiginit(self,_wxsvg.new_SVGUIWindow(*args, **kwargs))
        self._setOORInfo(self)

    def CreateElement(*args, **kwargs):
        """CreateElement(self, String tagName) -> SVGUIElement"""
        return _wxsvg.SVGUIWindow_CreateElement(*args, **kwargs)

    def CreateElementNS(*args, **kwargs):
        """CreateElementNS(self, String namespaceURI, String qualifiedName) -> SVGUIElement"""
        return _wxsvg.SVGUIWindow_CreateElementNS(*args, **kwargs)

    def CreateWindow(*args, **kwargs):
        """CreateWindow(self, String classname) -> Window"""
        return _wxsvg.SVGUIWindow_CreateWindow(*args, **kwargs)

    def LoadFiles(*args, **kwargs):
        """LoadFiles(self, String svgfile, String deffile) -> bool"""
        return _wxsvg.SVGUIWindow_LoadFiles(*args, **kwargs)

    def Update_Elements(*args, **kwargs):
        """Update_Elements(self)"""
        return _wxsvg.SVGUIWindow_Update_Elements(*args, **kwargs)

    def GetSVGUIRootElement(*args, **kwargs):
        """GetSVGUIRootElement(self) -> SVGUIContainer"""
        return _wxsvg.SVGUIWindow_GetSVGUIRootElement(*args, **kwargs)

    def GetElementById(*args, **kwargs):
        """GetElementById(self, String id) -> SVGUIElement"""
        return _wxsvg.SVGUIWindow_GetElementById(*args, **kwargs)

    def GetScrollBarById(*args, **kwargs):
        """GetScrollBarById(self, String id) -> SVGUIScrollBar"""
        return _wxsvg.SVGUIWindow_GetScrollBarById(*args, **kwargs)

    def OnLeftDown(*args, **kwargs):
        """OnLeftDown(self, MouseEvent event)"""
        return _wxsvg.SVGUIWindow_OnLeftDown(*args, **kwargs)

    def OnLeftUp(*args, **kwargs):
        """OnLeftUp(self, MouseEvent event)"""
        return _wxsvg.SVGUIWindow_OnLeftUp(*args, **kwargs)

    def OnMotion(*args, **kwargs):
        """OnMotion(self, MouseEvent event)"""
        return _wxsvg.SVGUIWindow_OnMotion(*args, **kwargs)

    def OnChar(*args, **kwargs):
        """OnChar(self, KeyEvent event)"""
        return _wxsvg.SVGUIWindow_OnChar(*args, **kwargs)

    def OnRefresh(*args, **kwargs):
        """OnRefresh(self, CommandEvent event)"""
        return _wxsvg.SVGUIWindow_OnRefresh(*args, **kwargs)

_wxsvg.SVGUIWindow_swigregister(SVGUIWindow)



