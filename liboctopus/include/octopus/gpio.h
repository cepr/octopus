#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include "octopus/async_operation.h"
#include "octopus/timer.h"

namespace octopus {

/**
 * @brief General Purpose Input/Output (GPIO)
 *
 * This class manages all the ATmega328P GPIOs.
 */
class Gpio: private Timer::Task
{
public:

    /**
     * GPIO direction.
     */
    typedef enum {
        INPUT, /**< GPIO is used as input */
        OUTPUT  /**< GPIO is used as output */
    } direction_t;

    /**
     * @brief Sets GPIO direction.
     *
     * @param direction
     *      @arg @a INPUT for input
     *      @arg @a OUTPUT for output
     */
    void setDirection(direction_t direction) const;

    /**
     * @brief Sets the pin value HIGH.
     *
     * If the GPIO is configured in input, this methods activates the internal
     * pull-up, otherwise it sets the output latch to HIGH.
     */
    inline void set() const {
        _MMIO_BYTE(port) |= _BV(pin_number);
    }

    /**
     * @brief Sets the pin value.
     *
     * @param value
     *      @arg `false` to set the pin to LOW
     *      @arg `true` to set the pin to HIGH
     */
    inline void set(bool value) const {
        if (value) {
            set();
        } else {
            clear();
        }
    }

    /**
     * @brief Clears the pin value (LOW).
     *
     * If the GPIO is configured in input, this methods deactivate the internal
     * pull-up, otherwise it clears the output latch to LOW.
     */
    inline void clear() const {
        _MMIO_BYTE(port) &= ~_BV(pin_number);
    }

    /**
     * @brief Generates a timed pulse.
     *
     * @param value
     *      @arg `false` to set the pulse to LOW.
     *      @arg `true` to set the pulse to HIGH.
     *
     * @param duration
     *      Duration of the pulse in microseconds.
     */
    void pulse(bool value, Timer::time_us_t width);

    /**
     * @brief Activates the internal pull-up.
     */
    inline void activatePullUp() {
        set();
    }

    /**
     * @brief De-activates the internal pull-up.
     */
    inline void deactivatePullUp() {
        clear();
    }

    /**
     * @brief Gets the GPIO input value.
     *
     * @return
     *      @arg `false` if GPIO is reading low
     *      @arg `true` if GPIO is reading high
     */
    inline bool get() const {
        return (_MMIO_BYTE(pin) >> pin_number) & 1;
    }

    /**
     * @brief Abstract base class for GPIO pin change listeners.
     *
     * Override this class and implement the method onPinChange() to
     * get notified about GPIO pin changes.
     *
     * @see #registerListener()
     */
    class Listener: public AsyncOperation {
    public:
        Listener(Looper *looper = 0) :
            AsyncOperation(looper)
        {
        }
    protected:
        virtual void onPinChange() = 0;
    private:
        // From AsyncOperation
        void onFinished()
        {
            onPinChange();
        }
    };

    /**
     * @brief Registers a listener on pin change interrupt.
     *
     * @param[in] listener
     *      Listener to be called when the GPIO input pin changes.
     *
     * @see #unregisterListener()
     */
    void registerListener(Listener* listener);

    /**
     * @brief Unregister the listener.
     *
     * @see #registerListener()
     */
    void unregisterListener(Listener* listener);

    static Gpio B0;
    static Gpio B1;
    static Gpio B2;
    static Gpio B3;
    static Gpio B4;
    static Gpio B5;
    static Gpio B6;
    static Gpio B7;

    static Gpio C0;
    static Gpio C1;
    static Gpio C2;
    static Gpio C3;
    static Gpio C4;
    static Gpio C5;
    static Gpio C6;

    static Gpio D0;
    static Gpio D1;
    static Gpio D2;
    static Gpio D3;
    static Gpio D4;
    static Gpio D5;
    static Gpio D6;
    static Gpio D7;

private:
    // Private constructor
    Gpio(uint8_t bank,
         uint8_t pin_number);

    // From Timer::Task used to generate pulse
    void run(Timer::time_us_t when, char what);

    const uint8_t bank;
    const uint8_t pin_number;
    volatile uint8_t const *pin;
    volatile uint8_t const *port;
    bool pulse_value;
};

} /* namespace octopus */

#endif // GPIO_H
