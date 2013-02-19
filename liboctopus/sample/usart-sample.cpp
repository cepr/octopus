
// USART Sample

#include "octopus/looper.h"
#include "octopus/avr_usart.h"

using namespace octopus;

static const char HELLO_WORLD_STRING[] = "Hello, world !\n";

class UsartSample: private Buffer::Callback
{
public:
    // Constructor
    UsartSample() :
        output_buffer((char*)HELLO_WORLD_STRING, // pointer to buffer data
                      0, // capacity, not used for writing USART
                      sizeof(HELLO_WORLD_STRING) - 1, // size, the number of bytes to write to the USART
                      this) // callback, see onWriteFinished() below
    {
        // Initiate the first write
        AvrUsart::instance.write(&output_buffer);
    }

    // From Buffer::Callback
    void onReadFinished(Buffer* buffer)
    {

    }

    // From Buffer::Callback
    void onWriteFinished(Buffer *buffer)
    {
        (void) buffer; // parameter buffer not used
        AvrUsart::instance.write(&output_buffer);
    }

private:
    Buffer output_buffer;
};

int main(void)
{
    UsartSample sample;
    Looper::instance.run();
    return 0;
}
