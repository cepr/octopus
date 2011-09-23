#include "panel_properties_impl.h"

static void recursiveAddProperty(wxTreeCtrl* tree, wxTreeItemId& id, Property* prop) {
    const char* name = prop->getName();
    wxTreeItemId newid = tree->AppendItem(id, wxString::FromAscii(name));
    // add children
    unsigned char index = 0;
    Property* child;
    while((child = prop->getChild(index)) != NULL) {
        recursiveAddProperty(tree, newid, child);
        index++;
    }
}

PanelPropertiesImpl::PanelPropertiesImpl(wxWindow* parent, Property* prop) : PanelProperties(parent)
{
    wxTreeItemId root = m_treeCtrl->AddRoot(wxT("/"));
    recursiveAddProperty(m_treeCtrl, root, prop);
}

PanelPropertiesImpl::~PanelPropertiesImpl()
{
}

