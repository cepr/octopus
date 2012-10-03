/*
 * Copyright 2010 Cedric Priscal
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

#ifndef RFREMOTE_H_
#define RFREMOTE_H_

#include "PrincetonRf/PrincetonRfEncoder.h"

typedef enum {
    RF_REMOTE_A1,
    RF_REMOTE_A2,
    RF_REMOTE_A3,
    RF_REMOTE_B1,
    RF_REMOTE_B2,
    RF_REMOTE_B3,
    RF_REMOTE_C1,
    RF_REMOTE_C2,
    RF_REMOTE_C3,
    RF_REMOTE_D1,
    RF_REMOTE_D2,
    RF_REMOTE_D3
} RfRemoteAddress;

class RfRemote {
    PrincetonRfEncoder mRfEncoder;
public:
    RfRemote(char pin);
    void Set(RfRemoteAddress remote, bool enabled);
};

#endif /* RFREMOTE_H_ */
