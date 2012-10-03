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

#ifndef PRINCETONRF_H_
#define PRINCETONRF_H_

#define ALPHA 81
#define SHORT_DURATION (4*ALPHA)
#define LONG_DURATION (12*ALPHA)
#define SYNC_HIGH_DURATION (4*ALPHA)
#define SYNC_LOW_DURATION (124*ALPHA)

typedef struct {
    unsigned char value;
    unsigned char mask;
} tristate;

#endif /* PRINCETONRF_H_ */
