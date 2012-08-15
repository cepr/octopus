//////////////////////////////////////////////////////////////////////////////
// Name:        SVGSVGElement.h
// Author:      Alex Thuering
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
// Notes:       generated by generate.py
//////////////////////////////////////////////////////////////////////////////

#ifndef WX_SVG_SVG_ELEMENT_H
#define WX_SVG_SVG_ELEMENT_H

#include "SVGElement.h"
#include "SVGTests.h"
#include "SVGLangSpace.h"
#include "SVGExternalResourcesRequired.h"
#include "SVGStylable.h"
#include "SVGLocatable.h"
#include "SVGFitToViewBox.h"
#include "SVGZoomAndPan.h"
#include "EventTarget.h"
#include "DocumentEvent.h"
#include "ViewCSS.h"
#include "DocumentCSS.h"
#include "SVGAnimatedLength.h"
#include "String_wxsvg.h"
#include "SVGRect.h"
#include "SVGViewSpec.h"
#include "SVGPoint.h"
#include "NodeList.h"
#include "SVGNumber.h"
#include "SVGLength.h"
#include "SVGAngle.h"
#include "SVGMatrix.h"
#include "SVGTransform.h"
#include "Element.h"

class wxSVGSVGElement:
  public wxSVGElement,
  public wxSVGTests,
  public wxSVGLangSpace,
  public wxSVGExternalResourcesRequired,
  public wxSVGStylable,
  public wxSVGLocatable,
  public wxSVGFitToViewBox,
  public wxSVGZoomAndPan,
  public wxEventTarget,
  public wxDocumentEvent,
  public wxViewCSS,
  public wxDocumentCSS
{
  protected:
    wxSVGAnimatedLength m_x;
    wxSVGAnimatedLength m_y;
    wxSVGAnimatedLength m_width;
    wxSVGAnimatedLength m_height;
    wxString m_contentScriptType;
    wxString m_contentStyleType;
    wxSVGRect m_viewport;
    double m_pixelUnitToMillimeterX;
    double m_pixelUnitToMillimeterY;
    double m_screenPixelToMillimeterX;
    double m_screenPixelToMillimeterY;
    bool m_useCurrentView;
    wxSVGViewSpec m_currentView;
    double m_currentScale;
    wxSVGPoint m_currentTranslate;

  public:
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

  public:
    wxSVGSVGElement(wxString tagName = wxT("svg")):
      wxSVGElement(tagName), m_pixelUnitToMillimeterX(0), m_pixelUnitToMillimeterY(0), m_screenPixelToMillimeterX(0), m_screenPixelToMillimeterY(0), m_useCurrentView(0), m_currentScale(0) {}
    virtual ~wxSVGSVGElement() {}
    wxSvgXmlNode* CloneNode(bool deep = true) { return new wxSVGSVGElement(*this); }
    wxSVGRect GetBBox(wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER) { return wxSVGLocatable::GetChildrenBBox(this, coordinates); }
    wxSVGRect GetResultBBox(wxSVG_COORDINATES coordinates = wxSVG_COORDINATES_USER) { return wxSVGLocatable::GetChildrenResultBBox(this, coordinates); }
    wxSVGMatrix GetCTM() { return wxSVGLocatable::GetCTM(this); }
    wxSVGMatrix GetScreenCTM() { return wxSVGLocatable::GetScreenCTM(this); }
    wxSvgXmlElement* GetElementById(const wxString& elementId) const;
    void UpdateMatrix(wxSVGMatrix& matrix) { wxSVGFitToViewBox::UpdateMatrix(matrix, GetWidth().GetAnimVal(), GetHeight().GetAnimVal()); }
    virtual unsigned long SuspendRedraw(unsigned long max_wait_milliseconds);
    virtual void UnsuspendRedraw(unsigned long suspend_handle_id);
    virtual void UnsuspendRedrawAll();
    virtual void ForceRedraw();
    virtual void PauseAnimations();
    virtual void UnpauseAnimations();
    virtual bool AnimationsPaused();
    virtual double GetCurrentTime();
    virtual void SetCurrentTime(double seconds);
    virtual wxNodeList GetIntersectionList(const wxSVGRect& rect, const wxSVGElement& referenceElement);
    virtual wxNodeList GetEnclosureList(const wxSVGRect& rect, const wxSVGElement& referenceElement);
    virtual bool CheckIntersection(const wxSVGElement& element, const wxSVGRect& rect);
    virtual bool CheckEnclosure(const wxSVGElement& element, const wxSVGRect& rect);
    virtual void DeselectAll();
    virtual wxSVGNumber CreateSVGNumber();
    virtual wxSVGLength CreateSVGLength();
    virtual wxSVGAngle CreateSVGAngle();
    virtual wxSVGPoint CreateSVGPoint();
    virtual wxSVGMatrix CreateSVGMatrix();
    virtual wxSVGRect CreateSVGRect();
    virtual wxSVGTransform CreateSVGTransform();
    virtual wxSVGTransform CreateSVGTransformFromMatrix(const wxSVGMatrix& matrix);
    bool HasAttribute(const wxString& name);
    wxString GetAttribute(const wxString& name);
    bool SetAttribute(const wxString& name, const wxString& value);
    wxSvgXmlAttrHash GetAttributes() const;
    virtual wxSVGDTD GetDtd() const { return wxSVG_SVG_ELEMENT; }
};

#endif // WX_SVG_SVG_ELEMENT_H