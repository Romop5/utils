#include "catch2/catch.hpp"
#include <iostream>
#include <fstream>
#include <utilslib/lookuptable.hpp>


constexpr size_t incTest(size_t i)
{
    return i;
}

TEST_CASE("Simple LUT table")
{
    // Create 0,1,2,3...,9 in compile-time
    auto lut = utilslib::Lookuptable<size_t, 0, 10>::computeIt(incTest);
    REQUIRE(lut[0] == 0);
    REQUIRE(lut[1] == 1);
    std::cout << "Testing LUT Table" << std::endl;
    for(auto &element: lut)
        std::cout << "Element: " << element << std::endl;
}

constexpr size_t fib(size_t i)
{
    return (i < 2)?1:fib(i-1)+fib(i-2);
}

TEST_CASE("Fibonaci")
{
    auto lut = utilslib::Lookuptable<size_t, 0, 30>::computeIt(fib);
    REQUIRE(lut[0] == 1);
    REQUIRE(lut[1] == 1);
    REQUIRE(lut[2] == 2);
    REQUIRE(lut[3] == 3);
    REQUIRE(lut[4] == 5);
    std::cout << "Testing FIB Table" << std::endl;
    for(auto &element: lut)
        std::cout << "Element: " << element << std::endl;
}
