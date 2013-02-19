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

#ifdef __AVR

#include "rf_remote.h"
#include "princeton_rf.h"

static const tristate RfAddresses[] = {
                  // A0....A7
    {0x00, 0x11}, // 0...0...
    {0x00, 0x21}, // 0....0..
    {0x00, 0x41}, // 0.....0.
    {0x00, 0x12}, // .0..0...
    {0x00, 0x22}, // .0...0..
    {0x00, 0x42}, // .0....0.
    {0x00, 0x14}, // ..0.0...
    {0x00, 0x24}, // ..0..0..
    {0x00, 0x44}, // ..0...0.
    {0x00, 0x18}, // ...00...
    {0x00, 0x28}, // ...0.0..
    {0x00, 0x48}, // ...0..0.
};

RfRemote::RfRemote(char pin) : mRfEncoder(pin) {
}

void RfRemote::Set(RfRemoteAddress remote, bool enabled) {
    tristate address = RfAddresses[remote];
    tristate data = {enabled ? (unsigned char)0x01 : (unsigned char)0x00, (unsigned char)0x01};
    mRfEncoder.send(address, data);
}

#endif /* __AVR */
