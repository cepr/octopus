
#include "fatal.h"

#include "Robot/Robot.h"
#include "octopus_comm_stack.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "Servo/Servo.h"

class OctopusXCopter : public Robot, public OctopusCommStack<AvrUsart, PropertyRecord>
{

private:
    // List of modules
    Blink           mBlink;

    class FrontLeftMotor: public Servo
    {
    public:
        FrontLeftMotor(Packet* packet) : Servo(4, packet) {
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
        }
        const char* getDescription() {
            return "Back right motor, CW";
        }
        const char* getName() const {
            return "BackRightMotor";
        }
    } mBackRightMotor;

public:
    // Constructor
    OctopusXCopter() :
        mBlink(&mPacket),
        mFrontLeftMotor(&mPacket),
        mFrontRightMotor(&mPacket),
        mBackLeftMotor(&mPacket),
        mBackRightMotor(&mPacket) {
    }

    // Property definition
    const char* getName() const {
        return "OctopusXCopter";
    }

    const char* getDescription() {
        return "OctopusXCopter robot";
    }

    void onStart() {
        mBlink.mEnabled = true;
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
