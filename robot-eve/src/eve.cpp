/*
 * Copyright 2010-2012 Cedric Priscal
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

#include "octopus/prop/octopus_comm_stack.h"
#include "octopus/prop/property_record.h"
#include "octopus/dev/blink/blink.h"
#include "octopus/dev/stepper/stepper_4c.h"
#include "octopus/dev/stepper/stepper_4d.h"
#include "octopus/dev/servo/servo.h"
#include "octopus/util/fatal.h"
#include "octopus/event/looper.h"

using namespace octopus;

/**
 * @brief Ground robot powered by two steppers, and one servomotor.
 */
class Eve : public StepperListener, public OctopusCommStack<AvrUsart, PropertyRecord> {

private:
    // List of modules
    class LeftStepper: public Stepper4C {
    public:
        LeftStepper() : Stepper4C(PORTC0, PORTC1, PORTC3, PORTC2) {}
        const char* getName() const { return "LeftStepper"; }
        const char* getDescription() { return "Left step motor"; }
    } mLeft;

    class RightStepper: public Stepper4D {
    public:
        RightStepper() : Stepper4D(PORTD3, PORTD2, PORTD4, PORTD5) {}
        const char* getName() const { return "RightStepper"; }
        const char* getDescription() { return "Right step motor"; }
    } mRight;

    Blink                   mBlink;
    Servo                   mServo;

public:
    /**
     * @brief Constructor.
     */
    Eve() :
            // Modules
            mLeft(&mPacket),
            mRight(&mPacket),
            mBlink(&mPacket),
            mServo(PORTD7, &mPacket)
    {
    }

    // Property definition
    PROPERTY_TYPE getType() { return PROPERTY_TYPE_VOID; }
    const char* getName() const { return "Eve"; }
    const char* getDescription() { return "Ground robot"; }

    /**
     * \copydoc StepperListener::onStepperStopped()
     */
    void onStepperStopped(Stepper *stepper, short location) {
    }

    /**
     * \copydoc Property::getChild()
     */
    Property* getChild(unsigned char index) {
        switch(index) {
        case 0: return &mBlink;
        case 1: return &mLeft;
        case 2: return &mRight;
        case 3: return &mServo;
        default: return 0;
        }
    }
};


int main(void)
{
    static Eve eve;
    main_looper.run();
    return 0;
}
