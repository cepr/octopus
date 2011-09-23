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

#ifndef I2CDEVICE_H_
#define I2CDEVICE_H_

/**
 * \brief I2C device interface
 *
 * All I2C devices are inherited from this class.
 *
 * \ingroup INTERFACES
 */
class I2CDevice {

public:
    virtual unsigned char getAddress(void) = 0 ;
    virtual void onReceiveFinished(unsigned char received) = 0 ;
    virtual void onTransmitFinished(unsigned char transmitted) = 0 ;
    virtual void onDeviceNotResponding(void) = 0 ;
    virtual void onBusError(void) = 0 ;
    virtual void onBusBusy(void) = 0 ;
    virtual void onDeviceNack(void) = 0 ;
};

#endif // I2CDEVICE_H_
