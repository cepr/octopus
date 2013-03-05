
// Gpio sample

#include "octopus/looper.h"
#include "octopus/gpio.h"

using namespace octopus;

/**
 * @brief The GpioSample class
 *
 * This class demonstrates how to get the value of a pin, how to set
 * the value of a pin and how to register a listener (interrupt) on
 * on pin.
 */
class GpioSample : public Gpio::Listener {
public:
    // Constructor.
    GpioSample()
    {
        // Configuration of B1 pin (pin 9 on Arduino Pro Mini) as input with internal pull-up.
        Gpio::B1.setDirection(Gpio::INPUT);
        Gpio::B1.activatePullUp();

        // Read of the pin value
        uint8_t value = Gpio::B1.get();

        // Configuration of B5 pin (LED on Arduino Pro Mini).
        Gpio::B5.setDirection(Gpio::OUTPUT);
        Gpio::B5.set(value);

        // Registering a listener
        Gpio::B1.registerListener(this);
    }

    // From Gpio::Listener
    void onPinChange()
    {
        // Toggle LED
        Gpio::B5.set(Gpio::B1.get());
    }
};

int main(void)
{
    static GpioSample sample;
    Looper::instance.run();
    return 0;
}
