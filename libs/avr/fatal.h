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

#ifndef FATAL_H_
#define FATAL_H_

typedef enum {
	FATAL_LOOPER_OVERFLOW=1,
	FATAL_TIMER_CLIENTS_OVERFLOW=2,
	FATAL_USART_RX_OVERFLOW=3,
	FATAL_USART_TX_OVERFLOW=4,
	FATAL_CXA_PURE_VIRTUAL=5,
	FATAL_PENDING_ADC_OVERFLOW=6,
	FATAL_DEBUG=7,
} ERRORCODE;

void fatal(ERRORCODE errorcode);

#endif /* FATAL_H_ */