/*
 * Copyright 2012 Cedric Priscal
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

#include "wx_auto_grid_sizer.h"
#include <wx/log.h>
#include <math.h>

wxAutoGridSizer::wxAutoGridSizer(int vgap, int hgap) :
		wxGridSizer(0, 0, vgap, hgap)
{
}

//void wxAutoGridSizer::RecalcSizes() {
//	this->wxGridSizer::RecalcSizes();
//}

wxSize wxAutoGridSizer::CalcMin()
{
	// Compute the optimal number of columns to obtain square children
	wxSize size = GetSize();
	if ( (size.GetWidth() > 0) && (size.GetHeight() > 0) ) {
		size_t count = GetItemCount();
		size_t best_cols = 0;
		float best_ratio_delta = __FLT_MAX__;
		for (size_t cols = 1; cols <= count; cols++) {
			size_t rows = ceilf((float)count / (float)cols);
			float ratio = (size.GetWidth() * rows) / (size.GetHeight() * cols);
			float ratio_delta = fabs(ratio - 0.5);
			if (ratio_delta < best_ratio_delta) {
				// A better ratio has been found
				best_cols = cols;
				best_ratio_delta = ratio_delta;
			}
		}
		SetCols(best_cols);
		SetRows(0);
	}
	return this->wxGridSizer::CalcMin();
}
