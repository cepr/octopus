
#include "Robot/Robot.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "PropertyPacket.h"
#include "RemotePropertyServer.h"
#include "Range/lv_max_sonar_ez.h"
#include "property_data.h"

class RangeProperty: public PropertyU16 {
    const char* getName() {
        return "Range";
    }
    const char* getDescription() {
        return "Range in centimeters";
    }
public:
    using PropertyU16::operator =;
};

class RangeFinder : public Robot, public PropertyRecord, public RangeListener {

private:
    // List of modules
    Blink 					mBlink;
    LVMaxSonarEZ            mRangeFinder;

    // Remote control
    AvrUsart 				mAvrUsart;
    Packet 					mPacket;
    PropertyPacket 			mBridge;
    RemotePropertyServer 	mServer;

    // Private
    RangeProperty           mRange;

public:
    // Constructor
    RangeFinder() : PropertyRecord(),
        // Modules
        mBlink(),
        // Remote control
        mAvrUsart(),
        mPacket(&mAvrUsart),
        mBridge(&mPacket),
        mServer(this, &mBridge) {
        mBridge.registerServer(&mServer);
    }

    // Property definition
    const char* getName() {
        return "RangeFinder";
    }

    const char* getDescription() {
        return "RangeFinder robot";
    }

    void onStart() {
        mBlink.mEnabled = true;
        mAvrUsart.sendString("RangeFinder starting!");
        mRangeFinder.getRange(this);
    }

    void onNewRange(unsigned short range) {
        mRange = range;
        mRangeFinder.getRange(this);
    }

    Property* getChild(unsigned char index) {
        switch(index) {
        case 0:
            return &mBlink;
        case 1:
            return &mRange;
        default:
            return 0;
        }
    }
};

static RangeFinder myRobot;
Robot* gRobot = &myRobot;
