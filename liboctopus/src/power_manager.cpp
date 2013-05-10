#include "octopus/power_manager.h"

#include <avr/io.h>
#include <avr/sleep.h>

namespace octopus {

PowerManager PowerManager::instance;

PowerManager::PowerManager()
{
    PRR = _BV(PRADC) | // PRADC: Power Reduction ADC
            //_BV(PRUSART0) | // Power Reduction USART0
            _BV(PRSPI) | // Power Reduction Serial Peripheral Interface
            _BV(PRTIM1) | // Power Reduction Timer/Counter1
            _BV(PRTIM0) | // Power Reduction Timer/Counter0
            //_BV(PRTIM2) | // Power Reduction Timer/Counter2
            _BV(PRTWI); // Power Reduction TWI
}

void PowerManager::sleep()
{
    if (!clk_IO.locks) {
        if (!clk_ADC.locks) {
            if (!clk_ASY.locks) {
                if (!clk_MAIN.locks) {
                    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
                } else {
                    set_sleep_mode(SLEEP_MODE_STANDBY);
                }
            } else {
                if (!clk_MAIN.locks) {
                    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
                } else {
                    set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
                }
            }
        } else {
            set_sleep_mode(SLEEP_MODE_ADC);
        }
    } else {
        set_sleep_mode(SLEEP_MODE_IDLE);
    }

    sleep_enable();
    sleep_cpu();
    sleep_disable();
}

} /* namespace octopus */
