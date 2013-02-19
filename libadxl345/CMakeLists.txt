
# Library

include_directories(
    src
    include
    ../liboctopus/include
)

add_library(adxl345 STATIC
    src/adxl345.cpp
    src/adxl345_register.cpp
)

# Sample

include_directories(
    ../liboctopus/src
)

add_executable(adxl345-sample
    sample/adxl345-sample.cpp
)

target_link_libraries(adxl345-sample
    adxl345
    octopus
)

add_hex(adxl345-sample)
