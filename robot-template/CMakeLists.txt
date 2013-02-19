include_directories(
    ../libcomm/src
    ../liboctopus/src
)

add_executable(robot-template
    src/template.cpp
)

target_link_libraries(robot-template
    comm
    octopus
)

add_hex(robot-template)
