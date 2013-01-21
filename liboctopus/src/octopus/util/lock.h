/*
 * Copyright 2013 Cedric Priscal
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

#ifndef LOCK_H_
#define LOCK_H_

namespace octopus {
namespace util {

/**
 * \brief Lock
 *
 * Instantiate this class in order to create a critical section. A critical section is a sequence of code delimited by
 * brackets which is safe from interrupts. When instantiating this class inside a section, the constructor gets called before
 * the first instruction of the section, which will mask interrupts, and the destructor will be called after the last instruction
 * of the section, which will restore the interrupt mask. This lock mechanism is simple to use and very safe because you cannot
 * forget to restore the interrupt mask status; the destructor always get called when leaving the section, even in case of an
 * explicit call to \a return or if an exception if thrown.
 *
 * This class can be instantiated both from interrupt context and from normal context.
 */
class Lock {
public:
	Lock();
	~Lock();
private:
	Lock(const Lock& from);
};

} /* util */
} /* octopus */

#endif /* LOCK_H_ */
