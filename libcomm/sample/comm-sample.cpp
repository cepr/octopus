
//#define CONFIG_BLINK

#include "octopus/event/looper.h"

#ifdef CONFIG_BLINK
# include "octopus/dev/blink/blink.h"
#endif

#if defined(CONFIG_MESSAGES)
# include "octopus/avr_usart.h"
#endif

#ifdef CONFIG_MESSAGES
# include "octopus/message_receiver.h"
# include "octopus/message_transmitter.h"
# ifdef CONFIG_COMMAND_REBOOT
#  include "octopus/commands/reboot.h"
# endif
#endif

using namespace octopus;

#ifdef CONFIG_BLINK
# ifdef CONFIG_MESSAGES
class MyBlink: public Blink
        , public MessageReceiver::Handler
{
public:
    MyBlink() : Handler('L')
    {
    }

    void onMessage(const Buffer &message)
    {
        if (message.size >= 2) {
            enable(message.ptr[1] != 0);
        }
    }
} blink;
# else
Blink blink;
# endif
#endif

int main(void)
{
#ifdef CONFIG_MESSAGES
    MessageReceiver rx(&AvrUsart::instance);
    MessageTransmitter tx(&AvrUsart::instance);

# ifdef CONFIG_COMMAND_REBOOT
    CommandReboot reboot;
    rx.registerHandler(&reboot);
# endif

# ifdef CONFIG_BLINK
    rx.registerHandler(&blink);
# endif
#endif

#ifdef CONFIG_BLINK
    Looper::instance.run(false);
#else
    Looper::instance.run(true);
#endif
    return 0;
}
