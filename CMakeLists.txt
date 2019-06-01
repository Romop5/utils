CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

option(UTILSLIB_UNIT "Compiles unittests" OFF)

add_library(utilslib INTERFACE )
target_include_directories(utilslib INTERFACE src)

if(UTILSLIB_UNIT)
    add_executable(unittests unittests/callbacks.cpp)
    target_link_libraries(unittests utilslib)
endif()
