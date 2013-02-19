include_directories(../liboctopus/src ../libcomm/src)
add_executable(robot-loopback src/loopback.cpp)
target_link_libraries(robot-loopback octopus comm)
add_hex(robot-loopback)
