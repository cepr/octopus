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

#ifndef IMU3000_H
#define IMU3000_H

#include "octopus/dev/i2c/i2c_device.h" // Base class: I2CDevice
#include "octopus/dev/i2c/i2c_driver.h"
#include "inertial_data_provider.h" // Base class: InertialDataProvider

/**
 * \brief InvenSense IMU-3000 Motion Processing Unit
 */
class IMU3000 : private I2CDevice, public InertialDataProvider {

public:
	IMU3000();

public:
	virtual unsigned char getAddress(void);
	virtual void getInertialData(InertialDataListener* listener);
	virtual void onBusBusy(void);
	virtual void onBusError(void);
	virtual void onDeviceNack(void);
	virtual void onDeviceNotResponding(void);
	virtual void onReceiveFinished(unsigned char received);
	virtual void onTransmitFinished(unsigned char transmitted);

private:
    InertialDataListener *mListener;
    I2CTransfer mI2CTransfer[2];
    unsigned char mI2CBuffer[2];
    struct {
        unsigned char mGyroXH;
        unsigned char mGyroXL;
        unsigned char mGyroYH;
        unsigned char mGyroYL;
        unsigned char mGyroZH;
        unsigned char mGyroZL;
    } mSensorRegisters;
};

#endif // IMU3000_H
