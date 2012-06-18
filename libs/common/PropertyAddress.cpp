/*
 * Copyright 2010 Cedric Priscal
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

#include "PropertyAddress.h"

static char memcmp(const void *s1, const void *s2, char n) {
	const char* p1 = (const char*)s1;
	const char* p2 = (const char*)s2;
	while(n>0) {
		if ((*p1) != (*p2)) {
			return 1;
		}
		p1++;
		p2++;
		n--;
	}
	return 0;
}

static void memcpy(void *dst, const void* src, char n) {
	char* pdst = (char*)dst;
	const char* psrc = (const char*)src;
	while(n>0) {
		*pdst++ = *psrc++;
		n--;
	}
}

PropertyAddress::PropertyAddress() :
		mParent(),
		mData(0),
		mSize(0) {
}

bool PropertyAddress::isEqual(PropertyAddress *addr) {
	return ((addr != 0) &&
			(addr->mSize == mSize) &&
			(memcmp(addr->mData, mData, mSize) == 0)
			);
}

PropertyAddress::PropertyAddress(const PropertyAddress* parent, unsigned char* data, char size) :
	mParent(parent),
	mData(data),
	mSize(size) {
}

PropertyAddress* PropertyAddress::getChild(unsigned char addr) const {
	unsigned char* data = new unsigned char[mSize + 1];
	if (mSize > 0 ) {
		memcpy(data, mData, mSize);
	}
	data[(int)mSize] = addr;
	return new PropertyAddress(this, data, mSize+1);
}

const PropertyAddress* PropertyAddress::getParent() {
	return mParent;
}
