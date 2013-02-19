include_directories(../liboctopus/src)
add_executable(robot-xcopter src/xcopter.cpp)
target_link_libraries(robot-xcopter octopus)
add_hex(robot-xcopter)
