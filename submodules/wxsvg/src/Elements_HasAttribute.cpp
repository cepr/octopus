//////////////////////////////////////////////////////////////////////////////
// Name:        Elements_HasAttribute.cpp
// Author:      Alex Thuering
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
// Notes:       generated by genHasAttribute.py
//////////////////////////////////////////////////////////////////////////////

#include "String_wxsvg.h"
#include "SVGAElement.h"
#include "SVGElement.h"
#include "SVGURIReference.h"
#include "SVGTests.h"
#include "SVGLangSpace.h"
#include "SVGExternalResourcesRequired.h"
#include "SVGStylable.h"
#include "SVGTransformable.h"
#include "SVGAltGlyphDefElement.h"
#include "SVGAltGlyphElement.h"
#include "SVGTextPositioningElement.h"
#include "SVGTextContentElement.h"
#include "SVGAltGlyphItemElement.h"
#include "SVGAnimationElement.h"
#include "SVGAnimateColorElement.h"
#include "SVGAnimateElement.h"
#include "SVGAnimateMotionElement.h"
#include "SVGAnimateTransformElement.h"
#include "SVGAnimatedPathData.h"
#include "SVGAnimatedPoints.h"
#include "SVGCircleElement.h"
#include "SVGClipPathElement.h"
#include "SVGColorProfileElement.h"
#include "SVGComponentTransferFunctionElement.h"
#include "SVGCursorElement.h"
#include "SVGDefinitionSrcElement.h"
#include "SVGDefsElement.h"
#include "SVGDescElement.h"
#include "SVGEllipseElement.h"
#include "SVGFEBlendElement.h"
#include "SVGFilterPrimitiveStandardAttributes.h"
#include "SVGFEColorMatrixElement.h"
#include "SVGFEComponentTransferElement.h"
#include "SVGFECompositeElement.h"
#include "SVGFEConvolveMatrixElement.h"
#include "SVGFEDiffuseLightingElement.h"
#include "SVGFEDisplacementMapElement.h"
#include "SVGFEDistantLightElement.h"
#include "SVGFEFloodElement.h"
#include "SVGFEFuncAElement.h"
#include "SVGFEFuncBElement.h"
#include "SVGFEFuncGElement.h"
#include "SVGFEFuncRElement.h"
#include "SVGFEGaussianBlurElement.h"
#include "SVGFEImageElement.h"
#include "SVGFEMergeElement.h"
#include "SVGFEMergeNodeElement.h"
#include "SVGFEMorphologyElement.h"
#include "SVGFEOffsetElement.h"
#include "SVGFEPointLightElement.h"
#include "SVGFESpecularLightingElement.h"
#include "SVGFESpotLightElement.h"
#include "SVGFETileElement.h"
#include "SVGFETurbulenceElement.h"
#include "SVGFilterElement.h"
#include "SVGFitToViewBox.h"
#include "SVGFontElement.h"
#include "SVGFontFaceElement.h"
#include "SVGFontFaceFormatElement.h"
#include "SVGFontFaceNameElement.h"
#include "SVGFontFaceSrcElement.h"
#include "SVGFontFaceUriElement.h"
#include "SVGForeignObjectElement.h"
#include "SVGGElement.h"
#include "SVGGlyphElement.h"
#include "SVGGlyphRefElement.h"
#include "SVGGradientElement.h"
#include "SVGHKernElement.h"
#include "SVGImageElement.h"
#include "SVGLineElement.h"
#include "SVGLinearGradientElement.h"
#include "SVGMPathElement.h"
#include "SVGMarkerElement.h"
#include "SVGMaskElement.h"
#include "SVGMetadataElement.h"
#include "SVGMissingGlyphElement.h"
#include "SVGPathElement.h"
#include "SVGPatternElement.h"
#include "SVGPolygonElement.h"
#include "SVGPolylineElement.h"
#include "SVGRadialGradientElement.h"
#include "SVGRectElement.h"
#include "SVGSVGElement.h"
#include "SVGZoomAndPan.h"
#include "SVGScriptElement.h"
#include "SVGSetElement.h"
#include "SVGStopElement.h"
#include "SVGStyleElement.h"
#include "SVGSwitchElement.h"
#include "SVGSymbolElement.h"
#include "SVGTBreakElement.h"
#include "SVGTRefElement.h"
#include "SVGTSpanElement.h"
#include "SVGTextElement.h"
#include "SVGTextPathElement.h"
#include "SVGTitleElement.h"
#include "SVGUseElement.h"
#include "SVGVKernElement.h"
#include "SVGVideoElement.h"
#include "SVGViewElement.h"
#include "SVGViewSpec.h"

// wxSVGAnimateMotionElement
bool wxSVGAnimateMotionElement::HasAttribute(const wxString& attrName)
{
  return wxSVGAnimationElement::HasAttribute(attrName);
}      

// wxSVGFontFaceUriElement
bool wxSVGFontFaceUriElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFontFaceElement
bool wxSVGFontFaceElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFEFuncBElement
bool wxSVGFEFuncBElement::HasAttribute(const wxString& attrName)
{
  return wxSVGComponentTransferFunctionElement::HasAttribute(attrName);
}      

// wxSVGFEFuncAElement
bool wxSVGFEFuncAElement::HasAttribute(const wxString& attrName)
{
  return wxSVGComponentTransferFunctionElement::HasAttribute(attrName);
}      

// wxSVGFEFuncRElement
bool wxSVGFEFuncRElement::HasAttribute(const wxString& attrName)
{
  return wxSVGComponentTransferFunctionElement::HasAttribute(attrName);
}      

// wxSVGForeignObjectElement
bool wxSVGForeignObjectElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGFEMorphologyElement
bool wxSVGFEMorphologyElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("operator") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGMarkerElement
bool wxSVGMarkerElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("refX") ||
    attrName == wxT("refY") ||
    attrName == wxT("markerUnits") ||
    attrName == wxT("markerWidth") ||
    attrName == wxT("markerHeight") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGFitToViewBox::HasAttribute(attrName);
}      

// wxSVGFETileElement
bool wxSVGFETileElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGPathElement
bool wxSVGPathElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("pathLength") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName) ||
    wxSVGAnimatedPathData::HasAttribute(attrName);
}      

// wxSVGTSpanElement
bool wxSVGTSpanElement::HasAttribute(const wxString& attrName)
{
  return wxSVGTextPositioningElement::HasAttribute(attrName);
}      

// wxSVGFEColorMatrixElement
bool wxSVGFEColorMatrixElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("type") ||
    attrName == wxT("values") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGFontFaceFormatElement
bool wxSVGFontFaceFormatElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFEOffsetElement
bool wxSVGFEOffsetElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("dx") ||
    attrName == wxT("dy") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGSymbolElement
bool wxSVGSymbolElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGFitToViewBox::HasAttribute(attrName);
}      

// wxSVGFEMergeNodeElement
bool wxSVGFEMergeNodeElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    wxSVGElement::HasAttribute(attrName);
}      

// wxSVGTBreakElement
bool wxSVGTBreakElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGTransformable
bool wxSVGTransformable::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("transform");
}      

// wxSVGStyleElement
bool wxSVGStyleElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("xml:space") ||
    attrName == wxT("type") ||
    attrName == wxT("media") ||
    attrName == wxT("title") ||
    wxSVGElement::HasAttribute(attrName);
}      

// wxSVGPolygonElement
bool wxSVGPolygonElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName) ||
    wxSVGAnimatedPoints::HasAttribute(attrName);
}      

// wxSVGCursorElement
bool wxSVGCursorElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName);
}      

// wxSVGFECompositeElement
bool wxSVGFECompositeElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("in2") ||
    attrName == wxT("operator") ||
    attrName == wxT("k1") ||
    attrName == wxT("k2") ||
    attrName == wxT("k3") ||
    attrName == wxT("k4") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGGradientElement
bool wxSVGGradientElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("gradientUnits") ||
    attrName == wxT("gradientTransform") ||
    attrName == wxT("spreadMethod") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGLinearGradientElement
bool wxSVGLinearGradientElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x1") ||
    attrName == wxT("y1") ||
    attrName == wxT("x2") ||
    attrName == wxT("y2") ||
    wxSVGGradientElement::HasAttribute(attrName);
}      

// wxSVGTextElement
bool wxSVGTextElement::HasAttribute(const wxString& attrName)
{
  return wxSVGTextPositioningElement::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGFEPointLightElement
bool wxSVGFEPointLightElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("z") ||
    wxSVGElement::HasAttribute(attrName);
}      

// wxSVGHKernElement
bool wxSVGHKernElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGStopElement
bool wxSVGStopElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("offset") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGFEDisplacementMapElement
bool wxSVGFEDisplacementMapElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("in2") ||
    attrName == wxT("scale") ||
    attrName == wxT("xChannelSelector") ||
    attrName == wxT("yChannelSelector") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGLineElement
bool wxSVGLineElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x1") ||
    attrName == wxT("y1") ||
    attrName == wxT("x2") ||
    attrName == wxT("y2") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGFontFaceNameElement
bool wxSVGFontFaceNameElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGPatternElement
bool wxSVGPatternElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("patternUnits") ||
    attrName == wxT("patternContentUnits") ||
    attrName == wxT("patternTransform") ||
    attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGFitToViewBox::HasAttribute(attrName);
}      

// wxSVGExternalResourcesRequired
bool wxSVGExternalResourcesRequired::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("externalResourcesRequired");
}      

// wxSVGScriptElement
bool wxSVGScriptElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("type") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName);
}      

// wxSVGStylable
bool wxSVGStylable::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("class") ||
    attrName == wxT("style") ||
    HasCustomAttribute(attrName);
}      

// wxSVGFitToViewBox
bool wxSVGFitToViewBox::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("viewBox") ||
    attrName == wxT("preserveAspectRatio");
}      

// wxSVGTests
bool wxSVGTests::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("requiredFeatures") ||
    attrName == wxT("requiredExtensions") ||
    attrName == wxT("systemLanguage");
}      

// wxSVGSVGElement
bool wxSVGSVGElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    attrName == wxT("contentScriptType") ||
    attrName == wxT("contentStyleType") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGFitToViewBox::HasAttribute(attrName) ||
    wxSVGZoomAndPan::HasAttribute(attrName);
}      

// wxSVGViewSpec
bool wxSVGViewSpec::HasAttribute(const wxString& attrName)
{
  return wxSVGZoomAndPan::HasAttribute(attrName) ||
    wxSVGFitToViewBox::HasAttribute(attrName);
}      

// wxSVGVKernElement
bool wxSVGVKernElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGMetadataElement
bool wxSVGMetadataElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGAElement
bool wxSVGAElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("target") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGAltGlyphElement
bool wxSVGAltGlyphElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("glyphRef") ||
    attrName == wxT("format") ||
    wxSVGTextPositioningElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName);
}      

// wxSVGURIReference
bool wxSVGURIReference::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("xlink:href");
}      

// wxSVGAnimateTransformElement
bool wxSVGAnimateTransformElement::HasAttribute(const wxString& attrName)
{
  return wxSVGAnimationElement::HasAttribute(attrName);
}      

// wxSVGFEComponentTransferElement
bool wxSVGFEComponentTransferElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGFEBlendElement
bool wxSVGFEBlendElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("in2") ||
    attrName == wxT("mode") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGFEMergeElement
bool wxSVGFEMergeElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGTextPositioningElement
bool wxSVGTextPositioningElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("dx") ||
    attrName == wxT("dy") ||
    attrName == wxT("rotate") ||
    wxSVGTextContentElement::HasAttribute(attrName);
}      

// wxSVGEllipseElement
bool wxSVGEllipseElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("cx") ||
    attrName == wxT("cy") ||
    attrName == wxT("rx") ||
    attrName == wxT("ry") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGFilterElement
bool wxSVGFilterElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("filterUnits") ||
    attrName == wxT("primitiveUnits") ||
    attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGClipPathElement
bool wxSVGClipPathElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("clipPathUnits") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGSwitchElement
bool wxSVGSwitchElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGMaskElement
bool wxSVGMaskElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("maskUnits") ||
    attrName == wxT("maskContentUnits") ||
    attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGViewElement
bool wxSVGViewElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("viewTarget") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGFitToViewBox::HasAttribute(attrName) ||
    wxSVGZoomAndPan::HasAttribute(attrName);
}      

// wxSVGDefinitionSrcElement
bool wxSVGDefinitionSrcElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFilterPrimitiveStandardAttributes
bool wxSVGFilterPrimitiveStandardAttributes::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    attrName == wxT("result") ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGFEDistantLightElement
bool wxSVGFEDistantLightElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("azimuth") ||
    attrName == wxT("elevation") ||
    wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFEDiffuseLightingElement
bool wxSVGFEDiffuseLightingElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("surfaceScale") ||
    attrName == wxT("diffuseConstant") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGAnimatedPathData
bool wxSVGAnimatedPathData::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("d");
}      

// wxSVGFontFaceSrcElement
bool wxSVGFontFaceSrcElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGZoomAndPan
bool wxSVGZoomAndPan::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("zoomAndPan");
}      

// wxSVGDescElement
bool wxSVGDescElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGSetElement
bool wxSVGSetElement::HasAttribute(const wxString& attrName)
{
  return wxSVGAnimationElement::HasAttribute(attrName);
}      

// wxSVGAnimateElement
bool wxSVGAnimateElement::HasAttribute(const wxString& attrName)
{
  return wxSVGAnimationElement::HasAttribute(attrName);
}      

// wxSVGLangSpace
bool wxSVGLangSpace::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("xml:lang") ||
    attrName == wxT("xml:space");
}      

// wxSVGGlyphRefElement
bool wxSVGGlyphRefElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("glyphRef") ||
    attrName == wxT("format") ||
    attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("dx") ||
    attrName == wxT("dy") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGFESpotLightElement
bool wxSVGFESpotLightElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("z") ||
    attrName == wxT("pointsAtX") ||
    attrName == wxT("pointsAtY") ||
    attrName == wxT("pointsAtZ") ||
    attrName == wxT("specularExponent") ||
    attrName == wxT("limitingConeAngle") ||
    wxSVGElement::HasAttribute(attrName);
}      

// wxSVGAnimationElement
bool wxSVGAnimationElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName);
}      

// wxSVGAltGlyphDefElement
bool wxSVGAltGlyphDefElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFETurbulenceElement
bool wxSVGFETurbulenceElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("numOctaves") ||
    attrName == wxT("seed") ||
    attrName == wxT("stitchTiles") ||
    attrName == wxT("type") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGComponentTransferFunctionElement
bool wxSVGComponentTransferFunctionElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("type") ||
    attrName == wxT("tableValues") ||
    attrName == wxT("slope") ||
    attrName == wxT("intercept") ||
    attrName == wxT("amplitude") ||
    attrName == wxT("exponent") ||
    attrName == wxT("offset") ||
    wxSVGElement::HasAttribute(attrName);
}      

// wxSVGMPathElement
bool wxSVGMPathElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName);
}      

// wxSVGDefsElement
bool wxSVGDefsElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGRectElement
bool wxSVGRectElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    attrName == wxT("rx") ||
    attrName == wxT("ry") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGPolylineElement
bool wxSVGPolylineElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName) ||
    wxSVGAnimatedPoints::HasAttribute(attrName);
}      

// wxSVGColorProfileElement
bool wxSVGColorProfileElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("local") ||
    attrName == wxT("name") ||
    attrName == wxT("rendering-intent") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName);
}      

// wxSVGAnimatedPoints
bool wxSVGAnimatedPoints::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("points");
}      

// wxSVGCircleElement
bool wxSVGCircleElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("cx") ||
    attrName == wxT("cy") ||
    attrName == wxT("r") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGTextContentElement
bool wxSVGTextContentElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("textLength") ||
    attrName == wxT("lengthAdjust") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGUseElement
bool wxSVGUseElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGMissingGlyphElement
bool wxSVGMissingGlyphElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGImageElement
bool wxSVGImageElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    attrName == wxT("preserveAspectRatio") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGFEImageElement
bool wxSVGFEImageElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGTextPathElement
bool wxSVGTextPathElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("startOffset") ||
    attrName == wxT("method") ||
    attrName == wxT("spacing") ||
    wxSVGTextContentElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName);
}      

// wxSVGFEFloodElement
bool wxSVGFEFloodElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGFontElement
bool wxSVGFontElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGVideoElement
bool wxSVGVideoElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("x") ||
    attrName == wxT("y") ||
    attrName == wxT("width") ||
    attrName == wxT("height") ||
    attrName == wxT("preserveAspectRatio") ||
    attrName == wxT("begin") ||
    attrName == wxT("dur") ||
    attrName == wxT("clipBegin") ||
    attrName == wxT("clipEnd") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGRadialGradientElement
bool wxSVGRadialGradientElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("cx") ||
    attrName == wxT("cy") ||
    attrName == wxT("r") ||
    attrName == wxT("fx") ||
    attrName == wxT("fy") ||
    wxSVGGradientElement::HasAttribute(attrName);
}      

// wxSVGElement
bool wxSVGElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("id");
}      

// wxSVGTitleElement
bool wxSVGTitleElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGFEConvolveMatrixElement
bool wxSVGFEConvolveMatrixElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("kernelMatrix") ||
    attrName == wxT("divisor") ||
    attrName == wxT("bias") ||
    attrName == wxT("targetX") ||
    attrName == wxT("targetY") ||
    attrName == wxT("edgeMode") ||
    attrName == wxT("preserveAlpha") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGFEGaussianBlurElement
bool wxSVGFEGaussianBlurElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName) ||
    HasCustomAttribute(attrName);
}      

// wxSVGGlyphElement
bool wxSVGGlyphElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName);
}      

// wxSVGGElement
bool wxSVGGElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName) ||
    wxSVGTests::HasAttribute(attrName) ||
    wxSVGLangSpace::HasAttribute(attrName) ||
    wxSVGExternalResourcesRequired::HasAttribute(attrName) ||
    wxSVGStylable::HasAttribute(attrName) ||
    wxSVGTransformable::HasAttribute(attrName);
}      

// wxSVGAnimateColorElement
bool wxSVGAnimateColorElement::HasAttribute(const wxString& attrName)
{
  return wxSVGAnimationElement::HasAttribute(attrName);
}      

// wxSVGFEFuncGElement
bool wxSVGFEFuncGElement::HasAttribute(const wxString& attrName)
{
  return wxSVGComponentTransferFunctionElement::HasAttribute(attrName);
}      

// wxSVGAltGlyphItemElement
bool wxSVGAltGlyphItemElement::HasAttribute(const wxString& attrName)
{
  return wxSVGElement::HasAttribute(attrName);
}      

// wxSVGFESpecularLightingElement
bool wxSVGFESpecularLightingElement::HasAttribute(const wxString& attrName)
{
  return attrName == wxT("in") ||
    attrName == wxT("surfaceScale") ||
    attrName == wxT("specularConstant") ||
    attrName == wxT("specularExponent") ||
    wxSVGElement::HasAttribute(attrName) ||
    wxSVGFilterPrimitiveStandardAttributes::HasAttribute(attrName);
}      

// wxSVGTRefElement
bool wxSVGTRefElement::HasAttribute(const wxString& attrName)
{
  return wxSVGTextPositioningElement::HasAttribute(attrName) ||
    wxSVGURIReference::HasAttribute(attrName);
}      
