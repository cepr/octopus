
#include "octopus/prop/octopus_comm_stack.h"
#include "octopus/prop/property_record.h"
#include "octopus/dev/usart/avr_usart.h"
#include "octopus/dev/usart/usart_listener.h"
#include "octopus/prop/packet.h"
#include "octopus/dev/blink/blink.h"
#include "octopus/dev/servo/servo.h"
#include "octopus/dev/compass/hmc6352.h"
#include "octopus/util/fatal.h"

class OctopusXCopter : public OctopusCommStack<AvrUsart, PropertyRecord>
{

private:
    // List of modules
    Blink           mBlink;

    class FrontLeftMotor: public Servo
    {
    public:
        FrontLeftMotor(Packet* packet) : Servo(4, packet) {
            //mEnabled = true;
        }
        const char* getDescription() {
            return "Front left motor, CW";
        }
        const char* getName() const {
            return "FrontLeftMotor";
        }
    } mFrontLeftMotor;

    class FrontRightMotor : public Servo
    {
    public:
        FrontRightMotor(Packet* packet) : Servo(5, packet) {
            //mEnabled = true;
        }
        const char* getDescription() {
            return "Front right motor, CCW";
        }
        const char* getName() const {
            return "FrontRightMotor";
        }
    } mFrontRightMotor;

    class BackLeftMotor : public Servo
    {
    public:
        BackLeftMotor(Packet* packet) : Servo(6, packet) {
            //mEnabled = true;
        }
        const char* getDescription() {
            return "Back left motor, CCW";
        }
        const char* getName() const {
            return "BackLeftMotor";
        }
    } mBackLeftMotor;

    class BackRightMotor : public Servo
    {
    public:
        BackRightMotor(Packet* packet) : Servo(7, packet) {
            //mEnabled = true;
        }
        const char* getDescription() {
            return "Back right motor, CW";
        }
        const char* getName() const {
            return "BackRightMotor";
        }
    } mBackRightMotor;

    class Heading : public PropertyU16, public CompassListener, public ApplicationTimer
    {
    public:
        // Attributes
        Hmc6352 mCompass;

        // Constructor
        Heading(Packet* packet) :
                // parent classes
                PropertyU16(0, packet),
                CompassListener(),
                ApplicationTimer(),
                // attributes
                mCompass() {

            schedule(0, 0);
        }

        // From PropertyU16
        const char* getName() const {
            return "Heading";
        }
        const char* getDescription() {
            return "Magnetic sensor (HMC6352)";
        }
        using PropertyU16::operator =;

        // From CompassListener
        void onNewHeading(unsigned short heading) {
            operator=(heading);
            refresh(); // send the value to the remote computer
        }

        // From ApplicationTimer
        void onTimer(char what) {
            schedule(now()+50000, 0);   // 20Hz
            mCompass.getHeading(this);
        }
    } mHeading;

public:
    // Constructor
    OctopusXCopter() :
        OctopusCommStack<AvrUsart, PropertyRecord>(),
        // Attributes
        mBlink(&mPacket),
        mFrontLeftMotor(&mPacket),
        mFrontRightMotor(&mPacket),
        mBackLeftMotor(&mPacket),
        mBackRightMotor(&mPacket),
        mHeading(&mPacket) {
    }

    // Property definition
    const char* getName() const {
        return "OctopusXCopter";
    }

    const char* getDescription() {
        return "OctopusXCopter robot";
    }

    void onStart() {
        //mFrontLeftMotor.mEnabled = true;
        //mFrontRightMotor.mEnabled = true;
        //mBackLeftMotor.mEnabled = true;
        //mBackRightMotor.mEnabled = true;
    }

    Property* getChild(unsigned char index) {
        switch(index) {
        case 0:
            return &mFrontLeftMotor;
        case 1:
            return &mFrontRightMotor;
        case 2:
            return &mBackLeftMotor;
        case 3:
            return &mBackRightMotor;
        case 4:
            return &mHeading;
        case 5:
            return &mBlink;
        default:
            return 0;
        }
    }
};


int main(void)
{
    static OctopusXCopter robot;
    robot.onStart();
    Event::startLooper();
    return 0;
}
