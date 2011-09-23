/*
 * Copyright 2010-2011 Cedric Priscal
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

#include "hmc6352.h"
#include "Timer/Timer.h"
#include "twi/AvrTwoWireInterface.h"

#ifdef FAST_I2C
# error FAST_I2C is not supported with HMC6352.
#endif

Hmc6352::Hmc6352() {
    mListener = 0;
    mTransfer.device = this;
    mTransfer.buffer = mBuffer;
}

void Hmc6352::getHeading(CompassListener* listener) {
    mListener = listener;
    mTransfer.type = I2C_TRANSMIT;
    mBuffer[0] = 'A';
    mTransfer.size = 1;
    mTransfer.next = 0;
    AvrTwoWireInterface::getInstance().commit(&mTransfer);
}

void Hmc6352::onTransmitFinished(unsigned char transmitted) {
    schedule(now() + 6000, 0);
}

void Hmc6352::onTimer(char what, unsigned short when) {
    mTransfer.type = I2C_RECEIVE;
    mTransfer.size = 2;
    mTransfer.next = 0;
    AvrTwoWireInterface::getInstance().commit(&mTransfer);
}

void Hmc6352::onReceiveFinished(unsigned char received) {
    if (mListener && (received == 2)) {
        unsigned short heading;
        ((unsigned char*)&heading)[0] = mBuffer[1];
        ((unsigned char*)&heading)[1] = mBuffer[0];
        mListener->onNewHeading(heading);
    }
}

unsigned char Hmc6352::getAddress(void) {
    return 0x42;
}

void Hmc6352::onBusBusy(void) {
    // TODO reschedule
}

void Hmc6352::onBusError(void) {
    // TODO reschedule
}

void Hmc6352::onDeviceNack(void) {
    // TODO reschedule
}

void Hmc6352::onDeviceNotResponding(void) {
    // TODO reschedule
}
