/*
 * Copyright 2012 Cedric Priscal
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

#include "Robot/Robot.h"
#include "octopus_comm_stack.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "Range/lv_max_sonar_ez.h"
#include "property_data.h"

class RangeFinder : public Robot, public OctopusCommStack<AvrUsart, PropertyRecord>, public RangeListener {

private:
    // List of modules
    class RangeProperty: public PropertyU16 {
    public:
        RangeProperty(Packet* packet) : PropertyU16(0, packet) {}
        const char* getName() const { return "Range"; }
        const char* getDescription() { return "Range in centimeters"; }
        using PropertyU16::operator =;
    } mRange;

    Blink                   mBlink;
    LVMaxSonarEZ            mRangeFinder;

public:
    // Constructor
    RangeFinder() :
        mRange(&mPacket),
        mBlink(&mPacket),
        mRangeFinder() {
    }

    // Property definition
    const char* getName() const {
        return "RangeFinder";
    }

    const char* getDescription() {
        return "RangeFinder robot";
    }

    void onStart() {
        mBlink.mEnabled = true;
        mRangeFinder.getRange(this);
    }

    void onNewRange(unsigned short range) {
        mRange = range;
        mRangeFinder.getRange(this);
    }

    Property* getChild(unsigned char index) {
        switch(index) {
        case 0:      return &mBlink;
        case 1:      return &mRange;
        default:    return 0;
        }
    }
};

int main(void)
{
    RangeFinder rf;
    rf.onStart();
    Event::startLooper();
    return 0;
}
