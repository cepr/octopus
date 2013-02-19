#ifndef COMMAND_WRITE_H
#define COMMAND_WRITE_H

#include "octopus/message_receiver.h"
#include "octopus/message_transmitter.h"
#include "octopus/commands.h"
#include <stdint.h>

namespace octopus {

class CommandWrite : public MessageReceiver::Handler
{
public:
    CommandWrite(MessageTransmitter *transmitter);
    void onMessage(const Buffer &message);

protected:
    struct Request {
        uint8_t id;
        uint16_t offset;
    } __attribute__((packed));

    MessageTransmitter *transmitter;
    TBuffer<uint8_t> reply_header;
};

} /* namespace octopus */

#endif // COMMAND_WRITE_H
