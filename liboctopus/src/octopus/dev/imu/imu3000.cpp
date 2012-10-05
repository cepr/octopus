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

#ifdef __AVR

#include "imu3000.h"
#include "octopus/dev/i2c/avr_two_wire_interface.h"
#include "octopus/util/fatal.h"

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

IMU3000::IMU3000()
{
}

unsigned char IMU3000::getAddress(void)
{
    // If AD0 pin is connected to ground, I2C address is 0xD0
    // If AD0 pin is connected to vcc, I2C address is 0xD2
    return 0xD0;
}

void IMU3000::getInertialData(InertialDataListener* listener)
{
    mListener = listener;
    mI2CTransfer[0].device = this;
    mI2CTransfer[0].type = I2C_TRANSMIT;
    mI2CTransfer[0].buffer = mI2CBuffer;
    mI2CBuffer[0] = GYRO_XOUT_H;
    mI2CTransfer[0].size = 1;
    mI2CTransfer[0].next = &mI2CTransfer[1];
    mI2CTransfer[1].device = this;
    mI2CTransfer[1].type = I2C_RECEIVE;
    mI2CTransfer[1].buffer = (unsigned char*)&mSensorRegisters;
    mI2CTransfer[1].size = sizeof(mSensorRegisters);
    mI2CTransfer[1].next = 0;
    AvrTwoWireInterface::getInstance().commit(mI2CTransfer);
}

void IMU3000::onBusBusy(void)
{
    fatal(FATAL_DEBUG);
}

void IMU3000::onBusError(void)
{
    fatal(FATAL_DEBUG);
}

void IMU3000::onDeviceNack(void)
{
    fatal(FATAL_DEBUG);
}

void IMU3000::onDeviceNotResponding(void)
{
    fatal(FATAL_DEBUG);
}

void IMU3000::onReceiveFinished(unsigned char received)
{
    if (received != sizeof(mSensorRegisters)) {
        fatal(FATAL_DEBUG);
    } else {
        // We must rebuild s16 values
        union {
            short s16;
            unsigned char u8[2];
        } gyrox;
        union {
            short s16;
            unsigned char u8[2];
        } gyroy;
        union {
            short s16;
            unsigned char u8[2];
        } gyroz;
        gyrox.u8[0] = mSensorRegisters.mGyroXL;
        gyrox.u8[1] = mSensorRegisters.mGyroXH;
        gyroy.u8[0] = mSensorRegisters.mGyroYL;
        gyroy.u8[1] = mSensorRegisters.mGyroYH;
        gyroz.u8[0] = mSensorRegisters.mGyroZL;
        gyroz.u8[1] = mSensorRegisters.mGyroZH;
        mListener->onNewInertialData(gyrox.s16, gyroy.s16, gyroz.s16);
    }
}

void IMU3000::onTransmitFinished(unsigned char transmitted)
{
}

#endif /* __AVR */
