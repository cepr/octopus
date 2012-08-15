//////////////////////////////////////////////////////////////////////////////
// Name:        SVGFEFloodElement.h
// Author:      Alex Thuering
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
// Notes:       generated by generate.py
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_FE_FLOOD_ELEMENT_H
#define WX_SVG_FE_FLOOD_ELEMENT_H

#include "SVGElement.h"
#include "SVGFilterPrimitiveStandardAttributes.h"
#include "SVGAnimatedString.h"
#include "String_wxsvg.h"
#include "Element.h"

class wxSVGFEFloodElement:
  public wxSVGElement,
  public wxSVGFilterPrimitiveStandardAttributes
{
  protected:
    wxSVGAnimatedString m_in1;

  public:
    inline const wxSVGAnimatedString& GetIn1() const { return m_in1; }
    inline void SetIn1(const wxSVGAnimatedString& n) { m_in1 = n; }
    inline void SetIn1(const wxString& n) { m_in1.SetBaseVal(n); }

  public:
    wxSVGFEFloodElement(wxString tagName = wxT("feFlood")):
      wxSVGElement(tagName) {}
    virtual ~wxSVGFEFloodElement() {}
    wxSvgXmlNode* CloneNode(bool deep = true) { return new wxSVGFEFloodElement(*this); }
    bool HasAttribute(const wxString& name);
    wxString GetAttribute(const wxString& name);
    bool SetAttribute(const wxString& name, const wxString& value);
    wxSvgXmlAttrHash GetAttributes() const;
    virtual wxSVGDTD GetDtd() const { return wxSVG_FEFLOOD_ELEMENT; }
};

#endif // WX_SVG_FE_FLOOD_ELEMENT_H
