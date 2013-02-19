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

#ifndef SERVO_H_
#define SERVO_H_

#ifdef __AVR

#include <stdint.h>
#include "octopus/timer.h"

namespace octopus {

/**
 * @brief Servomotor driver using 1 GPIO of port D.
 */
class Servo: private Timer::Task {

    ////////////////////////////////////////////////////////////////////////////
    // Constants

private:
    /**
     * Pulse frequency, in microseconds.
     */
    static const uint16_t PULSE_PERIOD=20000;

    /**
     * Minimum pulse duration, in microseconds.
     */
    static const uint16_t MIN_PULSE_WIDTH=1000;

    /**
     * Maximum pulse duration, in microseconds.
     */
    static const uint16_t MAX_PULSE_WIDTH=2000;
    
    ////////////////////////////////////////////////////////////////////////////
    // Public attributes

public:
    /**
     * @brief Enable or disable the servomotor.
     */
    class PropertyServoEnabled : public PropertyBoolean {
    public:
        const char* getName() const {return "enabled";}
        const char* getDescription() {return "";}
        PropertyServoEnabled() : PropertyBoolean(false) {}
        using PropertyBoolean::operator=;
    } mEnabled;

    /**
     * @brief Current servomotor position.
     */
    class PropertyServoPosition : public PropertyU16 {
    public:
        const char* getName() const {return "position";}
        const char* getDescription() {return "Absolute position";}
        PropertyServoPosition() : PropertyU16(0) {}
        using PropertyU16::operator=;
    } mPosition;

    ////////////////////////////////////////////////////////////////////////////
    // Private attributes

private:
	char mPin;
    uint16_t mNextPulse;
    uint16_t mPulseWidth;

    ////////////////////////////////////////////////////////////////////////////
    // Constructor

public:
    /**
     * Constructor.
     *
     * @param[in]     pin    GPIO of port D on which the servomotor is plugged
     */
    Servo(char pin);

    ////////////////////////////////////////////////////////////////////////////
    // Private methods

private:
    // SystemTimer
    void onTimerLISR(unsigned short when, char what = 0);

    // Property
    const char* getName() const {return "servo";}
    const char* getDescription() {return "";}
    Property* getChild(uint8_t index);

    // PropertyListener
    /// @copydoc PropertyListener::onPropertyChanged()
    void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin);
};

} /* namespace octopus */

#endif /* __AVR */

#endif /* SERVO_H_ */
