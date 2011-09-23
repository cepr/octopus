
#include "Robot/Robot.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Blink/Blink.h"

class LoopBack : public Robot, private UsartListener {

private:
	// List of modules
	Blink 					mBlink;

	// Remote control
	AvrUsart 				mAvrUsart;

public:
	// Constructor
	LoopBack() :
		// Modules
		mBlink(),
		// Remote control
		mAvrUsart(AvrUsart::B2400) {
		mAvrUsart.registerListener(this);
	}

	void onStart() {
		mBlink.mEnabled = true;
		mAvrUsart.sendString("LoopBack starting!");
	}


	void onUsartReceived(unsigned char byte) {
		mAvrUsart.sendByte(byte);
	}

};

static LoopBack myRobot;
Robot* gRobot = &myRobot;
