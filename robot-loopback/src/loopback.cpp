/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "octopus/dev/blink/blink.h"
#include "octopus/event/looper.h"
#include "octopus/avr_usart.h"

using namespace octopus;

class Parrot: public Buffer::Callback {
public:
    Parrot() :
        buffer(&b, sizeof(b), sizeof(b), this)
    {
        AvrUsart::instance.read(&buffer);
    }

    virtual void onReadFinished(Buffer* buffer)
    {
        // Byte received, send it back
        AvrUsart::instance.write(buffer);
    }

    virtual void onWriteFinished(Buffer *buffer)
    {
        // Tx terminated, listen again
        AvrUsart::instance.read(buffer);
    }

private:
    Buffer buffer;
    char b;
};

int main(void) {
    Blink blink;
    Parrot parrot;
    Looper::instance.run();
    return 0;
}
