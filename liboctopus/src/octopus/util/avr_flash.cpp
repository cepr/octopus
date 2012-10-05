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

#ifdef __AVR

unsigned char readU8(const unsigned char *ptr) {

    unsigned char ret;

    asm ("movw r30,%1\n\t"
         "lpm %0,Z\n\t"
         : "=r"(ret)
         : "r" (ptr)
         : "r30", "r31");

    return ret;
}

unsigned short readU16(const unsigned short *ptr) {

    union {
        unsigned char regs[2];
        unsigned short u16;
    } ret;

    asm ("movw r30,%2\n\t"
         "lpm %0,Z+\n\t"
         "lpm %1,Z\n\t"
         : "=r" (ret.regs[0]),
           "=r" (ret.regs[1])
         : "r" (ptr)
         : "r30",
           "r31");

    return ret.u16;
}

unsigned long readU32(const unsigned long *ptr) {

    union {
        unsigned char regs[4];
        unsigned long u32;
    } ret;

    asm ("movw r30,%4\n\t"
         "lpm %0,Z+\n\t"
         "lpm %1,Z+\n\t"
         "lpm %2,Z+\n\t"
         "lpm %3,Z\n\t"
         : "=r" (ret.regs[0]),
           "=r" (ret.regs[1]),
           "=r" (ret.regs[2]),
           "=r" (ret.regs[3])
         : "r" (ptr)
         : "r30",
           "r31");

    return ret.u32;
}

#endif /* __AVR */
