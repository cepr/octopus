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

#ifndef COMMAND_REBOOT_H
#define COMMAND_REBOOT_H

#include "octopus/message_receiver.h"
#include "octopus/commands.h"
#include "octopus/util/fatal.h"

namespace octopus {

class CommandReboot : public MessageReceiver::Handler
{
public:
    CommandReboot() : Handler(CMD_REBOOT)
    {
    }

    void onMessage(const Buffer&  message)
    {
        enter_boot_loader();
    }
};

} /* namespace octopus */

#endif // COMMAND_REBOOT_H
