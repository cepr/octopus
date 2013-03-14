
#include "octopus/gpio.h"
#include "octopus/lock.h"
#include "octopus/list.h"
#include "octopus/avr_timer.h"

namespace octopus {

namespace {

// Definition of a GPIO bank
typedef struct {
    volatile uint8_t *pin;
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pcmsk;
} gpio_bank_t;

// GPIO banks
const gpio_bank_t BANKS[] = {
    {
        &PINB,
        &DDRB,
        &PORTB,
        &PCMSK0
    },
    {
        &PINC,
        &DDRC,
        &PORTC,
        &PCMSK1
    },
    {
        &PIND,
        &DDRD,
        &PORTD,
        &PCMSK2
    }
};

List<Gpio::Listener> listeners[3];

} /* anonymous namespace */

Gpio Gpio::B0(0, 0);
Gpio Gpio::B1(0, 1);
Gpio Gpio::B2(0, 2);
Gpio Gpio::B3(0, 3);
Gpio Gpio::B4(0, 4);
Gpio Gpio::B5(0, 5);
Gpio Gpio::B6(0, 6);
Gpio Gpio::B7(0, 7);

Gpio Gpio::C0(1, 0);
Gpio Gpio::C1(1, 1);
Gpio Gpio::C2(1, 2);
Gpio Gpio::C3(1, 3);
Gpio Gpio::C4(1, 4);
Gpio Gpio::C5(1, 5);
Gpio Gpio::C6(1, 6);

Gpio Gpio::D0(2, 0);
Gpio Gpio::D1(2, 1);
Gpio Gpio::D2(2, 2);
Gpio Gpio::D3(2, 3);
Gpio Gpio::D4(2, 4);
Gpio Gpio::D5(2, 5);
Gpio Gpio::D6(2, 6);
Gpio Gpio::D7(2, 7);

Gpio::Gpio(uint8_t bank,
           uint8_t pin_number) :
    bank(bank),
    pin_number(pin_number),
    pin(BANKS[bank].pin),
    port(BANKS[bank].port)
{
}

void Gpio::setDirection(direction_t direction) const
{
    if (direction == OUTPUT) {
        _MMIO_BYTE(BANKS[bank].ddr) |= _BV(pin_number);
    } else {
        _MMIO_BYTE(BANKS[bank].ddr) &= ~_BV(pin_number);
    }
}

void Gpio::pulse(bool value, Timer::time_us_t width)
{
    // Abort any previous pulse
    AvrTimer::instance.cancel(this);

    // Start the pulse
    pulse_value = value;
    set(value);

    // Program the Timer::Task to stop the pulse
    AvrTimer::instance.schedule(this, AvrTimer::instance.now() + width);
}

// Called when the pulse is over
void Gpio::run(Timer::time_us_t when, char what)
{
    set(!pulse_value);
}

void Gpio::registerListener(Listener *listener)
{
    Lock l;
    // Configure interrupts
    _MMIO_BYTE(BANKS[bank].pcmsk) |= _BV(pin_number);
    PCICR |= _BV(bank);
    // Add listener
    listeners[bank].insert(listener);
}

void Gpio::unregisterListener(Listener* listener)
{
    Lock l;
    // Remove listener
    listeners[bank].remove(listener);
    // Deactivate interrupts
    _MMIO_BYTE(BANKS[bank].pcmsk) &= ~_BV(pin_number);
    if (!_MMIO_BYTE(BANKS[bank].pcmsk)) {
        // No other GPIO interrupt on this bank, we can deactivate interrupts on the complete bank
        PCICR &= ~_BV(bank);
    }
}

ISR(PCINT0_vect)
{
    List<Gpio::Listener>::Iterator it;
    for (it = listeners[0].begin(); it.is_valid(); ++it) {
        (*it)->post();
    }
}

ISR(PCINT1_vect)
{
    List<Gpio::Listener>::Iterator it;
    for (it = listeners[1].begin(); it.is_valid(); ++it) {
        (*it)->post();
    }
}

ISR(PCINT2_vect)
{
    List<Gpio::Listener>::Iterator it;
    for (it = listeners[2].begin(); it.is_valid(); ++it) {
        (*it)->post();
    }
}

} /* namespace octopus */
