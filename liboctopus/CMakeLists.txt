
# Library

include_directories(
    src
    include
)

add_library(octopus STATIC
#    src/analog_channel.cpp
#    src/analog_to_digital_converter.cpp
    src/async_operation.cpp
    src/avr_looper.cpp
    src/avr_timer.cpp
    src/avr_timer0.cpp
    src/avr_two_wire_interface.cpp
    src/avr_usart.cpp
    src/blink.cpp
    src/fatal.cpp
    src/i2c.cpp
#    src/servo.cpp
    src/timer.cpp
)

# Squeleton sample
add_executable(squeleton-sample sample/squeleton-sample.cpp)
target_link_libraries(squeleton-sample octopus)
add_hex(squeleton-sample)

# Blink sample
add_executable(blink-sample sample/blink-sample.cpp)
target_link_libraries(blink-sample octopus)
add_hex(blink-sample)

# Usart sample
add_executable(usart-sample sample/usart-sample.cpp)
target_link_libraries(usart-sample octopus)
add_hex(usart-sample)
