/////////////////////////////////////////////////////////////////////////////
// Name:        wxsvg.i
// Purpose:     Wrappers for the WXSVG classes
//
// Author:      Jonathan Hurtrel
//
// Created:     24-May-2007
// RCS-ID:      $Id: wxsvg.i,v 1.18 2008/07/02 14:28:05 etisserant Exp $
// Copyright:   (c) Jonathan Hurtrel
// Licence:     wxWindows license
///////////////////////////////////////////////////////////////////////////

%define DOCSTRING
"wxSVG wrapper
"
%enddef

%module(package="wx", docstring=DOCSTRING) wxsvg

%{
#include "wxSVGXML/svgxml.h"
#include "wx/wxPython/wxPython.h"
#include "wx/wxPython/pyclasses.h"
#include "wx/dynarray.h"
#include "wxSVG/svgctrl.h"
#include "wxSVG/SVGElement.h"
#include "wxSVG/SVGSVGElement.h"
#include "wxSVG/NodeListCls.h"
#include "wxSVG/SVGLocatable.h"

#include "wxSVG/ElementTransform.h"
//#include "ElementTransform.cpp"
#include "wxSVG/SVGUIID.h"
//#include "SVGUIID.cpp"
#include "wxSVG/SVGUIElement.h"
//#include "SVGUIElement.cpp"
#include "wxSVG/SVGUIControl.h"
//#include "SVGUIControl.cpp"
#include "wxSVG/SVGUIScrollBar.h"
//#include "SVGUIScrollBar.cpp"
#include "wxSVG/SVGUINoteBook.h"
//#include "SVGUINoteBook.cpp"
#include "wxSVG/SVGUINoteBookContent.h"
//#include "SVGUINoteBookContent.cpp"
#include "wxSVG/SVGUIRotatingCtrl.h"
//#include "SVGUIRotatingCtrl.cpp"
#include "wxSVG/SVGUIButton.h"
//#include "SVGUIButton.cpp"
#include "wxSVG/SVGUITextCtrl.h"
//#include "SVGUITextCtrl.cpp"
#include "wxSVG/SVGUIContainer.h"
//#include "SVGUIContainer.cpp"
#include "wxSVG/SVGUIWindow.h"
//#include "SVGUIWindow.cpp"
#include "wxSVG/SVGUITransform.h"
//#include "SVGUITransform.cpp"

%}

//---------------------------------------------------------------------------

%import core.i
%pythoncode { import wx }
%pythoncode { __docfilter__ = wx._core.__DocFilter(globals()) }

MAKE_CONST_WXSTRING2(SVGControlNameStr,     wxT("SVGControl"));
MAKE_CONST_WXSTRING_NOSWIG(EmptyString);

%include _wxsvg_rename.i


enum wxSVG_COORDINATES
{
  wxSVG_COORDINATES_USER = 0,
  wxSVG_COORDINATES_VIEWPORT = 1,
  wxSVG_COORDINATES_SCREEN = 2
};

//---------------------------------------------------------------------------
//****************************    wxSvgXmlNode  *****************************
//---------------------------------------------------------------------------
MustHaveApp(wxSvgXmlNode);
class wxSvgXmlNode
{
public:
		%pythonAppend wxSvgXmlNode         "self._setOORInfo(self)"
    %pythonAppend wxSvgXmlNode()       ""
    
    wxSvgXmlNode() : m_properties(NULL), m_parent(NULL),
                  m_children(NULL), m_next(NULL), m_ownerDocument(NULL) {}
    wxSvgXmlNode(wxSvgXmlNode* parent, wxSvgXmlNodeType type,
              const wxString& name, const wxString& content,
              wxSvgXmlProperty* props, wxSvgXmlNode *next);

    // copy ctor & operator=. Note that this does NOT copy syblings
    // and parent pointer, i.e. m_parent and m_next will be NULL
    // after using copy ctor and are never unmodified by operator=.
    // On the other hand, it DOES copy children and properties.
    wxSvgXmlNode(const wxSvgXmlNode& node);
	virtual wxSvgXmlNode* CloneNode(bool deep = true) { return new wxSvgXmlNode(*this); }

    // user-friendly creation:
    wxSvgXmlNode(wxSvgXmlNodeType type, const wxString& name,
              const wxString& content = wxEmptyString);
              
    %RenameCtor(PreSvgXmlNode, wxSvgXmlNode());
	
    void AddChild(wxSvgXmlNode* child);
	inline wxSvgXmlNode* AppendChild(wxSvgXmlNode* child)
	{ AddChild(child); return child; }
	
    void InsertChild(wxSvgXmlNode *child, wxSvgXmlNode *before_node);
	inline wxSvgXmlNode* InsertBefore(wxSvgXmlNode *newChild, wxSvgXmlNode *refChild)
	{ InsertChild(newChild, refChild); return newChild; }
	
    bool RemoveChild(wxSvgXmlNode *child);
	
    virtual void AddProperty(const wxString& name, const wxString& value);
    virtual bool DeleteProperty(const wxString& name);

    // access methods:
    //wxSvgXmlNodeType GetType() const { return m_type; }
    wxString GetName() const { return m_name; }
    wxString GetContent() const { return m_content; }

    wxSvgXmlDocument *GetOwnerDocument() const { return m_ownerDocument; }
    wxSvgXmlNode *GetParent() const { return m_parent; }
    wxSvgXmlNode *GetNext() const { return m_next; }
    wxSvgXmlNode *GetChildren() const { return m_children; }
    
    wxSvgXmlNode* GetParentNode() const { return m_parent; }
    wxSvgXmlNode* GetChildNodes() const { return m_children; }
    wxSvgXmlNode* GetFirstChild() const { return m_children; }
    wxSvgXmlNode* GetLastChild() const;
    wxSvgXmlNode* GetPreviousSibling() const;
    wxSvgXmlNode* GetNextSibling() const { return m_next; }

    wxSvgXmlProperty *GetProperties() const { return m_properties; }
    //bool GetPropVal(const wxString& propName, wxString *value) const;
    wxString GetPropVal(const wxString& propName,
                        const wxString& defaultVal) const;
    bool HasProp(const wxString& propName) const;

    void SetType(wxSvgXmlNodeType type) { m_type = type; }
    void SetName(const wxString& name) { m_name = name; }
    void SetContent(const wxString& con) { m_content = con; }

    void SetParent(wxSvgXmlNode *parent) { m_parent = parent; }
    void SetNext(wxSvgXmlNode *next) { m_next = next; }
    void SetChildren(wxSvgXmlNode *child) { m_children = child; }

    void SetProperties(wxSvgXmlProperty *prop) { m_properties = prop; }
    void AddProperty(wxSvgXmlProperty *prop);

public: // W3C DOM Methods
	virtual wxString GetAttribute(const wxString& name);
	virtual wxString GetAttributeNS(const wxString& namespaceURI, 
									const wxString& localName);
    virtual bool SetAttribute(const wxString& name, const wxString& value);
	virtual bool SetAttributeNS(const wxString& namespaceURI, 
								const wxString& qualifiedName, 
								const wxString& value);
    virtual void RemoveAttribute(const wxString& name);
    virtual void RemoveAttributeNS(const wxString& namespaceURI, 
								 const wxString& localName);
    virtual bool HasAttribute(const wxString& name);
    virtual bool HasAttributeNS(const wxString& namespaceURI, 
								const wxString& localName);
                                
    void SetOwnerDocument(wxSvgXmlDocument* ownerDocument);

};

//---------------------------------------------------------------------------
//***********************    wxSvgXmlDocument  ******************************
//---------------------------------------------------------------------------


class wxSvgXmlDocument
{
public:
		%pythonAppend wxSvgXmlDocument         "self._setOORInfo(self)"
    %pythonAppend wxSvgXmlDocument()				""
    
    wxSvgXmlDocument();
    wxSvgXmlDocument(const wxString& filename,
                  const wxString& encoding = wxT("UTF-8"));
             
    %RenameCtor(PreSvgXmlDocument, wxSvgXmlDocument());
    
    

    // Parses .xml file and loads data. Returns TRUE on success, FALSE
    // otherwise.
    bool Load(const wxString& filename,
              const wxString& encoding = wxT("UTF-8"));
    
    // Saves document as .xml file.
    bool Save(const wxString& filename) const;

    bool IsOk() const { return m_root != NULL; }

    // Returns root node of the document.
    wxSvgXmlNode *GetRoot() const { return m_root; }

    // Returns version of document (may be empty).
    wxString GetVersion() const { return m_version; }
    // Returns encoding of document (may be empty).
    // Note: this is the encoding original file was saved in, *not* the
    // encoding of in-memory representation!
    wxString GetFileEncoding() const { return m_fileEncoding; }

    // Write-access methods:
    void SetRoot(wxSvgXmlNode *node);
    void SetVersion(const wxString& version) { m_version = version; }
    void SetFileEncoding(const wxString& encoding) { m_fileEncoding = encoding; }

#ifndef wxUSE_UNICODE
    // Returns encoding of in-memory representation of the document
    // (same as passed to Load or ctor, defaults to UTF-8).
    // NB: this is meaningless in Unicode build where data are stored as wchar_t*
    wxString GetEncoding() const { return m_encoding; }
    void SetEncoding(const wxString& enc) { m_encoding = enc; }
#endif

public: // W3C DOM Methods
	virtual wxSvgXmlElement* CreateElement(const wxString& tagName);
	virtual wxSvgXmlElement* CreateElementNS(const wxString& namespaceURI,
										  const wxString& qualifiedName);
										  
	inline wxSvgXmlNode* AppendChild(wxSvgXmlNode* child)
	{ if (!m_root) SetRoot(child); return child; }
	inline wxSvgXmlNode* RemoveChild(wxSvgXmlNode* child)
	{ if (m_root != child) return NULL; m_root = NULL; return child; }
	
	inline wxSvgXmlNode* GetFirstChild() { return m_root; }

private:
    wxString   m_version;
    wxString   m_fileEncoding;
#ifndef wxUSE_UNICODE
    wxString   m_encoding;
#endif
    wxSvgXmlNode *m_root;

    void DoCopy(const wxSvgXmlDocument& doc);
};


typedef wxSvgXmlNode wxSvgXmlElement;



//---------------------------------------------------------------------------
//****************************    wxSVGLocatable  ***************************
//---------------------------------------------------------------------------


class wxSVGLocatable
{
  protected:
    wxSVGElement* m_nearestViewportElement;
    wxSVGElement* m_farthestViewportElement;

  public:
    inline wxSVGElement* GetNearestViewportElement() const { return m_nearestViewportElement; }
    inline void SetNearestViewportElement(wxSVGElement* n) { m_nearestViewportElement = n; }

    inline wxSVGElement* GetFarthestViewportElement() const { return m_farthestViewportElement; }
    inline void SetFarthestViewportElement(wxSVGElement* n) { m_farthestViewportElement = n; }

  public:
  	%pythonAppend wxSVGLocatable         "self._setOORInfo(self)"
  	%pythonAppend wxSVGLocatable()       ""
    wxSVGLocatable(): m_nearestViewportElement(NULL), m_farthestViewportElement(NULL) {}
    
    virtual wxSVGRect GetBBox(wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER) = 0;
    virtual wxSVGRect GetResultBBox(wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER) = 0;
    virtual wxSVGMatrix GetCTM() = 0;
    virtual wxSVGMatrix GetScreenCTM() = 0;
    static wxSVGRect GetElementBBox(const wxSVGElement* element, wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER);
    static wxSVGRect GetElementResultBBox(const wxSVGElement* element, wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER);
    static wxSVGMatrix GetCTM(const wxSVGElement* element);
    static wxSVGMatrix GetScreenCTM(const wxSVGElement* element);
    virtual wxSVGMatrix GetTransformToElement(const wxSVGElement& element);

  protected:
    static wxSVGRect GetChildrenBBox(const wxSVGElement* element, wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER);
    static wxSVGRect GetChildrenResultBBox(const wxSVGElement* element, wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER);
    inline wxSVGMatrix GetMatrix(wxSVG_COORDINATES coordinates)
    { return coordinates == wxSVG_COORDINATES_SCREEN ? GetScreenCTM() : (coordinates == wxSVG_COORDINATES_VIEWPORT ? GetCTM() : wxSVGMatrix()); }
};


//---------------------------------------------------------------------------
//****************************    wxSVGElement  ****************************
//---------------------------------------------------------------------------


class wxSVGElement:
  public wxSvgXmlElement,
  public wxSVGLocatable
  
{
  protected:
    wxString m_id;
    wxString m_xmlbase;
    wxSVGSVGElement* m_ownerSVGElement;
    wxSVGElement* m_viewportElement;

  public:
    inline const wxString& GetId() const { return m_id; }
    inline void SetId(const wxString& n) { m_id = n; }

    inline const wxString& GetXmlbase() const { return m_xmlbase; }
    inline void SetXmlbase(const wxString& n) { m_xmlbase = n; }

    inline wxSVGSVGElement* GetOwnerSVGElement() const { return m_ownerSVGElement; }
    inline void SetOwnerSVGElement(wxSVGSVGElement* n) { m_ownerSVGElement = n; }

    inline wxSVGElement* GetViewportElement() const { return m_viewportElement; }
    inline void SetViewportElement(wxSVGElement* n) { m_viewportElement = n; }


  public:
  	%pythonAppend wxSVGElement()       ""
  	
    wxSVGElement(wxString tagName = wxT("")):
      wxSvgXmlElement(wxSVGXML_ELEMENT_NODE, tagName),
      m_ownerSVGElement(NULL), m_viewportElement(NULL) { };
    
    virtual wxSVGDTD GetDtd() const = 0;
    virtual void AddProperty(const wxString& name, const wxString& value)
      { SetAttribute(name, value); }
  public:
    bool HasAttribute(const wxString& name);
    wxString GetAttribute(const wxString& name);
    bool SetAttribute(const wxString& name, const wxString& value);
    wxSvgXmlAttrHash GetAttributes() const;
};



//---------------------------------------------------------------------------
//****************************    NodeList   ********************************
//---------------------------------------------------------------------------


WX_DECLARE_OBJARRAY(wxSVGElement*, wxNodeList);



class wxNodeListCls
{
	protected:
		wxNodeList my_list;
		
	public:
		%pythonAppend wxNodeListCls()       ""
		wxNodeListCls(wxNodeList m_list){ my_list = m_list; }
		%RenameCtor(PreNodeListCls, wxNodeListCls());
		
		wxSVGElement *GetFirstElement();
		wxSVGElement *GetElement(int i);
		int GetSize();
};


//---------------------------------------------------------------------------
//****************************    wxSvgDocument  ****************************
//---------------------------------------------------------------------------

#ifndef wxSVG_DOCUMENT_EVENT_H
#define wxSVG_DOCUMENT_EVENT_H

struct wxDocumentEvent {};

#endif //wxSVG_DOCUMENT_EVENT_H


MustHaveApp(wxSVGDocument);
class wxSVGDocument:public wxSvgXmlDocument,public wxDocumentEvent
{

  public:
    %pythonAppend wxSVGDocument()				""
    
    wxSVGDocument(const wxString& filename, const wxString& encoding = wxT("UTF-8"));
		~wxSVGDocument();


    %RenameCtor(PreSVGDocument, wxSVGDocument());
    
    wxSVGSVGElement* GetRootElement() { return (wxSVGSVGElement*) GetRoot(); }
    void SetRootElement(wxSVGSVGElement* n) { SetRoot((wxSvgXmlElement*) n); }
    wxSVGElement* GetElementById(const wxString& id);

    wxImage Render(int width = -1, int height = -1, const wxSVGRect* rect = NULL);
    wxImage RenderElementById(const wxString& id);
 
};


//---------------------------------------------------------------------------
//****************************    wxSVGRect  **************************
//---------------------------------------------------------------------------

class wxSVGRect
{
  public:
    inline double GetX() const { return m_x; }
    inline void SetX(double n) { m_x = n; m_empty = false; }

    inline double GetY() const { return m_y; }
    inline void SetY(double n) { m_y = n; m_empty = false; }

    inline double GetWidth() const { return m_width; }
    inline void SetWidth(double n) { m_width = n; m_empty = false; }

    inline double GetHeight() const { return m_height; }
    inline void SetHeight(double n) { m_height = n; m_empty = false; }
    
    inline bool IsEmpty() const { return m_empty; }
    inline void Clear() { m_x = m_y = m_width = m_height = 0; m_empty = true; }
    
  public:
	  %pythonAppend wxSVGRect()				""
    wxSVGRect(): m_x(0), m_y(0), m_width(0), m_height(0), m_empty(true) {}
    wxSVGRect(double x, double y, double width, double height):
      m_x(x), m_y(y), m_width(width), m_height(height), m_empty(false) {}
    ~wxSVGRect() {}
    wxString GetValueAsString() const;
    void SetValueAsString(const wxString& value);
    wxSVGRect MatrixTransform(const wxSVGMatrix& matrix) const;
};




//---------------------------------------------------------------------------
//****************************    wxSVGSVGElement  **************************
//---------------------------------------------------------------------------


class wxSVGSVGElement:wxSVGElement
{
	
  public:
  	%pythonAppend wxSVGSVGElement()				""
  	
    wxSVGSVGElement(wxString tagName = wxT("svg")):
      wxSVGElement(tagName), m_pixelUnitToMillimeterX(0), m_pixelUnitToMillimeterY(0), m_screenPixelToMillimeterX(0), m_screenPixelToMillimeterY(0), m_useCurrentView(0), m_currentScale(0);

		%RenameCtor(PreSVGSVGElement, wxSVGSVGElement());
		
		
		inline const wxSVGAnimatedLength& GetX() const { WX_SVG_ANIM_LENGTH_CALC_WIDTH(m_x, GetViewportElement()); return m_x; }
    inline void SetX(const wxSVGAnimatedLength& n) { m_x = n; }
    inline void SetX(const wxSVGLength& n) { m_x.SetBaseVal(n); }

    inline const wxSVGAnimatedLength& GetY() const { WX_SVG_ANIM_LENGTH_CALC_HEIGHT(m_y, GetViewportElement()); return m_y; }
    inline void SetY(const wxSVGAnimatedLength& n) { m_y = n; }
    inline void SetY(const wxSVGLength& n) { m_y.SetBaseVal(n); }

    inline const wxSVGAnimatedLength& GetWidth() const { WX_SVG_ANIM_LENGTH_CALC_WIDTH(m_width, GetViewportElement()); return m_width; }
    inline void SetWidth(const wxSVGAnimatedLength& n) { m_width = n; }
    inline void SetWidth(const wxSVGLength& n) { m_width.SetBaseVal(n); }

    inline const wxSVGAnimatedLength& GetHeight() const { WX_SVG_ANIM_LENGTH_CALC_HEIGHT(m_height, GetViewportElement()); return m_height; }
    inline void SetHeight(const wxSVGAnimatedLength& n) { m_height = n; }
    inline void SetHeight(const wxSVGLength& n) { m_height.SetBaseVal(n); }

    inline const wxString& GetContentScriptType() const { return m_contentScriptType; }
    inline void SetContentScriptType(const wxString& n) { m_contentScriptType = n; }

    inline const wxString& GetContentStyleType() const { return m_contentStyleType; }
    inline void SetContentStyleType(const wxString& n) { m_contentStyleType = n; }

    inline const wxSVGRect& GetViewport() const { return m_viewport; }
    inline void SetViewport(const wxSVGRect& n) { m_viewport = n; }

    inline double GetPixelUnitToMillimeterX() const { return m_pixelUnitToMillimeterX; }
    inline void SetPixelUnitToMillimeterX(double n) { m_pixelUnitToMillimeterX = n; }

    inline double GetPixelUnitToMillimeterY() const { return m_pixelUnitToMillimeterY; }
    inline void SetPixelUnitToMillimeterY(double n) { m_pixelUnitToMillimeterY = n; }

    inline double GetScreenPixelToMillimeterX() const { return m_screenPixelToMillimeterX; }
    inline void SetScreenPixelToMillimeterX(double n) { m_screenPixelToMillimeterX = n; }

    inline double GetScreenPixelToMillimeterY() const { return m_screenPixelToMillimeterY; }
    inline void SetScreenPixelToMillimeterY(double n) { m_screenPixelToMillimeterY = n; }

    inline bool GetUseCurrentView() const { return m_useCurrentView; }
    inline void SetUseCurrentView(bool n) { m_useCurrentView = n; }

    inline const wxSVGViewSpec& GetCurrentView() const { return m_currentView; }
    inline void SetCurrentView(const wxSVGViewSpec& n) { m_currentView = n; }

    inline double GetCurrentScale() const { return m_currentScale; }
    inline void SetCurrentScale(double n) { m_currentScale = n; }

    inline const wxSVGPoint& GetCurrentTranslate() const { return m_currentTranslate; }
    inline void SetCurrentTranslate(const wxSVGPoint& n) { m_currentTranslate = n; }

    wxSVGRect GetBBox(wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER) { return wxSVGLocatable::GetChildrenBBox(this, coordinates); }
    wxSVGRect GetResultBBox(wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER) { return wxSVGLocatable::GetChildrenResultBBox(this, coordinates); }
    wxSvgXmlElement* GetElementById(const wxString& elementId) const;
    virtual wxNodeList GetIntersectionList(const wxSVGRect& rect, const wxSVGElement& referenceElement);
    virtual wxNodeList GetEnclosureList(const wxSVGRect& rect, const wxSVGElement& referenceElement);
    virtual bool CheckIntersection(const wxSVGElement& element, const wxSVGRect& rect);
    virtual bool CheckEnclosure(const wxSVGElement& element, const wxSVGRect& rect);
    bool HasAttribute(const wxString& name);
    wxString GetAttribute(const wxString& name);
    bool SetAttribute(const wxString& name, const wxString& value);
    wxSvgXmlAttrHash GetAttributes() const;
    virtual wxSVGDTD GetDtd() const { return wxSVG_SVG_ELEMENT; }
    
  
};

//---------------------------------------------------------------------------
//****************************    wxSvgCtrl    ******************************
//---------------------------------------------------------------------------

MustHaveApp(wxSVGCtrl);
class wxSVGCtrl : public wxControl
{
public:
    %pythonAppend wxSVGCtrl         "self._setOORInfo(self)"
    %pythonAppend wxSVGCtrl()       ""

    wxSVGCtrl(wxWindow* parent, wxWindowID id = wxID_ANY,
      const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
      long style = 0, const wxString& name = wxPySVGControlNameStr);

    %RenameCtor(PreSVGCtrl, wxSVGCtrl());
    void SetFitToFrame(bool fit = true) { m_fitToFrame = fit; }
    double GetScale() const;
    wxSVGDocument* GetSVG() { return m_doc; }
     bool Load(const wxString& filename);
     
     void Refresh(bool eraseBackground = true, const wxRect* rect = NULL);
     void Clear();
     
     void MoveElement(wxSVGElement* elem, double Xposition, double Yposition);

protected:
     void OnPaint(wxPaintEvent& event);
};

//---------------------------------------------------------------------------
//****************************    wxSVGPoint    ******************************
//---------------------------------------------------------------------------


class wxSVGPoint
{
  protected:
    double m_x;
    double m_y;

  public:
    inline double GetX() const { return m_x; }
    inline void SetX(double n) { m_x = n; }

    inline double GetY() const { return m_y; }
    inline void SetY(double n) { m_y = n; }

  public:
    %pythonAppend wxSVGPoint()       ""
    
    wxSVGPoint(): m_x(0), m_y(0) {}
    wxSVGPoint(double x, double y): m_x(x), m_y(y) {}
    virtual wxSVGPoint MatrixTransform(const wxSVGMatrix& matrix) const;
};


//---------------------------------------------------------------------------
//****************************    wxSVGFitToViewBox    ******************************
//---------------------------------------------------------------------------


class wxSVGFitToViewBox
{
  protected:
    wxSVGAnimatedRect m_viewBox;
    wxSVGAnimatedPreserveAspectRatio m_preserveAspectRatio;

  public:
    %pythonAppend wxSVGFitToViewBox()       ""
    
    inline const wxSVGAnimatedRect& GetViewBox() const { return m_viewBox; }
    inline void SetViewBox(const wxSVGAnimatedRect& n) { m_viewBox = n; }
    inline void SetViewBox(const wxSVGRect& n) { m_viewBox.SetBaseVal(n); }

    inline const wxSVGAnimatedPreserveAspectRatio& GetPreserveAspectRatio() const { return m_preserveAspectRatio; }
    inline void SetPreserveAspectRatio(const wxSVGAnimatedPreserveAspectRatio& n) { m_preserveAspectRatio = n; }
    inline void SetPreserveAspectRatio(const wxSVGPreserveAspectRatio& n) { m_preserveAspectRatio.SetBaseVal(n); }

  public:
    void UpdateMatrix(wxSVGMatrix& matrix, const wxSVGLength& width, const wxSVGLength& height);
    bool HasAttribute(const wxString& name);
    wxString GetAttribute(const wxString& name);
    bool SetAttribute(const wxString& name, const wxString& value);
    wxSvgXmlAttrHash GetAttributes() const;
};

//---------------------------------------------------------------------------
//****************************    wxSVGViewSpec    ******************************
//---------------------------------------------------------------------------


class wxSVGViewSpec:
  public wxSVGZoomAndPan,
  public wxSVGFitToViewBox
{
  protected:
    wxSVGTransformList m_transform;
    wxSVGElement* m_viewTarget;
    wxString m_viewBoxString;
    wxString m_preserveAspectRatioString;
    wxString m_transformString;
    wxString m_viewTargetString;

  public:
  	%pythonAppend wxSVGViewSpec         "self._setOORInfo(self)"
    %pythonAppend wxSVGViewSpec()       ""
    
    inline const wxSVGTransformList& GetTransform() const { return m_transform; }
    inline void SetTransform(const wxSVGTransformList& n) { m_transform = n; }

    inline wxSVGElement* GetViewTarget() const { return m_viewTarget; }
    inline void SetViewTarget(wxSVGElement* n) { m_viewTarget = n; }

    inline const wxString& GetViewBoxString() const { return m_viewBoxString; }
    inline void SetViewBoxString(const wxString& n) { m_viewBoxString = n; }

    inline const wxString& GetPreserveAspectRatioString() const { return m_preserveAspectRatioString; }
    inline void SetPreserveAspectRatioString(const wxString& n) { m_preserveAspectRatioString = n; }

    inline const wxString& GetTransformString() const { return m_transformString; }
    inline void SetTransformString(const wxString& n) { m_transformString = n; }

    inline const wxString& GetViewTargetString() const { return m_viewTargetString; }
    inline void SetViewTargetString(const wxString& n) { m_viewTargetString = n; }

  public:
    wxSVGViewSpec(): m_viewTarget(NULL) {}
    bool HasAttribute(const wxString& name);
    wxString GetAttribute(const wxString& name);
    bool SetAttribute(const wxString& name, const wxString& value);
    wxSvgXmlAttrHash GetAttributes() const;
};




//---------------------------------------------------------------------------
//****************************    wxSVGAnimatedRect    ***************************
//--------------------------------------------------------------------------

class wxSVGAnimatedRect
{
  public:
  	%pythonAppend wxSVGAnimatedRect         "self._setOORInfo(self)"
    %pythonAppend wxSVGAnimatedRect()       ""
    
    wxSVGAnimatedRect(): m_animVal(NULL) {}
    wxSVGAnimatedRect(const wxSVGRect& value): m_baseVal(value), m_animVal(NULL) {}
    wxSVGAnimatedRect(const wxSVGAnimatedRect& value): m_baseVal(value.m_baseVal), m_animVal(NULL)
    { if (value.m_animVal != NULL) m_animVal = new wxSVGRect(*value.m_animVal); }
    
    inline wxSVGAnimatedRect& operator=(const wxSVGAnimatedRect& value)
    { m_baseVal = value.m_baseVal; m_animVal = value.m_animVal != NULL ? new wxSVGRect(*value.m_animVal) : NULL; return *this; }
    
    inline wxSVGRect& GetBaseVal() { return m_baseVal; }
    inline const wxSVGRect& GetBaseVal() const { return m_baseVal; }
    inline void SetBaseVal(const wxSVGRect& value) { m_baseVal = value; ResetAnimVal(); }
    
    inline wxSVGRect& GetAnimVal()
    {
      if (!m_animVal)
        m_animVal = new wxSVGRect(m_baseVal);
      return *m_animVal;
    }
    inline const wxSVGRect& GetAnimVal() const
    {
        return m_animVal ? *m_animVal : m_baseVal;
    }
    inline void SetAnimVal(const wxSVGRect& value)
    {
      if (!m_animVal)
        m_animVal = new wxSVGRect(value);
      else
        *m_animVal = value;
    }
    inline void ResetAnimVal()
    {
      if (m_animVal)
      {
        delete m_animVal;
        m_animVal = NULL;
      }
    }
    
  public:
    inline operator const wxSVGRect&() const { return GetAnimVal(); }
    
  protected:
    wxSVGRect m_baseVal;
    wxSVGRect* m_animVal;
};

//---------------------------------------------------------------------------
//****************************    wxSVGAnimatedLength    ***************************
//--------------------------------------------------------------------------


class wxSVGAnimatedLength
{
  public:
  	%pythonAppend wxSVGAnimatedLength         "self._setOORInfo(self)"
		%pythonAppend wxSVGAnimatedLength()       ""
    wxSVGAnimatedLength(): m_animVal(NULL) {}
    wxSVGAnimatedLength(const wxSVGLength& value): m_baseVal(value), m_animVal(NULL) {}
    wxSVGAnimatedLength(const wxSVGAnimatedLength& value): m_baseVal(value.m_baseVal), m_animVal(NULL)
    { if (value.m_animVal != NULL) m_animVal = new wxSVGLength(*value.m_animVal); }
    
    inline wxSVGAnimatedLength& operator=(const wxSVGAnimatedLength& value)
    { m_baseVal = value.m_baseVal; m_animVal = value.m_animVal != NULL ? new wxSVGLength(*value.m_animVal) : NULL; return *this; }
    
    inline wxSVGLength& GetBaseVal() { return m_baseVal; }
    inline const wxSVGLength& GetBaseVal() const { return m_baseVal; }
    inline void SetBaseVal(const wxSVGLength& value) { m_baseVal = value; ResetAnimVal(); }
    
    inline wxSVGLength& GetAnimVal()
    {
      if (!m_animVal)
        m_animVal = new wxSVGLength(m_baseVal);
      return *m_animVal;
    }
    inline const wxSVGLength& GetAnimVal() const
    {
        return m_animVal ? *m_animVal : m_baseVal;
    }
    inline void SetAnimVal(const wxSVGLength& value)
    {
      if (!m_animVal)
        m_animVal = new wxSVGLength(value);
      else
        *m_animVal = value;
    }
    inline void ResetAnimVal()
    {
      if (m_animVal)
      {
        delete m_animVal;
        m_animVal = NULL;
      }
    }
    
  public:
    inline operator const wxSVGLength&() const { return GetAnimVal(); }
    
  protected:
    wxSVGLength m_baseVal;
    wxSVGLength* m_animVal;
};


//---------------------------------------------------------------------------
//****************************    wxSVGLength    ***************************
//--------------------------------------------------------------------------

class wxSVGLength
{
  protected:
    wxSVG_LENGTHTYPE m_unitType;
    double m_value;
    double m_valueInSpecifiedUnits;

  public:
    inline wxSVG_LENGTHTYPE GetUnitType() const { return m_unitType; }
    inline void SetUnitType(const wxSVG_LENGTHTYPE& n) { m_unitType = n; }

  public:
		%pythonAppend wxSVGLength()       ""
		
    wxSVGLength() : m_unitType(wxSVG_LENGTHTYPE_UNKNOWN), m_value(0), m_valueInSpecifiedUnits(0) {}
    wxSVGLength(double v) : m_unitType(wxSVG_LENGTHTYPE_NUMBER), m_value(v), m_valueInSpecifiedUnits(v) {}
    wxSVGLength(wxSVG_LENGTHTYPE unitType, double v): m_unitType(unitType) { SetValueInSpecifiedUnits(v); }
    wxSVGLength(const wxSVGLength& l): m_unitType(l.m_unitType), m_value(l.m_value), m_valueInSpecifiedUnits(l.m_valueInSpecifiedUnits) {}
    
    inline double GetValue() const { return m_value; }
    inline void SetValue(double n) { m_unitType = wxSVG_LENGTHTYPE_NUMBER; m_valueInSpecifiedUnits = n; m_value = n; }
    inline operator double() const { return GetValue(); }
    
    double GetValueInSpecifiedUnits() const { return m_valueInSpecifiedUnits; }
    void SetValueInSpecifiedUnits(double n);
    
    wxString GetValueAsString() const;
    void SetValueAsString(const wxString& n);
    
    inline void ToViewportWidth(float viewportWidth) { m_value = m_valueInSpecifiedUnits*viewportWidth/100; }
	inline void ToViewportHeight(float viewportHeight) { m_value = m_valueInSpecifiedUnits*viewportHeight/100; }
	inline void ToViewportSize(float viewportWidth, float viewportHeight)
	{
	  m_value = m_valueInSpecifiedUnits*
		sqrt(viewportWidth*viewportWidth + viewportHeight*viewportHeight)/sqrt(2)/100;
	}

    virtual void NewValueSpecifiedUnits(wxSVG_LENGTHTYPE unitType, double valueInSpecifiedUnits);
    virtual void ConvertToSpecifiedUnits(wxSVG_LENGTHTYPE unitType);
};



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//****************************    SVGUIElement    ***************************
//--------------------------------------------------------------------------

class SVGUIElement:public wxSvgXmlElement
{
	protected:
		wxSVGDocument* m_doc;
		wxSVGElement* m_BackgroundElement;
		bool m_enable;
		bool m_visible;
    bool m_selected;
		
	public:
		//%pythonAppend SVGUIElement         "self._setOORInfo(self)"
		%pythonAppend SVGUIElement()       ""
		
		SVGUIElement();
		SVGUIElement(wxSVGDocument* doc);
		~SVGUIElement();
		wxString GetId();
		wxString GetName();
		
		virtual void Initialize(){Update_Elements();}
		virtual bool HitTest(wxPoint pt) = 0;
		virtual wxSVGRect GetBBox() = 0;
		virtual void Update_Elements() = 0;
		virtual void SetSelected(bool selected) {m_selected = selected;}
    bool IsVisible(){return m_visible;}
    bool IsEnabled(){return m_enable;}
		
		void Hide();
		void Show();
		void Enable(){m_enable = true;}
		void Disable(){m_enable = false;}
		
		virtual void AddProperty(const wxString& name, const wxString& value);
		virtual bool SetAttribute(const wxString& attrName, const wxString& attrValue); 
};



//---------------------------------------------------------------------------
//****************************    SVGUIControl    ***************************
//--------------------------------------------------------------------------




class SVGUIControl:
	public SVGUIElement
{
	protected:
		wxEvtHandler* m_window;
		
	public:
		%pythonAppend SVGUIControl         "self._setOORInfo(self)"
		%pythonAppend SVGUIControl()       ""
	
		SVGUIControl(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUIControl();
	 	
		void Refresh();
		
		virtual bool HitTest(wxPoint pt);
		virtual wxSVGRect GetBBox();
		virtual void Update_Elements() = 0;

		virtual void OnLeftDown(wxMouseEvent& event);		
		virtual void OnLeftUp(wxMouseEvent& event);
		virtual void OnMotion(wxMouseEvent& event);
		virtual void OnChar(wxKeyEvent& event);
  	
};



//---------------------------------------------------------------------------
//****************************    SVGUIContainer    ***************************
//--------------------------------------------------------------------------


class SVGUIContainer:
	public SVGUIElement
{
	protected:
		SVGUIElement* m_FocusedElement;
		
	public:
		%pythonAppend SVGUIContainer()       ""
		
		SVGUIContainer(){};
		SVGUIContainer(wxSVGDocument* doc);
		~SVGUIContainer();
	 	wxString GetFocusedElement();
		wxString GetFocusedElementName();
		virtual void Update_Elements();
		
		void Hide();
		void Show();
		void Enable();
		void Disable();
		
		virtual bool HitTest(wxPoint pt);
		virtual wxSVGRect GetBBox();
		
		virtual void OnLeftDown(wxMouseEvent& event);   
    virtual void OnLeftUp(wxMouseEvent& event);
    virtual void OnMotion(wxMouseEvent& event);
    virtual void OnChar(wxKeyEvent& event);
};



//---------------------------------------------------------------------------
//****************************    SVGUIScrollBar    ***************************
//--------------------------------------------------------------------------



class SVGUIScrollBar:
	public SVGUIControl
{
	protected:
		bool m_initialised;
		wxSVGPoint m_direction;
		wxSVGPoint m_position_size;
		wxSVGPoint m_offset;
		wxSVGPoint* m_last_cursor_position;
		unsigned int m_position;
		unsigned int m_thumb;
		unsigned int m_range;
		wxSVGElement* m_ThumbBackElement;
		wxSVGElement* m_ThumbMiddleElement;
		wxSVGElement* m_UpArrowElement;
		wxSVGElement* m_DownArrowElement;
	
	public:
		%pythonAppend SVGUIScrollBar         "self._setOORInfo(self)"
		%pythonAppend SVGUIScrollBar()       ""
		SVGUIScrollBar(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUIScrollBar();
		void Init_ScrollBar(unsigned int position, unsigned int thumb, unsigned int range);
		void Initialize();
		unsigned int GetThumbPosition(){return m_position;}
		unsigned int GetThumbSize(){return m_thumb;}
		unsigned int GetRange(){return m_range;}
		
		void MoveThumbByUnit(int direction);
		void MoveThumbByPage(int direction);
		
		bool HitTest(wxPoint pt);
		wxSVGRect GetBBox();
		bool SetAttribute(const wxString& attrName, const wxString& attrValue);
		void Update_Elements();
		
		void OnLeftDown(wxMouseEvent &event);
		void OnMotion(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
};




//---------------------------------------------------------------------------
//*************************    SVGUINoteBookContent    ************************
//--------------------------------------------------------------------------



class SVGUINoteBookContent:
  public SVGUIContainer
{
  protected:
    wxSVGElement* m_TabElement;
    wxSVGElement* m_ContentElement;
    
  public:
    %pythonAppend SVGUINoteBookContent         "self._setOORInfo(self)"
		%pythonAppend SVGUINoteBookContent()       ""
    SVGUINoteBookContent(wxSVGDocument* doc);
    ~SVGUINoteBookContent();
	 	
    bool SetAttribute(const wxString& attrName, const wxString& attrValue);
    wxSVGElement* GetTabElement() {return m_TabElement;}
    wxSVGElement* GetContentElement() {return m_ContentElement;}
};



//---------------------------------------------------------------------------
//****************************    SVGUINoteBook    ***************************
//--------------------------------------------------------------------------



class SVGUINoteBook:
	public SVGUIControl
{
	protected:
		bool m_initialised;
    int m_current_page;
    SVGUINoteBookContent* m_current_content;
    wxSVGElement* m_GroupElement;
    wxSVGElement* m_ContentElement;
	
	public:
		%pythonAppend SVGUINoteBook         "self._setOORInfo(self)"
		%pythonAppend SVGUINoteBook()       ""
		SVGUINoteBook(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUINoteBook();
	 	
		bool HitTest(wxPoint pt);
    wxSVGRect GetBBox();
    bool SetAttribute(const wxString& attrName, const wxString& attrValue);
    void Initialize();
    void Update_Elements();
    unsigned int GetCurrentPage(){return m_current_page;}
    void SetCurrentPage(int page);
    
    void OnLeftDown(wxMouseEvent &event);
    void OnMotion(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
};




//---------------------------------------------------------------------------
//****************************    SVGUIRotatingCtrl    ***************************
//--------------------------------------------------------------------------



class SVGUIRotatingCtrl:
	public SVGUIControl
{
	protected:
		bool m_initialised;
		wxSVGPoint* m_center;
		wxSVGPoint* m_last_cursor_position;
		wxSVGPoint* m_init_pos;
		double m_angle;
		double m_min_angle;
		double m_max_angle;
		bool m_show_center;
		wxSVGElement* m_RotatingElement;
		wxSVGElement* m_CenterElement;
	
	public:
		%pythonAppend SVGUIRotatingCtrl         "self._setOORInfo(self)"
		%pythonAppend SVGUIRotatingCtrl()       ""
		
		SVGUIRotatingCtrl(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUIRotatingCtrl();
	 	void Initialize();
		
		double GetAngle(){return m_angle;}
		double GetMinAngle(){return m_min_angle;}
		double GetMaxAngle(){return m_max_angle;}
		void SetAngle(double angle);
		void DefineCenter(wxSVGPoint* center);
		wxSVGPoint* GetCenter();
		void DefineLimits(double min_angle, double max_angle);
		void Rotate(double angle);
		
		bool HitTest(wxPoint pt);
		wxSVGRect GetBBox();
		bool SetAttribute(const wxString& attrName, const wxString& attrValue);
		void Update_Elements();
		
		void OnLeftDown(wxMouseEvent &event);
		void OnMotion(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
};






//---------------------------------------------------------------------------
//****************************    SVGUIButton    ***************************
//--------------------------------------------------------------------------



class SVGUIButton:
	public SVGUIControl
{
	protected:
		bool m_up;
		wxSVGElement* m_SelectedElement;
		wxSVGElement* m_UnselectedElement;		
	
	public:
		%pythonAppend SVGUIButton         "self._setOORInfo(self)"
		%pythonAppend SVGUIButton()       ""
		
		SVGUIButton(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUIButton();
	 	
		bool HitTest(wxPoint pt);
		wxSVGRect GetBBox();
		bool SetAttribute(const wxString& attrName, const wxString& attrValue);
		void Update_Elements();
		
		void OnLeftDown(wxMouseEvent &event);
		void OnMotion(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
};




//---------------------------------------------------------------------------
//****************************    SVGUITextCtrl    ***************************
//--------------------------------------------------------------------------



class SVGUITextCtrl:
	public SVGUIControl
{
	protected:
		bool m_initialised;
		bool m_selected;
		bool m_fixed_size;
		bool m_show_background;
		long m_style;
		wxSVGPoint m_offset;
		wxSVGRect m_last_bbox;
		unsigned int m_cursor_position;
		wxSVGElement* m_TextElement;
		wxSVGElement* m_CursorElement;
		
		unsigned int RecursiveCursorSearch(wxSVGPoint& point, unsigned int start, unsigned int end);
		unsigned int AjustSize(unsigned int start, unsigned int end, wxSVGRect back, wxSVGRect text);
		void SetText(const wxString& value);
		
	public:
		%pythonAppend SVGUITextCtrl       "self._setOORInfo(self)"
		%pythonAppend SVGUITextCtrl()       ""
		
		SVGUITextCtrl(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUITextCtrl();
	 	void Initialize();
		
		bool HitTest(const wxPoint pt);
		wxSVGRect GetBBox();
		bool SetAttribute(const wxString& attrName, const wxString& attrValue);
		wxString GetValue();
		void SetValue(const wxString& value);
		void SetStyle(long style) {m_style = style;}
		long GetStyle() {return m_style;}
		void SetSelected(const bool selected);
		
		void AddCharInText(const wxString& character);
		void DelCharInText(const bool backward=false);
		void MoveCursor(const int direction);
		
		void FindCursorIndex(wxSVGPoint& point);
		void Update_Elements();
		
		void OnLeftDown(wxMouseEvent &event);
		void OnMotion(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
		void OnChar(wxKeyEvent &event);
};



//---------------------------------------------------------------------------
//****************************    SVGUITransform    ***************************
//--------------------------------------------------------------------------

class SVGUITransform:
	public SVGUIControl
{
	protected:
		bool m_initialised;
		double m_angle;
		double m_x_pos;
		double m_y_pos;
		double m_x_scale;
		double m_y_scale;
		wxSVGPoint* m_last_cursor_position;
		wxSVGRect* m_moving_zone;
				
		wxSVGElement* m_MovingElement;
		
	public:
		%pythonAppend SVGUITransform         "self._setOORInfo(self)"
		%pythonAppend SVGUITransform()       ""
		
		SVGUITransform(wxSVGDocument* doc, wxEvtHandler* window);
		~SVGUITransform();
	 	void Initialize();
		
		bool HitTest(wxPoint pt);
    wxSVGRect GetBBox();
    bool SetAttribute(const wxString& attrName, const wxString& attrValue);
		void Update_Elements();
    
    double GetX(){return m_x_pos;}
    double GetY(){return m_y_pos;}
    double GetXScale(){return m_y_scale;}
    double GetYScale(){return m_y_scale;}
    double GetAngle(){return m_angle;}
    void Move(double x, double y);
    void Scale(double x, double y);
    void Rotate(double angle);
    
		void OnLeftDown(wxMouseEvent &event);
		void OnMotion(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
};



//---------------------------------------------------------------------------
//****************************    SVGUIWindow    ***************************
//--------------------------------------------------------------------------


MustHaveApp(SVGUIWindow);
class SVGUIWindow:
	public wxSvgXmlDocument,
	public wxSVGCtrl
{
	protected:
		bool m_clicked;
  
	public:
		%pythonAppend SVGUIWindow         "self._setOORInfo(self)"
		%pythonAppend SVGUIWindow()       ""
		
		SVGUIWindow(wxWindow* parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
			long style = 0, const wxString& name = wxPanelNameStr);
	 	
	  SVGUIElement* CreateElement(const wxString& tagName);
		SVGUIElement* CreateElementNS(const wxString& namespaceURI, const wxString& qualifiedName);
		
		virtual wxWindow* CreateWindow(const wxString& classname);
		
		bool LoadFiles(const wxString& svgfile, const wxString& deffile);
		void Update_Elements();
		
		SVGUIContainer* GetSVGUIRootElement();
		SVGUIElement* GetElementById(const wxString& id);
		SVGUIScrollBar* GetScrollBarById(const wxString& id);
		
		virtual void OnLeftDown(wxMouseEvent& event);		
		virtual void OnLeftUp(wxMouseEvent& event);
		virtual void OnMotion(wxMouseEvent& event);
		virtual void OnChar(wxKeyEvent& event);
    virtual void OnRefresh(wxCommandEvent& event);
};



