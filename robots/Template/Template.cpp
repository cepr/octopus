
#include "Robot/Robot.h"
#include "octopus_comm_stack.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"

class Template : public Robot, public OctopusCommStack<AvrUsart, PropertyRecord> {

private:
    // List of modules
    Blink           mBlink;

public:
    // Constructor
    Template() : mBlink(&mPacket) {
    }

    // Property definition
    const char* getName() const {
        return "Template";
    }

    const char* getDescription() {
        return "Template robot";
    }

    void onStart() {
    }

    Property* getChild(unsigned char index) {
        switch(index) {
            case 0: return &mBlink;
            default: return 0;
        }
    }
};


int main(void)
{
    Template robot;
    robot.onStart();
    Event::startLooper();
    return 0;
}
