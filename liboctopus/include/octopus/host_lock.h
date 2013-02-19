#ifndef HOST_LOCK_H
#define HOST_LOCK_H

#ifndef __AVR__

namespace octopus {

// TODO implement octopus::Lock for host

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
class StubLock {
};

typedef StubLock Lock;

} /* octopus */

#endif /* ! __AVR__ */

#endif // HOST_LOCK_H
