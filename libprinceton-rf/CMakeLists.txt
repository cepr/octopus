include_directories(./src)
add_library(princeton_rf STATIC
    src/princeton_rf_decoder.cpp
    src/princeton_rf_encoder.cpp
    src/rf_remote.cpp
)

