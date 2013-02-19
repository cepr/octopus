/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IMU3000_H
#define IMU3000_H

#include "octopus/i2c.h"
#include "octopus/inertial_data_provider.h"

namespace octopus {

/**
 * \brief InvenSense IMU-3000 Motion Processing Unit
 */
class IMU3000 : private I2C::Operation::Callback, public InertialDataProvider {

public:
    /**
     * @brief Constructor
     *
     * IMU3000 driver constructor. You must specify the I2C bus to use and the device address.
     * If AD0 pin is connected to ground, I2C address is 0xD0.
     * If AD0 pin is connected to VCC, I2C address is 0xD2.
     *
     * @param i2c      I2C bus to use
     * @param address  I2C device address
     */
    IMU3000(I2C* i2c, uint8_t address = 0xd0);

public:
    // From I2C::Operation::Callback
    virtual void onFinished(AsyncOperation *operation);

    // From InertialDataProvider
	virtual void getInertialData(InertialDataListener* listener);

private:
    I2C* i2c;
    uint8_t address;
    InertialDataListener *listener;
    uint8_t buffer[2];
    struct {
        uint8_t gyro_XH;
        uint8_t gyro_XL;
        uint8_t gyro_YH;
        uint8_t gyro_YL;
        uint8_t gyro_ZH;
        uint8_t gyro_ZL;
    } sensor_registers;
};

} /* namespace octopus */

#endif // IMU3000_H
