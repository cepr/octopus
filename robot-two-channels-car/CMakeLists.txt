include_directories(../liboctopus/src)
add_executable(robot-two-channels-car src/two_channels_car.cpp)
target_link_libraries(robot-two-channels-car octopus)
add_hex(robot-two-channels-car)
