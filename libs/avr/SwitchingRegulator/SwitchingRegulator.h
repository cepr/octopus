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

#ifndef SWITCHINGREGULATOR_H_
#define SWITCHINGREGULATOR_H_

#include "ADC/AnalogChannel.h"

/**
 * This class provides a Boost Switching Regulator. It regulates the voltage
 * by modifying the duty cycle of a PWM signal.
 * This signal should drive the transistor of a boost power supply.
 * (http://en.wikipedia.org/wiki/Boost_converter)
 *
 * You should put some hardware over-voltage protection, since a
 * crash of the microcontroller could lead to regulation problems.
 */
class SwitchingRegulator : private AnalogChannel {
private:
	bool mEnabled;
	unsigned short mVoltage;
public:
	SwitchingRegulator(CHANNEL channel, VREF vref, unsigned short voltage);
	void setEnable(bool enable);
	void setVoltage(unsigned short voltage);
	void onNewMeasure(unsigned short value);
};

#endif /* SWITCHINGREGULATOR_H_ */
