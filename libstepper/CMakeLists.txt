
if(CMAKE_CROSSCOMPILING)

    # Library

    include_directories(
        src
        include
        ../liboctopus/include
    )

    add_library(stepper STATIC
        src/stepper.cpp
        src/avr_stepper.cpp
    )

    # Sample
    add_executable(stepper-sample sample/stepper-sample.cpp)
    target_link_libraries(stepper-sample stepper octopus)
    add_hex(stepper-sample)

else(CMAKE_CROSSCOMPILING)

    # Acceleration

    add_executable(step_table
        step_table/step_table.c
    )

    target_link_libraries(step_table
        m
    )

endif(CMAKE_CROSSCOMPILING)
