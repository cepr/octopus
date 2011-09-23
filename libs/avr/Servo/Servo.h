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

#include "Handler.h"
#include "Timer/timer_listener.h"
#include "property_record.h"
#include "property_data.h"
#include "Module.h"

class PropertyServoPosition : public PropertyU16 {

protected:
    const char* getName() {return "position";}
    const char* getDescription() {return "Absolute position between 1310 and 2100.";}
    void setValue(const PROPERTY_VALUE & value) {
        operator=(value.u16);
    }

public:
    /**
     * @brief Constructor.
     * The initial position of the servomotor is set to SERVO_DEFAULT_PULSE.
     */
    PropertyServoPosition();

    /**
     * @brief Minimum pulse duration, in microseconds.
     */
    static const unsigned short MIN=1310;

    /**
     * @brief Maximum pulse duration, in microseconds.
     */
    static const unsigned short MAX=2100;

    /**
     * @brief Default pulse duration, in microseconds.
     *
     * This value is used in case you call @a setEnabled() without a prior call
     * to @a go() with a location.
     */
    static const unsigned short DEFAULT=((MIN + MAX) / 2);

    unsigned short operator= (unsigned short value) {
    	if (value < MIN) {
    		return mValue = MIN;
    	} else if (value > MAX) {
    		return mValue = MAX;
    	} else {
    		return mValue = value;
    	}
	}
};

class PropertyServoEnabled : public PropertyBoolean {
private:
    const char* getName() {return "enabled";}
    const char* getDescription() {return "";}
    PropertyListener* mListener;
    void setValue(const PROPERTY_VALUE & value) {
        if (mValue != value.boolean) {
            mValue = value.boolean;
            if (mListener) {
                mListener->onPropertyChanged(this);
            }
        }
    }
public:
    PropertyServoEnabled(PropertyListener* listener) : PropertyBoolean(), mListener(listener) {}
};

/**
 * @brief Servomotor driver using 1 GPIO of port D.
 */
class Servo: private TimerListener, public PropertyRecord, public PropertyListener, public Module {

private:
	char mPin;
    void onTimer(char what, unsigned short when);

protected:
    virtual const char* getName() {return "servo";}
    virtual const char* getDescription() {return "";}
	Property* getChild(unsigned char index);

public:
    /**
     * @brief Constructor.
     *
     * @param pin GPIO of port D on which the servomotor is plugged
     */
    Servo(char pin);

    /**
     * @brief Enable or disable the servomotor.
     */
	PropertyServoEnabled mEnabled;

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
    void go(unsigned short position);

    /**
     * @brief Current servomotor position.
     */
    PropertyServoPosition mPosition;

    /**
     * @copydoc PropertyListener::onPropertyChanged()
     */
    void onPropertyChanged(Property* prop);
};

#endif /* SERVO_H_ */
