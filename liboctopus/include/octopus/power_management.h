#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H

#include <stdint.h>
#include <avr/io.h>

namespace octopus {

class PowerManagement
{
public:
    /**
     * @brief PowerManagement singleton.
     */
    static PowerManagement instance;

    /**
     * @brief List of devices that the PowerManager
     *        can activate or deactivate.
     */
    typedef enum {
        DEV_ADC = _BV(PRADC),
        DEV_USART0 = _BV(PRUSART0),
        DEV_SPI = _BV(PRSPI),
        DEV_TIM1 = _BV(PRTIM1),
        DEV_TIM0 = _BV(PRTIM0),
        DEV_TIM2 = _BV(PRTIM2),
        DEV_TWI = _BV(PRTWI)
    } device_t;

    /**
     * @brief List of locks that can be used to
     *        prevent some clocks to be shut down.
     */
    typedef enum {
        LOCK_IDLE = (1<<0),
        LOCK_USART_TX = (1<<1),
        LOCK_USART_RX = (1<<2),
        LOCK_APP = (1<<3)
    } lock_t;

    /**
     * @brief Represents a clock that can be switched
     *        ON or OFF.
     */
    class Clock {
    public:
        /**
         * @brief Acquires a lock to prevent the
         *        clock from being shut down.
         *
         * @param lock
         *      Clock user.
         */
        void acquire(lock_t lock)
        {
            locks |= lock;
        }

        /**
         * @brief Releases a lock to inform the clock
         *        manager that a particular user does
         *        not need it anymore.
         *
         * @param lock
         *      Clock user.
         */
        void release(lock_t lock)
        {
            locks &= ~lock;
        }

    private:
        Clock() : locks(0) {}
        uint8_t locks;
        friend class PowerManagement;
    };

    Clock clk_IO;
    Clock clk_ADC;
    Clock clk_ASY;
    Clock clk_MAIN;

    // Called from Looper to enter sleep mode.
    void sleep();

private:
    PowerManagement();
    friend class Clock;
};

} /* namespace octopus */

#endif // POWER_MANAGEMENT_H
