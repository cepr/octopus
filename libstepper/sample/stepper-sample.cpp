
// Sample for AvrStepper

#include "octopus/looper.h"
#include "octopus/avr_stepper.h"

using namespace octopus;

class MyRobot: public AsyncOperation
{
public:
    // Constructor
    MyRobot() :
        stepper(&PORTC, 0, 1, 2, 3)
    {
    }

    // From AsyncOperation
    void onFinished() {
        // Stepper has reached its target, let's go back the other direction
        stepper.reachSpeed(-stepper.getSpeed(), this);
    }

    void start()
    {
        stepper.reachSpeed(stepper.getMaxSpeed(), this);
    }

private:
    AvrStepper stepper;
};

MyRobot robot;

int main(void)
{
    robot.start();
    Looper::instance.run(&Gpio::B5);
    return 0;
}
