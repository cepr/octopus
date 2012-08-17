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

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include "Handler.h"
#include "Timer/system_timer.h"
#include "property_record.h"
#include "property_data.h"
#include "Module.h"


/**
 * @brief Servomotor driver using 1 GPIO of port D.
 */
class Servo: private SystemTimer, public PropertyRecord, public PropertyListener, public Module {

    // Inner classes

public:
    /**
     * @brief Enable or disable the servomotor.
     */
    class PropertyServoEnabled : public PropertyBoolean {
    private:
        const char* getName() const {return "enabled";}
        const char* getDescription() {return "";}
        PropertyListener* mListener;
        void setValue(const PROPERTY_VALUE & value) {
            if (mValue != value.boolean) {
                mValue = value.boolean;
                if (mListener) {
                    mListener->onPropertyChanged(this, PROPERTY_INFO_VALUE);
                }
            }
        }
    public:
        PropertyServoEnabled(PropertyListener* listener, Packet* packet) : PropertyBoolean(false, packet), mListener(listener) {}
    } mEnabled;

    /**
     * @brief Current servomotor position.
     */
    class PropertyServoPosition : public PropertyU16 {

    protected:
        const char* getName() const {return "position";}
        const char* getDescription() {return "Absolute position between 1310 and 2100.";}
        void setValue(const PROPERTY_VALUE & value) {
            operator=(value.u16);
        }

    public:
        /**
         * Constructor.
         *
         * The initial position of the servomotor is set to SERVO_DEFAULT_PULSE.
         */
        PropertyServoPosition(Packet* packet);

        /**
         * Minimum pulse duration, in microseconds.
         */
        static const uint16_t MIN=1000;

        /**
         * Maximum pulse duration, in microseconds.
         */
        static const uint16_t MAX=2000;

        /**
         * Default pulse duration, in microseconds.
         *
         * This value is used in case you call @a setEnabled() without a prior call
         * to @a go() with a location.
         */
        static const uint16_t DEFAULT=MIN;

        uint16_t mPulseWidth;

        uint16_t operator =(uint16_t value) {
            mPulseWidth = MIN + (uint16_t)(((uint32_t)(MAX-MIN) * (uint32_t)value) >> 16);
            return PropertyU16::operator=(value);
        }
    } mPosition;

private:
    /**
     * Pulse frequency, in microseconds.
     */
    static const uint16_t PERIOD=20000;

	char mPin;
    void onTimerLISR(unsigned short when, char what = 0);
    uint16_t mNextPulse;

protected:
    virtual const char* getName() const {return "servo";}
    virtual const char* getDescription() {return "";}
	Property* getChild(uint8_t index);

public:
    /**
     * @brief Constructor.
     *
     * @param[in]     pin    GPIO of port D on which the servomotor is plugged
	 * @param[in,out] packet Packet class to report modifications to
     */
    Servo(char pin, Packet* packet);

    /**
     * @brief Move the servomotor to the specified location.
     *
     * This method is non blocking. Do not forget to enable the servomotor with @a setEnabled().
     *
     * @param position [in] Target position, between @a SERVO_MIN_PULSE and @a SERVO_MAX_PULSE.
     *
     * @see SERVO_MIN_PULSE
     * @see SERVO_MAX_PULSE
     */
    void go(uint16_t position);

    /**
     * @copydoc PropertyListener::onPropertyChanged()
     */
    void onPropertyChanged(Property* prop, PROPERTY_INFO what);
};

#endif /* SERVO_H_ */
