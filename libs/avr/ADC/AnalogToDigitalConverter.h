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

#ifndef ANALOGTODIGITALCONVERTER_H_
#define ANALOGTODIGITALCONVERTER_H_

#include "Timer/system_timer.h"
#include "event.h"

#define MAX_PENDING_CONVERTIONS 8

/**
 * \brief AVR internal ADC driver.
 *
 * This class is a singleton, use getInstance() to retrieve it.
 * You should not use this class directly, please consider using the class \ref AnalogChannel instead.
 *
 * \ingroup AVR_ADC
 */
class AnalogToDigitalConverter : public Event {

private:
    class AnalogChannel* mList[MAX_PENDING_CONVERTIONS];
    int mPutIndex;
    int mGetIndex;
    char mCount;
    void programNextADC();
    bool mRunning;
    AnalogToDigitalConverter();

	class Timer : public SystemTimer {
	public:
		Timer(AnalogToDigitalConverter *parent);
	private:
		AnalogToDigitalConverter* mParent;
		void onTimerLISR(unsigned short when, char what);
	};
	Timer mTimer;

public:

    /**
     * \brief ADC conversion complete
     *
     * \param[in] what Not used.
     */
    void onEvent(char what);

    /**
     * \brief Returns the unique instance of \ref AnalogToDigitalConverter
     *
     * \return A \ref AnalogToDigitalConverter class
     */
    static AnalogToDigitalConverter* getInstance();

    /**
     * \brief Start an ADC reading on the specified channel.
     *
     * This method should be called only from an AnalogChannel.
     *
     * \param channel [in] Analog channel to read.
     *
     * \see AnalogChannel::startOneShot()
     * \see AnalogChannel::startPeriodic()
     */
    void startADC(AnalogChannel *channel);
};

#endif /* ANALOGTODIGITALCONVERTER_H_ */
