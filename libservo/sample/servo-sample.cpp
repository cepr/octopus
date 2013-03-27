
// Servo sample

#include "octopus/looper.h"
#include "octopus/servo.h"
#include "octopus/avr_timer.h"
#include "octopus/blink.h"
#include "octopus/gpio.h"

using namespace octopus;

class ServoSample : public Timer::Task, Gpio::Listener {
public:
    static const Servo::pos_t MIN_PULSE_WIDTH = 800;
    static const Servo::pos_t MAX_PULSE_WIDTH = 2200;

    ServoSample() :
        servo(&Gpio::C0),
        position((MIN_PULSE_WIDTH + MAX_PULSE_WIDTH) / 2),
        direction(0)
    {
        // B0 and B1 controls the servomotor (pins 8 and 9 on Arduino Pro Mini)
        Gpio::B0.setDirection(Gpio::INPUT);
        Gpio::B0.activatePullUp();
        Gpio::B0.registerListener(this);

        Gpio::B1.setDirection(Gpio::INPUT);
        Gpio::B1.activatePullUp();
        Gpio::B1.registerListener(this);
    }

    void run(Timer::time_us_t when, char what)
    {
        // Compute new servo position
        if (direction) {
            servo.reachPosition(position);
            position += direction;
            if (position > MAX_PULSE_WIDTH) {
                position = MAX_PULSE_WIDTH;
            } else if (position < MIN_PULSE_WIDTH) {
                position = MIN_PULSE_WIDTH;
            }
        }
        AvrTimer::instance.schedule(this, when + 20000);
    }

    // From Gpio::Listener
    void onPinChange()
    {
        if (!Gpio::B0.get()) {
            direction = 20;
        } else if (!Gpio::B1.get()){
            direction = -20;
        } else {
            direction = 0;
            servo.stop();
        }
    }

    Servo servo;
    uint16_t position;
    int16_t direction;
};

ServoSample s;

int main(void)
{
    s.run(AvrTimer::instance.now(), 0);
    Looper::instance.run(&Gpio::B5);
    return 0;
}
