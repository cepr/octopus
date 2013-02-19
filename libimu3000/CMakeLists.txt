
include_directories(
    src
    include
)

add_library(imu3000 STATIC
    src/imu3000.cpp
)

