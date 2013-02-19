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

#ifdef __AVR__

#include "octopus/imu3000.h"
#include "octopus/fatal.h"

namespace octopus {

typedef enum {
    WHO_AM_I = 0,
    X_OFFS_USRH = 12,
    X_OFFS_USRL = 13,
    Y_OFFS_USRH = 14,
    Y_OFFS_USRL = 15,
    Z_OFFS_USRH = 16,
    Z_OFFS_USRL = 17,
    FIFO_EN = 18,
    AUX_VDDIO = 19,
    AUX_SLV_ADDR = 20,
    SMPLRT_DIV = 21,
    DLPF_FS = 22,
    INT_CFG = 23,
    AUX_BURST_ADDR = 24,
    INT_STATUS = 26,
    TEMP_OUT_H = 27,
    TEMP_OUT_L = 28,
    GYRO_XOUT_H = 29,
    GYRO_XOUT_L = 30,
    GYRO_YOUT_H = 31,
    GYRO_YOUT_L = 32,
    GYRO_ZOUT_H = 33,
    GYRO_ZOUT_L = 34,
    AUX_XOUT_H = 35,
    AUX_XOUT_L = 36,
    AUX_YOUT_H = 37,
    AUX_YOUT_L = 38,
    AUX_ZOUT_H = 39,
    AUX_ZOUT_L = 40,
    DMP_REG1 = 53,
    DMP_REG2 = 54,
    DMP_REG3 = 55,
    DMP_REG4 = 56,
    DMP_REG5 = 57,
    FIFO_COUNTH = 58,
    FIFO_COUNTL = 59,
    FIFO_R = 60,
    USER_CTRL = 61,
    PWR_MGM = 62
} eIMU3000REG;

IMU3000::IMU3000(I2C* i2c, uint8_t address) :
    i2c(i2c),
    address(address)
{
}

void IMU3000::getInertialData(InertialDataListener* listener)
{
    if (listener) {
        this->listener = listener;
        i2c->write(address, buffer, 1, this);
    }
}

void IMU3000::onFinished(AsyncOperation *operation)
{
    I2C::Operation* op = static_cast<I2C::Operation*>(operation);

    if (op->result != I2C::Operation::RESULT_OK) {
        listener->onInertialError((uint8_t)op->result);
        return;
    }

    if (op->type == I2C::Operation::TYPE_WRITE) {
        if (op->size != 1) {
            listener->onInertialError(10);
            return;
        }
        // register address has been sent, start the reading
        i2c->read(address, (uint8_t*)&sensor_registers, sizeof(sensor_registers), this);
    } else {
        // register values have been read
        if (op->size != sizeof(sensor_registers)) {
            listener->onInertialError(11);
            return;
        }
        listener->onNewInertialData(
                    (int16_t)sensor_registers.gyro_XL | ((int16_t)sensor_registers.gyro_XH) << 8,
                    (int16_t)sensor_registers.gyro_YL | ((int16_t)sensor_registers.gyro_YH) << 8,
                    (int16_t)sensor_registers.gyro_ZL | ((int16_t)sensor_registers.gyro_ZH) << 8);
    }
}

} /* namespace octopus */

#endif /* __AVR__ */
