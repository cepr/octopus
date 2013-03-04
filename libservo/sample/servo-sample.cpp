
// Servo sample

#include "octopus/looper.h"
#include "octopus/servo.h"
#include "octopus/avr_timer.h"
#include "octopus/blink.h"

using namespace octopus;

class Sample : public Timer::Task {
public:
    static const Timer::time_us_t MIN_PULSE_WIDTH = 1300;
    static const Timer::time_us_t MAX_PULSE_WIDTH = 1700;

    Sample() :
        servo(&PORTC, PORTC0, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH),
        seconds(0)
    {
    }

    void run(Timer::time_us_t when, char what)
    {
        // Compute new servo position
        servo.reachPosition((int16_t)seconds *
                            (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 60);
        seconds++;
        if (seconds < 60) {
            AvrTimer::instance.schedule(this, when + 1000000);
        } else {
            servo.stop();
        }
    }

    Servo servo;
    uint8_t seconds;
};

Sample s;

int main(void)
{
    s.run(AvrTimer::instance.now(), 0);
    Looper::instance.run(true);
    return 0;
}
