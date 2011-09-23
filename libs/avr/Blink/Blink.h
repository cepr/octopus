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

#ifndef BLINK_H_
#define BLINK_H_

#include "Timer/timer_listener.h"
#include "property_record.h"
#include "property_data.h"

/**
 * @brief Blinking LED.
 *
 * Use this class to make the Arduino onboard LED
 * (GPIO B5 of ATMEGA328) blink at a 2 seconds period.
 */
class Blink: public PropertyRecord, public PropertyListener {

private:
    char mRequestId;

	class Timer: public TimerListener {
	public:
		Timer(Blink *parent);
		void onTimer(char what);
	private:
		Blink* mParent;
		unsigned short mTimeMs;
	};
	Timer mTimer;

public:
    /**
     * @brief Constructor.
     *
     * Blinking is not activated in this constructor.
     * @see setEnabled()
     */
    Blink();

    class PropertyBlinkEnabled : public PropertyBoolean {
    private:
        const char* getName() {return "enabled";}
        const char* getDescription() {return "";}
        PropertyListener* mListener;
        void setValue(const PROPERTY_VALUE & value) {
            operator=(value.boolean);
        }
    public:
        PropertyBlinkEnabled(PropertyListener* listener) : PropertyBoolean(), mListener(listener) {};
        bool operator=(bool value) {
            if (value != mValue) {
                mValue = value;
                if (mListener) {
                    mListener->onPropertyChanged(this);
                }
            }
            return value;
        }
    };

    /**
     * @brief Enable or disable the blinking.
     */
    PropertyBlinkEnabled mEnabled;

private:
    // PropertyRecord pure virtual functions
	const char* getName() { return "Blink"; }
	const char* getDescription() { return "LED blinking"; }
    Property* getChild(unsigned char index);

    // PropertyListener implementation
    void onPropertyChanged(class Property* prop);
};

#endif /* BLINK_H_ */
