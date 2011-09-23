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

#ifndef ADXL345REGISTER_H
#define ADXL345REGISTER_H

#include "property_data.h" // Base class: PropertyU8

/**
 * List of ADXL345 registers extracted from datasheet.
 */
typedef enum {
    REG_DEVID           = 0x00, /**< Device ID. */
    REG_THRESH_TAP      = 0x1D, /**< Tap threshold. */
    REG_OFSX            = 0x1E, /**< X-axis offset. */
    REG_OFSY            = 0x1F, /**< Y-axis offset. */
    REG_OFSZ            = 0x20, /**< Z-axis offset. */
    REG_DUR             = 0x21, /**< Tap duration. */
    REG_Latent          = 0x22, /**< Tap latency. */
    REG_Window          = 0x23, /**< Tap window. */
    REG_THRESH_ACT      = 0x24, /**< Activity threshold. */
    REG_THRESH_INACT    = 0x25, /**< Inactivity threshold. */
    REG_TIME_INACT      = 0x26, /**< Inactivity time. */
    REG_ACT_INACT_CTL   = 0x27, /**< Axis enable control for activity and inactivity detection. */
    REG_THRESH_FF       = 0x28, /**< Free-fall threshold. */
    REG_TIME_FF         = 0x29, /**< Free-fall time. */
    REG_TAP_AXES        = 0x2A, /**< Axis control for tap/double tap. */
    REG_ACT_TAP_STATUS  = 0x2B, /**< Source of tap/double tap. */
    REG_BW_RATE         = 0x2C, /**< Data rate and power mode control.*/
    REG_POWER_CTL       = 0x2D, /**< Power-saving features control. */
    REG_INT_ENABLE      = 0x2E, /**< Interrupt enable control. */
    REG_INT_MAP         = 0x2F, /**< Interrupt mapping control. */
    REG_INT_SOURCE      = 0x30, /**< Source of interrupts. */
    REG_DATA_FORMAT     = 0x31, /**< Data format control. */
    REG_DATAX0          = 0x32, /**< X-Axis Data 0. */
    REG_DATAX1          = 0x33, /**< X-Axis Data 1. */
    REG_DATAY0          = 0x34, /**< Y-Axis Data 0. */
    REG_DATAY1          = 0x35, /**< Y-Axis Data 1. */
    REG_DATAZ0          = 0x36, /**< Z-Axis Data 0. */
    REG_DATAZ1          = 0x37, /**< Z-Axis Data 1. */
    REG_FIFO_CTL        = 0x38, /**< FIFO control. */
    REG_FIFO_STATUS     = 0x39, /**< FIFO status. */
} ADXL345_REGISTER;

class Adxl345Register : public PropertyU8 {

public:

	Adxl345Register(ADXL345_REGISTER reg);
	~Adxl345Register();
    const char* getDescription();

private:
    ADXL345_REGISTER mReg;
};

#endif // ADXL345REGISTER_H
