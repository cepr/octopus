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

#ifdef __AVR

typedef enum {
    FATAL_PACKET_IN_USE = 1,
	FATAL_CXA_PURE_VIRTUAL = 2,
    FATAL_USART_RX_OVERRUN = 3,
    FATAL_TWI_UNKNOWN_STATUS = 4,
    FATAL_DEBUG = 5,
    FATAL_INVALID_PARAMETER = 6
} ERRORCODE;

void fatal(ERRORCODE errorcode) __attribute__ ((noreturn));

/**
 * @brief Reboot the device
 *
 * This function activates the watchdog and waits for the device to reset.
 */
void reboot(void) __attribute__ ((noreturn));

/**
 * @brief Enter the bootloader
 */
void enter_boot_loader(void);

#endif /* __AVR */

#endif /* FATAL_H_ */
