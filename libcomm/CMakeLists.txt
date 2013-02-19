
# Library

include_directories(
    src
    include
    ../liboctopus/include
)

add_library(comm STATIC
    src/buffer_pool.cpp
    src/cmd_i2c.cpp
    src/cmd_read.cpp
    src/cmd_write.cpp
    src/message_receiver.cpp
    src/message_transmitter.cpp
    src/packet.cpp
)

# Sample

