# Library

include_directories(
    src
    include
    ../liboctopus/include
)

add_library(servo STATIC
    src/servo.cpp
)

# Sample
add_executable(servo-sample sample/servo-sample.cpp)
target_link_libraries(servo-sample servo octopus)
add_hex(servo-sample)
