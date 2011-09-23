/*
 * Copyright 2010-2011 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "main_frame_impl.h"
#include "panel_properties_impl.h"
#include "dashboard_panel.h"

MainFrameImpl::MainFrameImpl() : MainFrame(NULL, wxID_ANY, wxT("Octopus Control Panel")), mRootProperty(NULL)
{
    // Add a properties panel for device on serial port
    //PanelPropertiesImpl *panel1 = new PanelPropertiesImpl(m_auinotebook2, &mRootProperty);
    DashboardPanel *panel2 = new DashboardPanel(m_auinotebook2, &mRootProperty);
    //m_auinotebook2->AddPage(panel1, wxT("Tree view"));
    m_auinotebook2->AddPage(panel2, wxT("Dashboard view"));
}

MainFrameImpl::~MainFrameImpl()
{
}

