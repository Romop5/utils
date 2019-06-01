add_subdirectory(Catch2)


add_executable(unittests
    callbacks.cpp
    logger.cpp
    main.cpp
    )

target_link_libraries(unittests utilslib)

# Unit testing framework in C++
target_link_libraries(unittests Catch2)

# Run test
add_test(utilslibTest unittests)
