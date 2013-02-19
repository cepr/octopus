
set(CMAKE_SYSTEM_NAME atmega328p-8mhz)
set(MCU atmega328p)
set(F_CPU 16000000L)

set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_FIND_ROOT_PATH /usr/lib/gcc/avr)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -Wall -Os -fpack-struct -fshort-enums -fno-exceptions -fno-threadsafe-statics -mmcu=${MCU} -DF_CPU=${F_CPU}")

function(add_hex target)
  add_custom_command(TARGET ${target}
                     POST_BUILD
                     COMMAND avr-objcopy -R .eeprom -O ihex $<TARGET_FILE:${target}> ${target}.hex
                     COMMENT "Generating ${target}.hex")
endfunction(add_hex)
