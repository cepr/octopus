
#include "octopus/prop/octopus_comm_stack.h"
#include "octopus/prop/property_record.h"
#include "octopus/dev/usart/avr_usart.h"
#include "octopus/dev/usart/usart_listener.h"
#include "octopus/prop/packet.h"
#include "octopus/dev/blink/blink.h"

class Template : public OctopusCommStack<AvrUsart, PropertyRecord> {

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
