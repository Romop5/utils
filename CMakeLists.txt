CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

option(UTILSLIB_UNIT "Compiles unittests" OFF)

add_library(utilslib INTERFACE )
target_include_directories(utilslib INTERFACE src)

if(UTILSLIB_UNIT)
    enable_testing()
    add_subdirectory(unittests)
endif()
