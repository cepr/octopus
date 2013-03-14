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

#ifndef AVRADC_H_
#define AVRADC_H_

#ifdef __AVR__

#include "octopus/async_operation.h"
#include "octopus/list.h"

namespace octopus {

/**
 * \brief AVR internal ADC driver.
 *
 * This class is a singleton, use getInstance() to retrieve it.
 * You should not use this class directly, please consider using the class \ref AnalogChannel instead.
 *
 * \ingroup AVR_ADC
 */
class AvrADC : public AsyncOperation {

public:
    /**
     * \brief Base class for one channel of the AVR internal ADC.
     *
     * In order to use this class, you have to inherit this
     * abstract class with your own, and override the method
     * onNewMeasure() to get the ADC measures.
     *
     * \ingroup AVR_ADC
     */
    class Channel {

    public:
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
         * \brief Constructor
         *
         * \param[in] channel AVR ADC channel
         * \param[in] vref    Voltage reference
         */
        Channel(CHANNEL channel, VREF vref);

        /**
         * \brief Trigger a single ADC conversion
         *
         * This method is non-blocking, onNewMeasure() will
         * be called when a the result is available.
         */
        void start() {
            AvrADC::instance.start(this);
        }

        /**
         * \brief Method to override in order to get the ADC results.
         *
         * \param[in] value Result of the ADC conversion
         */
        virtual void onNewMeasure(uint16_t value) = 0;

    private:
        // For List<Channel>
        friend class List<Channel>;
        Channel *prev;
        Channel *next;

        friend class AvrADC;
        CHANNEL channel;
        VREF vref;
    };

    /**
     * \brief Instance of the AnalogToDigitalConverter
     */
    static AvrADC instance;

private:
    // Start an ADC reading on the specified channel.
    friend class Channel;
    void start(Channel *channel);

    // Private constructor
    AvrADC();

    // List of pending ADC measurements
    List<Channel> list;

    // Program the next ADC in the list
    void programNextADC();

    // ADC conversion complete
    void onFinished();
};

} /* namespace octopus */

#endif /* __AVR__ */

#endif /* AVRADC_H_ */
