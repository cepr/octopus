#ifndef PANELPROPERTIESIMPL_H
#define PANELPROPERTIESIMPL_H

#include "octopus_control_panel_gui.h" // Base class: PanelProperties
#include "Property.h"

class PanelPropertiesImpl : public PanelProperties {

public:
	PanelPropertiesImpl(wxWindow* parent, Property* prop);
	~PanelPropertiesImpl();
};

#endif // PANELPROPERTIESIMPL_H
