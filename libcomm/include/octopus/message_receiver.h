/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H

#include "usart.h"
#include "packet.h"
#include "buffer.h"
#include "octopus/util/list.h"

namespace octopus {

/**
 * @brief The MessageReceiver class
 *
 * This class listens for incoming messages, extract the ID of the message and
 * call the message handler which supports that ID. The ID is the first byte of
 * a message.
 */
class MessageReceiver: public Packet::Callback
{
public:
    /**
     * @brief The Handler class
     *
     * This class is the abstract class for all message handlers. The first
     * byte of a message is called the ID of the message and defines which
     * handler should handle it.
     *
     * To handle a custom message, you should inherit this class and register
     * it using MessageReceiver::registerHandler().
     */
    class Handler
    {
    public:
        /**
         * @brief Constructor
         *
         * This constructor is used to define the ID handled by this message
         * handler. The ID of a message is its first byte.
         */
        Handler(unsigned char id) :
            prev(0),
            next(0),
            id(id)
        {
        }

        /**
         * @brief Incoming message callback
         *
         * This callback is called when a new complete message with corresponding
         * ID is received. The message content is passed in the argument @arg
         * message.
         *
         * This method is called from application context.
         *
         * @arg message is only valid for the duration of the call to this method.
         * Especially, you must not keep any reference for later use.
         */
        virtual void onMessage(const Buffer&  message) = 0;

        /**
         * @brief Returns the message ID handled by this class
         */
        char getID()
        {
            return id;
        }

        // For List<Handler>
        Handler* prev;
        Handler* next;

    protected:
        // Message ID
        unsigned char id;
    };

    /**
     * @brief Constructor
     *
     * Construct a message transmitter. The created server will immediately begin
     * to listen on @a usart. The server will handle the built-in commands. You
     * can register custom message handlers with ::registerHandler().
     */
    MessageReceiver(Usart* usart);

    /**
     * @brief Registers a new message handler
     *
     * Every time a message whose ID correspond to the ID handled by @arg handler,
     * the server will call the method Handler::onMessage() of @arg handler with
     * that message.
     */
    void registerHandler(Handler* handler);

private:
    // From Packet::Callback, called when a complete incoming message is ready
    virtual void onReadPacketComplete();

    // Packet instance for reading packets
    Packet packet;

    // Buffer for message reception
    char buffer[64];
    Buffer message;

    // All commands
    List<Handler> handlers;
};

} /* namespace octopus */

#endif // MESSAGE_RECEIVER_H
