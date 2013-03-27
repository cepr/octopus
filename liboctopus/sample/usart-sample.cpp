
// USART Sample

#include "octopus/looper.h"
#include "octopus/avr_usart.h"

using namespace octopus;

class UsartSample: private Buffer::Callback
{
public:
    // Constructor
    UsartSample() :
        buffer(data, // pointer to buffer data
               sizeof(data), // capacity, not used for writing USART
               sizeof(data), // size, the number of bytes to write to the USART
               this) // callback, see onWriteFinished() below
    {
        // Set the baudrate
        AvrUsart::instance.setBaudrate(AvrUsart::B38400);

        // Initiate the first write
        data[0] = '>';
        AvrUsart::instance.write(&buffer);
    }

    // From Buffer::Callback
    void onReadFinished(Buffer* buffer)
    {    
        AvrUsart::instance.write(buffer);
    }

    // From Buffer::Callback
    void onWriteFinished(Buffer *buffer)
    {
        buffer->size = 0;
        AvrUsart::instance.read(buffer);
    }

private:
    Buffer buffer;
    char data[1];
};

int main(void)
{
    UsartSample sample;
    Looper::instance.run();
    return 0;
}
