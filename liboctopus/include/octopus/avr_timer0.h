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

#ifndef AVRTIMER0_H
#define AVRTIMER0_H

#include "pwm_channel.h"

class AvrTimer0 {

public:
	AvrTimer0();

	class FastPWMChannelA : public PwmChannel {

		/**
		 * @brief
		 * @return
		 */
		unsigned char getValue();

		/**
		 * @brief
		 * @param value
		 */
		void setValue(unsigned char value);

	};

	class FastPWMChannelB : public PwmChannel {

		/**
		 * @brief
		 * @return
		 */
		unsigned char getValue();

		/**
		 * @brief
		 * @param value
		 */
		void setValue(unsigned char value);

	};
};

#endif // AVRTIMER0_H
