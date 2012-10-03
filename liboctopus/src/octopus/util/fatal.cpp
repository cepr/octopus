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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/wdt.h>

#include "fatal.h"

void fatal(ERRORCODE errorcode) {
	cli();
	wdt_disable();
	DDRB |= _BV(5);
	for (;;) {
		char i;
		for (i = 0; i < errorcode; i++) {
			PORTB |= _BV(5);
			_delay_ms(100);
			PORTB &= ~_BV(5);
			_delay_ms(300);
		}
		_delay_ms(1000);
	}
}

void reboot(void) {
	cli();
	// Enable watchdog
	wdt_enable(WDTO_15MS);
	for (;;) {
		// Wait for reboot
	}
}

void enter_boot_loader(void) {
	cli();
	SREG = 0x00;
	__asm__ __volatile__ ("jmp 0x3800" ::: "memory");
}

/**
 * The __cxa_pure_virtual function is an error handler that is invoked
 * when a pure virtual function is called.
 */
extern "C" void __cxa_pure_virtual() {
	fatal(FATAL_CXA_PURE_VIRTUAL);
}
