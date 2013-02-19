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

#ifndef I2C_H
#define I2C_H

#include "octopus/message_receiver.h"
#include "octopus/i2c.h"

namespace octopus {

class i2c : public MessageReceiver::Handler
{
public:
    // Constructor
    i2c(I2CDriver* driver);

    // From MessageReceiver::Handler
    void onMessage(const Buffer &message);

private:
    I2CDriver* driver;
};

} /* namespace octopus */

#endif // I2C_H
