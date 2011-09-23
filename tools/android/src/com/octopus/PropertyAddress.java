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

package com.octopus;

import java.util.Arrays;

/**
 * @brief Address of a property.
 */
public class PropertyAddress {

	private PropertyAddress(PropertyAddress parent, byte data[]) {
		mParent = parent;
		mData = data;
	}

	private PropertyAddress mParent;

	public byte[] mData;

	public PropertyAddress() {
		mParent = null;
		mData = null;
	}

	public boolean isEqual(PropertyAddress addr) {
		return Arrays.equals(addr.mData, this.mData);
	}

	PropertyAddress getChild(byte addr) {
		byte[] data = new byte[mData.length + 1];
		System.arraycopy(mData, 0, data, 0, data.length);
		data[data.length - 1] = addr;
		return new PropertyAddress(this, data);
	}

	PropertyAddress getParent() {
		return mParent;
	}
}
