include_directories(../liboctopus/src)
add_executable(robot-gpio src/gpio.cpp)
target_link_libraries(robot-gpio octopus)
add_hex(robot-gpio)
