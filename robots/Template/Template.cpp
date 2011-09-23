
#include "Robot/Robot.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "PropertyPacket.h"
#include "RemotePropertyServer.h"

class Template : public Robot, public PropertyRecord {

private:
    // List of modules
    Blink 					mBlink;

    // Remote control
	AvrUsart 				mAvrUsart;
	Packet 					mPacket;
	PropertyPacket 			mBridge;
	RemotePropertyServer 	mServer;

public:
    // Constructor
    Template() : PropertyRecord(),
                 // Modules
                 mBlink(),
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
        return "Template";
    }

	const char* getDescription() {
        return "Template robot";
    }

    void onStart() {
        mBlink.mEnabled = true;
        mAvrUsart.sendString("Template starting!");
    }

    Property* getChild(unsigned char index) {
       	switch(index) {
            case 0: return &mBlink;
            default: return 0;
        }
    }
};

static Template myRobot;
Robot* gRobot = &myRobot;
