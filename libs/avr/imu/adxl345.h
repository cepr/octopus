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

#ifndef ADXL345_H
#define ADXL345_H

#include "i2c_device.h" // Base class: I2CDevice
#include "Property.h"
#include "adxl345_register.h"

class Adxl345 : public I2CDevice, Property {
    Property* getChild(unsigned char index);
    PROPERTY_TYPE getType();
    const char* getDescription();
    const char* getName();

public:
    Adxl345();
    ~Adxl345();

    /**
     * \brief
     * \param byte
     * \return
     */
    bool onByteRead(unsigned char byte);

    /**
     * \brief
     * \param success
     * \return
     */
    bool onWriteFinished(bool success);

private:
/*    Adxl345Register mRegDEVID;
    Adxl345Register mRegTHRESH_TAP;
    Adxl345Register mRegOFSX;
    Adxl345Register mRegOFSY;
    Adxl345Register mRegOFSZ;
    Adxl345Register mRegDUR;
    Adxl345Register mRegLatent;
    Adxl345Register mRegWindow;
    Adxl345Register mRegTHRESH_ACT;
    Adxl345Register mRegTHRESH_INACT;
    Adxl345Register mRegTIME_INACT;
    Adxl345Register mRegACT_INACT_CTL;
    Adxl345Register mRegTHRESH_FF;
    Adxl345Register mRegTIME_FF;
    Adxl345Register mRegTAP_AXES;
    Adxl345Register mRegACT_TAP_STATUS;
    Adxl345Register mRegBW_RATE;
    Adxl345Register mRegPOWER_CTL;
    Adxl345Register mRegINT_ENABLE;
    Adxl345Register mRegINT_MAP;
    Adxl345Register mRegINT_SOURCE;
    Adxl345Register mRegDATA_FORMAT;
    Adxl345Register mRegDATAX0;
    Adxl345Register mRegDATAX1;
    Adxl345Register mRegDATAY0;
    Adxl345Register mRegDATAY1;
    Adxl345Register mRegDATAZ0;
    Adxl345Register mRegDATAZ1;
    Adxl345Register mRegFIFO_CTL;
    Adxl345Register mRegFIFO_STATUS;*/

};

#endif // ADXL345_H
