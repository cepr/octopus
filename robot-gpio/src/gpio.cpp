
#include "octopus/prop/octopus_comm_stack.h"
#include "octopus/prop/property_record.h"
#include "octopus/dev/usart/avr_usart.h"
#include "octopus/dev/usart/usart_listener.h"
#include "octopus/prop/packet.h"
#include "octopus/dev/blink/blink.h"

class Gpio : public PropertyRecord, public PropertyListener, public SystemTimer {
private:
    const char* mName;
    int mPort;
    int mPin;

    // false : input
    // true : output
    class Direction : public PropertyBoolean {
    public:
        Direction(Packet* packet) : PropertyBoolean(false, packet) {}
        const char* getName() const { return "direction"; }
        const char* getDescription() { return "true = output"; }
        using PropertyBoolean::operator =;
    } mDirection;

    // if Direction is input, Level represent pull down or pull up
    // if Direction is output, Level represent output latch value
    class Level: public PropertyBoolean {
    public:
        Level(Packet* packet) : PropertyBoolean(true, packet) {}
        const char* getName() const { return "level"; }
        const char* getDescription() { return ""; }
        using PropertyBoolean::operator =;
    } mLevel;

public:
    Gpio(Packet* packet, const char* name, int port, int pin) :
            // Parent classes
            PropertyRecord(packet),
            PropertyListener(),
            SystemTimer(),
            // Attributes
            mName(name),
            mPort(port),
            mPin(pin),
            mDirection(packet),
            mLevel(packet) {
        mDirection.registerListener(this);
        mLevel.registerListener(this);
    }
    const char* getName() const { return mName; }
    const char* getDescription() { return ""; }
    Property* getChild(unsigned char index) {
        switch(index) {
            case 0: return &mDirection;
            case 1: return &mLevel;
        }
        return 0;
    }

    void onPropertyChanged(Property* prop, PROPERTY_INFO what, ORIGIN origin) {
        if (origin == ORIGIN_REMOTE) {
            switch(mPort) {
                case 0: // PORTB
                    if ((bool)mDirection) {
                        // output
                        if ((bool)mLevel) {
                            // high level
                            PORTB |= (1<<mPin);
                        } else {
                            // low level
                            PORTB &= ~(1<<mPin);
                        }
                        DDRB |= (1<<mPin);
                    } else {
                        // input
                        if ((bool)mLevel) {
                            PORTB |= (1<<mPin);
                        } else {
                            PORTB &= ~(1<<mPin);
                        }
                        DDRB &= ~(1<<mPin);
                    }
                    break;

                case 1: // PORTC
                    if ((bool)mDirection) {
                        // output
                        if ((bool)mLevel) {
                            // high level
                            PORTC |= (1<<mPin);
                        } else {
                            // low level
                            PORTC &= ~(1<<mPin);
                        }
                        DDRC |= (1<<mPin);
                    } else {
                        // input
                        if ((bool)mLevel) {
                            PORTC |= (1<<mPin);
                        } else {
                            PORTC &= ~(1<<mPin);
                        }
                        DDRC &= ~(1<<mPin);
                    }
                    break;

                case 2: // PORTD
                    if ((bool)mDirection) {
                        // output
                        if ((bool)mLevel) {
                            // high level
                            PORTD |= (1<<mPin);
                        } else {
                            // low level
                            PORTD &= ~(1<<mPin);
                        }
                        DDRD |= (1<<mPin);
                    } else {
                        // input
                        if ((bool)mLevel) {
                            PORTD |= (1<<mPin);
                        } else {
                            PORTD &= ~(1<<mPin);
                        }
                        DDRD &= ~(1<<mPin);
                    }
                    break;
            }

            if (!(bool)mDirection) {
                // Trigger read timer
                schedule(now() + 20000, 0);
            }
        }
    }

    void onTimerLISR(unsigned short when, char what = 0) {
        if (!(bool)mDirection) {
            switch(mPort) {
                case 0:
                    mLevel = (PINB & (1<<mPin)) ? true : false;
                    break;
                case 1:
                    mLevel = (PINC & (1<<mPin)) ? true : false;
                    break;
                case 2:
                    mLevel = (PIND & (1<<mPin)) ? true : false;
                    break;
            }
            schedule(when + 20000, 0);
        }
    }
};

class GPIOs : public OctopusCommStack<AvrUsart, PropertyRecord> {

private:
    // List of modules
    Blink           mBlink;
    Gpio            mPB0;
    Gpio            mPB1;
    Gpio            mPC0;
    Gpio            mPC1;
    Gpio            mPC2;
    Gpio            mPC3;
    Gpio            mPC4;
    Gpio            mPC5;
    Gpio            mPD2;
    Gpio            mPD3;
    Gpio            mPD4;
    Gpio            mPD5;
    Gpio            mPD6;
    Gpio            mPD7;

public:
    // Constructor
    GPIOs() :
            OctopusCommStack<AvrUsart, PropertyRecord>(),
            // Properties
            mBlink(&mPacket),
            mPB0(&mPacket, "PB0", 0, 0),
            mPB1(&mPacket, "PB1", 0, 1),
            mPC0(&mPacket, "PC0", 1, 0),
            mPC1(&mPacket, "PC1", 1, 1),
            mPC2(&mPacket, "PC2", 1, 2),
            mPC3(&mPacket, "PC3", 1, 3),
            mPC4(&mPacket, "PC4", 1, 4),
            mPC5(&mPacket, "PC5", 1, 5),
            mPD2(&mPacket, "PD2", 2, 2),
            mPD3(&mPacket, "PD3", 2, 3),
            mPD4(&mPacket, "PD4", 2, 4),
            mPD5(&mPacket, "PD5", 2, 5),
            mPD6(&mPacket, "PD6", 2, 6),
            mPD7(&mPacket, "PD7", 2, 7) {
    }

    // Property definition
    const char* getName() const {
        return "GPIOs";
    }

    const char* getDescription() {
        return "GPIOs robot";
    }

    Property* getChild(unsigned char index) {
        switch(index) {
            case 0: return &mBlink;
            case 1: return &mPB0;
            case 2: return &mPB1;
            case 3: return &mPC0;
            case 4: return &mPC1;
            case 5: return &mPC2;
            case 6: return &mPC3;
            case 7: return &mPC4;
            case 8: return &mPC5;
            case 9: return &mPD2;
            case 10: return &mPD3;
            case 11: return &mPD4;
            case 12: return &mPD5;
            case 13: return &mPD6;
            case 14: return &mPD7;
            default: return 0;
        }
    }
};


int main(void)
{
    static GPIOs robot;
    Event::startLooper();
    return 0;
}
