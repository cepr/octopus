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

#include "Robot/Robot.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "PropertyPacket.h"
#include "RemotePropertyServer.h"
#include "compass_listener.h"
#include "hmc6352/hmc6352.h"
#include "property_data.h"

class HeadingProperty: public PropertyU16 {
    const char* getName() {
        return "Heading";
    }
    const char* getDescription() {
        return "Compass heading in 1/10 degrees, from 0 to 3600";
    }
public:
    using PropertyData<unsigned short>::operator =;
};

class Compass : public Robot, public PropertyRecord, public CompassListener {

private:
    // List of modules
    Blink                   mBlink;
    Hmc6352                 mCompass;
    HeadingProperty         mHeading;

    // Remote control
    AvrUsart                mAvrUsart;
    Packet                  mPacket;
    PropertyPacket          mBridge;
    RemotePropertyServer    mServer;

public:
    // Constructor
    Compass() : PropertyRecord(),
                 // Modules
                 mBlink(),
                 mCompass(),
                 // Remote control
                 mAvrUsart(),
                 mPacket(&mAvrUsart),
                 mBridge(&mPacket),
                 mServer(this, &mBridge)
    {
        mBridge.registerServer(&mServer);
    }

    // Property definition
    const char* getName() {
        return "Compass";
    }

    const char* getDescription() {
        return "Compass robot";
    }

    void onStart() {
        mBlink.mEnabled = true;
        mAvrUsart.sendString("Compass starting!");
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

static Compass myRobot;
Robot* gRobot = &myRobot;
