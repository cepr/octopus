
# Library

include_directories(
    src
    include
    ../liboctopus/include
)

add_library(lv_max_sonar_ez STATIC
    src/lv_max_sonar_ez.cpp
)
