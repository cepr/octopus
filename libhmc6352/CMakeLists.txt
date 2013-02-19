# Library

include_directories(
    src
    include
    ../liboctopus/include
)

add_library(hmc6352 STATIC
    src/hmc6352.cpp
)

# Sample

include_directories(
    ../liboctopus/src
)

add_executable(hmc6352-sample
    sample/hmc6352-sample.cpp
)

target_link_libraries(hmc6352-sample
    hmc6352
    octopus
)

add_hex(hmc6352-sample)

