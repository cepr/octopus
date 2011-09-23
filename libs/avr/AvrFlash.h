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

#ifndef AVRFLASH_H_
#define AVRFLASH_H_

/**
 * \defgroup const_access_group Direct access to const variables
 * \ingroup DEVELOPER_GUIDE
 *
 * When you define a const variable with avr-gcc, its value is stored
 * in flash and mirrored into RAM at boot. It is not acceptable for huge
 * constant arrays.
 *
 * A solution is to place your constant variable into section .text, which
 * will bypass the flash to RAM mirroring at boot.
 * \code
 * const unsigned char MY_CONST_ARRAY[] __attribute__ ((section (".text"))) = {
 *   ...
 * };
 * \endcode
 *
 * Since the assembler instruction to read flash is different from the one to read RAM,
 * you have to use a special function:
 * \code
 * unsigned char value = readU8(&MY_CONST_ARRAY[i]);
 * \endcode
 *
 * \{
 */

/**
 * \brief Read an unsigned char from AVR flash memory
 *
 * \param[in] ptr Address to read from.
 *
 * \return The value of the unsigned char.
 *
 * \see readU16
 * \see readU32
 */
unsigned char  readU8 (const unsigned char  *ptr);

/**
 * \brief Read an unsigned short from AVR flash memory
 *
 * \param[in] ptr Address to read from
 *
 * \return The value of the unsigned short.
 *
 * \see readU8
 * \see readU32
 */
unsigned short readU16(const unsigned short *ptr);

/**
 * \brief Read an unsigned long from AVR flash memory
 *
 * \param[in] ptr Address to read from
 *
 * \return The value of the unsigned long.
 *
 * \see readU8
 * \see readU16
 */
unsigned long  readU32(const unsigned long  *ptr);

/**
 * \}
 */

#endif /* AVRFLASH_H_ */
