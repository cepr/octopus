include_directories(../liboctopus/src)
add_executable(robot-eve src/eve.cpp)
target_link_libraries(robot-eve octopus)
add_hex(robot-eve)
