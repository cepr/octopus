#ifdef __AVR__

#include "octopus/avr_stepper.h"
#include "octopus/fatal.h"

namespace octopus {

AvrStepper::AvrStepper(volatile uint8_t *port,
                       uint8_t pinA1,
                       uint8_t pinA2,
                       uint8_t pinB1,
                       uint8_t pinB2,
                       Mode mode,
                       const uint16_t *speed_lookup_table,
                       speed_t max_speed) :
    Stepper(speed_lookup_table, max_speed),
    port(port),
    gpio_mask(_BV(pinA1) | _BV(pinA2) | _BV(pinB1) | _BV(pinB2)),
    mode(mode)
{
    gpio_sequence[0] = _BV(pinA1) | _BV(pinB1);
    gpio_sequence[1] = _BV(pinB1);
    gpio_sequence[2] = _BV(pinB1) | _BV(pinA2);
    gpio_sequence[3] = _BV(pinA2);
    gpio_sequence[4] = _BV(pinA2) | _BV(pinB2);
    gpio_sequence[5] = _BV(pinB2);
    gpio_sequence[6] = _BV(pinB2) | _BV(pinA1);
    gpio_sequence[7] = _BV(pinA1);

    if (port == &PORTB) {
        DDRB |= gpio_mask;
    } else if (port == &PORTC) {
        DDRC |= gpio_mask;
    } else if (port == &PORTD) {
        DDRD |= gpio_mask;
    } else {
        fatal(FATAL_INVALID_PARAMETER);
    }

    step();
}

void AvrStepper::step()
{
    uint8_t sequence = (uint8_t)current_pos;

    if (mode != MODE_HALF_STEPPING) {
        sequence <<= 1;
    }

    if (mode == MODE_WAVE_DRIVE) {
        sequence++;
    }

    sequence &= 7;

    _MMIO_BYTE(port) = (_MMIO_BYTE(port) & (~gpio_mask)) | gpio_sequence[sequence];
}

} /* namespace octopus */

#endif /* __AVR__ */
