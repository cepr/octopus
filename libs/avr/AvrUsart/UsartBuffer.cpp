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

#include "UsartBuffer.h"

UsartBuffer::UsartBuffer() {
    mCount = 0;
    mPutIndex = 0;
    mGetIndex = 0;
}

bool UsartBuffer::PutChar(unsigned char b) {
    if (mCount < sizeof(mBuffer)) {
        mBuffer[mPutIndex++] = b;
        if (mPutIndex == sizeof(mBuffer)) {
            mPutIndex = 0;
        }
        mCount++;
        return true;
    }
    return false;
}

unsigned char UsartBuffer::GetChar() {
    unsigned char c = mBuffer[mGetIndex++];
    if (mGetIndex == sizeof(mBuffer)) {
        mGetIndex = 0;
    }
    mCount--;
    return c;
}

void UsartBuffer::reset(void)
{
    mCount = 0;
    mPutIndex = 0;
    mGetIndex = 0;
}
