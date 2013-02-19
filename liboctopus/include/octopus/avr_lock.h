#ifndef AVR_LOCK_H
#define AVR_LOCK_H

#ifdef __AVR__

#include <avr/interrupt.h>

namespace octopus {

/**
 * \brief Lock
 *
 * Instantiate this class in order to create a critical section. A critical section is a sequence of code delimited by
 * brackets which is safe from interrupts.
 *
 * This class can be instantiated both from interrupt context and from normal context.
 *
 * @par Example
 *
 * @code
 * #include <octopus/lock.h>
 * using namespace octopus;
 *
 * void function()
 * {
 *    Lock l;
 *    // Critical code begin
 *    ...
 *    // Critical code end
 * }
 * @endcode
 * is equivalent to:
 * @code
 * #include <avr/interrupt.h>
 *
 * void function()
 * {
 *     unsigned char mSREG = SREG;
 *     cli();
 *     // Critical code begin
 *
 *     // Critical code end
 *     SREG = mSREG;
 * }
 * @endcode
 *
 * Except that you can call `return` at any point in the critical section without having to restore SREG. It will be automaticaly
 * done by the compiler.
 *
 * @par How it works ?
 *
 * When instantiating this class inside a section, the constructor gets called before
 * the first instruction of the section, which will mask interrupts, and the destructor will be called after the last instruction
 * of the section, which will restore the interrupt mask. This lock mechanism is simple to use and very safe because you cannot
 * forget to restore the interrupt mask status; the destructor always get called when leaving the section, even in case of an
 * explicit call to `return` or if an exception if thrown (gcc does not support exception for AVR targets though).
 */
class Lock {
public:
    Lock()
    {
        mSREG = SREG;
        cli();
    }

    ~Lock()
    {
        SREG = mSREG;
    }

private:
    unsigned char mSREG;
    Lock(const Lock& from);
};

} /* octopus */

#endif // __AVR__

#endif // AVR_LOCK_H
