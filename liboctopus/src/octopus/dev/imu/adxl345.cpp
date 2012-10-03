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

#include "adxl345.h"

Adxl345::Adxl345(Packet* packet) : PropertyRecord(packet) /*mRegDEVID(REG_DEVID)*/ {
}

Adxl345::~Adxl345() {
}

const char* Adxl345::getDescription() {
    return "Accelerometer";
}

const char* Adxl345::getName() const {
    return "ADXL345";
}
Property* Adxl345::getChild(unsigned char index) {
    switch(index) {
/*        case 0: return &mRegDEVID;
        case 1: return &mRegTHRESH_TAP;
        case 2: return &mRegOFSX;
        case 3: return &mRegOFSY;
        case 4: return &mRegOFSZ;
        case 5: return &mRegDUR;
        case 6: return &mRegLatent;
        case 7: return &mRegWindow;
        case 8: return &mRegTHRESH_ACT;
        case 9: return mRegTHRESH_INACT;
        case 10: return mRegTIME_INACT;
        case 11: return mRegACT_INACT_CTL;
        case 12: return mRegTHRESH_FF;
        case 13: return mRegTIME_FF;
        case 14: return mRegTAP_AXES;
        case 15: return mRegACT_TAP_STATUS;
        case 16: return mRegBW_RATE;
        case 17: return mRegPOWER_CTL;
        case 18: return mRegINT_ENABLE;
        case 19: return mRegINT_MAP;
        case 20: return mRegINT_SOURCE;
        case 21: return mRegDATA_FORMAT;
        case 22: return mRegDATAX0;
        case 23: return mRegDATAX1;
        case 24: return mRegDATAY0;
        case 25: return mRegDATAY1;
        case 26: return mRegDATAZ0;
        case 27: return mRegDATAZ1;
        case 28: return mRegFIFO_CTL;
        case 29: return mRegFIFO_STATUS;*/
        default: return 0;
    }
}

PROPERTY_TYPE Adxl345::getType() {
	return PROPERTY_TYPE_VOID;
}
