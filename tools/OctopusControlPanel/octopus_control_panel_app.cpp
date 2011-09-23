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

#include "octopus_control_panel_app.h"
#include "main_frame_impl.h"
#include "panel_properties_impl.h"

IMPLEMENT_APP(wxOctopusControlPanelApp);

wxOctopusControlPanelApp::wxOctopusControlPanelApp()
{
}

bool wxOctopusControlPanelApp::OnInit()
{
	// create a new frame and set it as the top most application window
    MainFrameImpl *frame = new MainFrameImpl();
    SetTopWindow( frame );

	// show main frame
    GetTopWindow()->Show();

	// enter the application's main loop
    return true;
}
