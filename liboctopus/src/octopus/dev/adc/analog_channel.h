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

#ifndef ANALOGCHANNEL_H_
#define ANALOGCHANNEL_H_

#ifdef __AVR

#include <avr/io.h>
#include "octopus/dev/timer/application_timer.h"

/**
 * \brief Enumeration of the available analog channels.
 *
 * \see AnalogChannel
 */
typedef enum {
    CHANNEL_ADC0=0,
    CHANNEL_ADC1=1,
    CHANNEL_ADC2=2,
    CHANNEL_ADC3=3,
    CHANNEL_ADC4=4,
    CHANNEL_ADC5=5,
    CHANNEL_ADC6=6,
    CHANNEL_ADC7=7,
    CHANNEL_ADC8=8,
    CHANNEL_VBG=14,
    CHANNEL_GND=15
} CHANNEL;

/**
 * \brief Enumeration of the available voltage references.
 *
 * \see AnalogChannel
 */
typedef enum {
    VREF_AVCC = _BV(REFS0),           //!< VREF_AVCC
    VREF_VBG = _BV(REFS1) | _BV(REFS0)//!< VREF_VBG
} VREF;

/**
 * \brief Base class for one channel of the AVR internal ADC.
 *
 * In order to use this class, you have to inherit this
 * abstract class with your own, and override the method
 * onNewMeasure() to get the ADC measures.
 *
 * \ingroup AVR_ADC
 */
class AnalogChannel {

private:
    unsigned short mPeriod;
    unsigned short mMs;
    void onTimer(char what, unsigned short when);

	class Timer : public ApplicationTimer {
	public:
		Timer(AnalogChannel* parent);
	private:
		AnalogChannel* mParent;
		void onTimer();
	};
	Timer mTimer;

public:
    CHANNEL mChannel;
    VREF mVref;

    /**
     * \brief Constructor
     *
     * \param[in] channel AVR ADC channel
     * \param[in] vref    Voltage reference
     */
    AnalogChannel(CHANNEL channel, VREF vref);

    /**
     * \brief Trigger a single ADC conversion
     *
     * This method is non-blocking, onNewMeasure() will
     * be called when a the result is available.
     */
    void startOneShot();

    /**
     * \brief Trigger periodic ADC conversions
     *
     * This method is non-blocking, onNewMeasure() will
     * be called each time a the result is available.
     *
     * \param[in] period Refresh period in milliseconds
     */
    void startPeriodic(unsigned short period);

    /**
     * \brief Stops any ADC background operation
     */
    void stop();

    /**
     * \brief Method to override in order to get the ADC results.
     *
     * \param[in] value Result of the ADC conversion
     */
    virtual void onNewMeasure(unsigned short value) = 0;
};

#endif /* __AVR */

#endif /* ANALOGCHANNEL_H_ */
