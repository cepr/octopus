//////////////////////////////////////////////////////////////////////////////
// Name:        SVGDocument_CreateElement.cpp
// Author:      Alex Thuering
// Copyright:   (c) 2005 Alex Thuering
// Licence:     wxWindows licence
// Notes:       generated by genSvgElement.py
//////////////////////////////////////////////////////////////////////////////

wxSvgXmlElement* wxSVGDocument::CreateElementNS(const wxString& namespaceURI,
  const wxString& qualifiedName)
{
  wxSVGElement* res = NULL;
  if (qualifiedName == wxT("feTurbulence"))
    res = new wxSVGFETurbulenceElement();
  else if (qualifiedName == wxT("feGaussianBlur"))
    res = new wxSVGFEGaussianBlurElement();
  else if (qualifiedName == wxT("feTile"))
    res = new wxSVGFETileElement();
  else if (qualifiedName == wxT("textPath"))
    res = new wxSVGTextPathElement();
  else if (qualifiedName == wxT("text"))
    res = new wxSVGTextElement();
  else if (qualifiedName == wxT("image"))
    res = new wxSVGImageElement();
  else if (qualifiedName == wxT("hkern"))
    res = new wxSVGHKernElement();
  else if (qualifiedName == wxT("missing-glyph"))
    res = new wxSVGMissingGlyphElement();
  else if (qualifiedName == wxT("font-face"))
    res = new wxSVGFontFaceElement();
  else if (qualifiedName == wxT("set"))
    res = new wxSVGSetElement();
  else if (qualifiedName == wxT("video"))
    res = new wxSVGVideoElement();
  else if (qualifiedName == wxT("animateMotion"))
    res = new wxSVGAnimateMotionElement();
  else if (qualifiedName == wxT("marker"))
    res = new wxSVGMarkerElement();
  else if (qualifiedName == wxT("altGlyph"))
    res = new wxSVGAltGlyphElement();
  else if (qualifiedName == wxT("animate"))
    res = new wxSVGAnimateElement();
  else if (qualifiedName == wxT("feBlend"))
    res = new wxSVGFEBlendElement();
  else if (qualifiedName == wxT("color-profile"))
    res = new wxSVGColorProfileElement();
  else if (qualifiedName == wxT("ellipse"))
    res = new wxSVGEllipseElement();
  else if (qualifiedName == wxT("mpath"))
    res = new wxSVGMPathElement();
  else if (qualifiedName == wxT("cursor"))
    res = new wxSVGCursorElement();
  else if (qualifiedName == wxT("use"))
    res = new wxSVGUseElement();
  else if (qualifiedName == wxT("font"))
    res = new wxSVGFontElement();
  else if (qualifiedName == wxT("polygon"))
    res = new wxSVGPolygonElement();
  else if (qualifiedName == wxT("title"))
    res = new wxSVGTitleElement();
  else if (qualifiedName == wxT("definition-src"))
    res = new wxSVGDefinitionSrcElement();
  else if (qualifiedName == wxT("tspan"))
    res = new wxSVGTSpanElement();
  else if (qualifiedName == wxT("font-face-uri"))
    res = new wxSVGFontFaceUriElement();
  else if (qualifiedName == wxT("feFlood"))
    res = new wxSVGFEFloodElement();
  else if (qualifiedName == wxT("tbreak"))
    res = new wxSVGTBreakElement();
  else if (qualifiedName == wxT("vkern"))
    res = new wxSVGVKernElement();
  else if (qualifiedName == wxT("font-face-src"))
    res = new wxSVGFontFaceSrcElement();
  else if (qualifiedName == wxT("feSpecularLighting"))
    res = new wxSVGFESpecularLightingElement();
  else if (qualifiedName == wxT("feColorMatrix"))
    res = new wxSVGFEColorMatrixElement();
  else if (qualifiedName == wxT("feImage"))
    res = new wxSVGFEImageElement();
  else if (qualifiedName == wxT("circle"))
    res = new wxSVGCircleElement();
  else if (qualifiedName == wxT("radialGradient"))
    res = new wxSVGRadialGradientElement();
  else if (qualifiedName == wxT("glyphRef"))
    res = new wxSVGGlyphRefElement();
  else if (qualifiedName == wxT("metadata"))
    res = new wxSVGMetadataElement();
  else if (qualifiedName == wxT("defs"))
    res = new wxSVGDefsElement();
  else if (qualifiedName == wxT("feFuncA"))
    res = new wxSVGFEFuncAElement();
  else if (qualifiedName == wxT("feFuncB"))
    res = new wxSVGFEFuncBElement();
  else if (qualifiedName == wxT("font-face-name"))
    res = new wxSVGFontFaceNameElement();
  else if (qualifiedName == wxT("fePointLight"))
    res = new wxSVGFEPointLightElement();
  else if (qualifiedName == wxT("feSpotLight"))
    res = new wxSVGFESpotLightElement();
  else if (qualifiedName == wxT("feFuncG"))
    res = new wxSVGFEFuncGElement();
  else if (qualifiedName == wxT("feConvolveMatrix"))
    res = new wxSVGFEConvolveMatrixElement();
  else if (qualifiedName == wxT("feDistantLight"))
    res = new wxSVGFEDistantLightElement();
  else if (qualifiedName == wxT("symbol"))
    res = new wxSVGSymbolElement();
  else if (qualifiedName == wxT("clipPath"))
    res = new wxSVGClipPathElement();
  else if (qualifiedName == wxT("stop"))
    res = new wxSVGStopElement();
  else if (qualifiedName == wxT("style"))
    res = new wxSVGStyleElement();
  else if (qualifiedName == wxT("animateColor"))
    res = new wxSVGAnimateColorElement();
  else if (qualifiedName == wxT("feDisplacementMap"))
    res = new wxSVGFEDisplacementMapElement();
  else if (qualifiedName == wxT("feFuncR"))
    res = new wxSVGFEFuncRElement();
  else if (qualifiedName == wxT("glyph"))
    res = new wxSVGGlyphElement();
  else if (qualifiedName == wxT("a"))
    res = new wxSVGAElement();
  else if (qualifiedName == wxT("feComposite"))
    res = new wxSVGFECompositeElement();
  else if (qualifiedName == wxT("foreignObject"))
    res = new wxSVGForeignObjectElement();
  else if (qualifiedName == wxT("path"))
    res = new wxSVGPathElement();
  else if (qualifiedName == wxT("line"))
    res = new wxSVGLineElement();
  else if (qualifiedName == wxT("rect"))
    res = new wxSVGRectElement();
  else if (qualifiedName == wxT("desc"))
    res = new wxSVGDescElement();
  else if (qualifiedName == wxT("altGlyphItem"))
    res = new wxSVGAltGlyphItemElement();
  else if (qualifiedName == wxT("feComponentTransfer"))
    res = new wxSVGFEComponentTransferElement();
  else if (qualifiedName == wxT("g"))
    res = new wxSVGGElement();
  else if (qualifiedName == wxT("feMorphology"))
    res = new wxSVGFEMorphologyElement();
  else if (qualifiedName == wxT("svg"))
    res = new wxSVGSVGElement();
  else if (qualifiedName == wxT("feDiffuseLighting"))
    res = new wxSVGFEDiffuseLightingElement();
  else if (qualifiedName == wxT("script"))
    res = new wxSVGScriptElement();
  else if (qualifiedName == wxT("mask"))
    res = new wxSVGMaskElement();
  else if (qualifiedName == wxT("altGlyphDef"))
    res = new wxSVGAltGlyphDefElement();
  else if (qualifiedName == wxT("tref"))
    res = new wxSVGTRefElement();
  else if (qualifiedName == wxT("filter"))
    res = new wxSVGFilterElement();
  else if (qualifiedName == wxT("font-face-format"))
    res = new wxSVGFontFaceFormatElement();
  else if (qualifiedName == wxT("switch"))
    res = new wxSVGSwitchElement();
  else if (qualifiedName == wxT("animateTransform"))
    res = new wxSVGAnimateTransformElement();
  else if (qualifiedName == wxT("linearGradient"))
    res = new wxSVGLinearGradientElement();
  else if (qualifiedName == wxT("feOffset"))
    res = new wxSVGFEOffsetElement();
  else if (qualifiedName == wxT("pattern"))
    res = new wxSVGPatternElement();
  else if (qualifiedName == wxT("feMerge"))
    res = new wxSVGFEMergeElement();
  else if (qualifiedName == wxT("polyline"))
    res = new wxSVGPolylineElement();
  else if (qualifiedName == wxT("view"))
    res = new wxSVGViewElement();
  else if (qualifiedName == wxT("feMergeNode"))
    res = new wxSVGFEMergeNodeElement();
  else 
	res = new wxSVGGElement();
  return res;
}
