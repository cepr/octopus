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
#include "octopus/dev/usart/avr_usart.h"
#include "octopus/prop/property_record.h"
#include "octopus/dev/blink/blink.h"
#include "octopus/dev/compass/compass_listener.h"
#include "octopus/dev/compass/hmc6352.h"
#include "octopus/prop/property_data.h"

class Compass : public OctopusCommStack<AvrUsart, PropertyRecord>, public CompassListener {

private:
    // Inner classes
    class HeadingProperty: public PropertyU16 {
    public:
        HeadingProperty(Packet* packet) : PropertyU16(0, packet) {}
        const char* getName() const {
            return "Heading";
        }
        const char* getDescription() {
            return "Compass heading in 1/10 degrees, from 0 to 3600";
        }
        using PropertyData<unsigned short>::operator =;
    };

    // List of modules
    Blink                   mBlink;
    Hmc6352                 mCompass;
    HeadingProperty         mHeading;

public:
    // Constructor
    Compass() : // Modules
            mBlink(&mPacket),
            mCompass(),
            mHeading(&mPacket)
    {
    }

    // Property definition
    const char* getName() const {
        return "Compass";
    }

    const char* getDescription() {
        return "Compass robot";
    }

    void onStart() {
        mCompass.getHeading(this);
    }

    void onNewHeading(unsigned short heading) {
        mHeading = heading;
        mCompass.getHeading(this);
    }

    Property* getChild(unsigned char index) {
           switch(index) {
            case 0: return &mBlink;
            case 1: return &mHeading;
            default: return 0;
        }
    }
};

int main(void)
{
    static Compass c;
    c.onStart();
    Event::startLooper();
    return 0;
}

