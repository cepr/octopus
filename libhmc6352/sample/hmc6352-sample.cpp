
// hmc6352 digital compass sample

#include "octopus/looper.h"
#include "octopus/avr_usart.h"
#include "octopus/avr_two_wire_interface.h"
#include "octopus/hmc6352.h"
#include "octopus/avr_timer.h"
#include "octopus/fatal.h"

using namespace octopus;

class MyCompass:
        public CompassListener,
        public Buffer::Callback,
        public Timer::Task
{
public:
    // Constructor
    MyCompass() :
        device(&AvrTwoWireInterface::instance)
    {
    }

    // From CompassListener
    void onNewHeading(uint16_t heading)
    {
        // Measure finished, send result to the serial port
        buffer.data = heading;
        AvrUsart::instance.write(&buffer);
    }

    // From CompassListener
    void onCompassError(uint8_t error_code)
    {
        buffer.data = (unsigned short)error_code;
        AvrUsart::instance.write(&buffer);
    }

    // From Timer::Task
    void run(Timer::time_us_t when, char what)
    {
        device.getHeading(this);
        AvrTimer::instance.schedule(this, when + 20000);
    }

    Hmc6352 device;
    TBuffer<unsigned short> buffer;

} compass;

int main(void)
{
    // Start the compass timer
    AvrTimer::instance.schedule(&compass, 0);

    Looper::instance.run(&Gpio::B5);
    return 0;
}
