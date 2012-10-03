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

#ifndef HMC6352_H
#define HMC6352_H

#include "compass_provider.h" // Base class: CompassProvider
#include "i2c_device.h"
#include "i2c_driver.h"
#include "Timer/application_timer.h"

/**
 * \defgroup HMC6352 Honeywell HMC6252 Digital Compass
 * \ingroup SENSORS_LIBS
 * \{
 */

/**
 * \brief CompassProvider implementation for Honeywell HMC6352 digital compass.
 *
 * This chip is an I2C digital compass.
 */
class Hmc6352 : public CompassProvider, private I2CDevice, private ApplicationTimer {

public:

    /**
     * \brief Constructor
     */
    Hmc6352();

    /*
     * see CompassProvider::getHeading()
     */
    void getHeading(CompassListener* listener);

    void startCalibration();
    void stopCalibration();
    
private:
    unsigned char getAddress(void);
    void onBusBusy(void);
    void onBusError(void);
    void onDeviceNack(void);
    void onDeviceNotResponding(void);
    void onReceiveFinished(unsigned char received);
    void onTransmitFinished(unsigned char transmitted);
    void onTimer(char what);

    unsigned char mGetHeadingBuffer[2];
    I2CTransfer mGetHeadingTransfer;
    unsigned char mStartCalibrationBuffer[1];
    I2CTransfer mStartCalibrationTransfer;
    unsigned char mStopCalibrationBuffer[1];
    I2CTransfer mStopCalibrationTransfer;
    CompassListener *mListener;
};

/**
 * \}
 */

#endif // HMC6352_H
