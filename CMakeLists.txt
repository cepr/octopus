cmake_minimum_required(VERSION 2.8)

project(octopus CXX C)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(liblv-max-sonar-ez)
    add_subdirectory(libadxl345)
#    add_subdirectory(libprinceton-rf)
    add_subdirectory(liboctopus)
    add_subdirectory(libhmc6352)
#    add_subdirectory(libimu3000)
#    add_subdirectory(libcomm)
endif(CMAKE_CROSSCOMPILING)

add_subdirectory(libstepper)
