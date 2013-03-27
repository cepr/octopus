
// octopus temperature sample
//
// You can display the temperature in real time using `trend`:
// cat /dev/ttyACM0 | trend -f s - 1000 0 1023

#include "octopus/looper.h"
#include "octopus/avr_adc.h"
#include "octopus/avr_usart.h"

using namespace octopus;

class TemperatureSample: private AvrADC::Channel, private Buffer::Callback {
public:
    TemperatureSample() :
        Channel(Channel::CHANNEL_ADC8, Channel::VREF_VBG),
        buffer((char*)&value,
               0,
               sizeof(value),
               this)
    {
        // Start a new measure
        start();
    }

    // New measure available
    void onNewMeasure(uint16_t value)
    {
        // Send result to the serial port
        this->value = value;
        AvrUsart::instance.write(&buffer);
    }

    // Result sent to the serial port
    void onWriteFinished(Buffer *)
    {
        // Start a new measure
        start();
    }

private:
    Buffer buffer;
    uint16_t value;
};

int main(void)
{
    static TemperatureSample sample;
    Looper::instance.run(&Gpio::B5);
    return 0;
}
