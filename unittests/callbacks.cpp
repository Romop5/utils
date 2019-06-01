#include "catch2/catch.hpp"

#include <utilslib/callbacks.hpp>
#include <cassert>
#include <iostream>

TEST_CASE("Trying to create a simple register callback")
{
    std::cout << "Hello from the other side :)" << std::endl;
    utilslib::Callbacks<std::function<void(int)>> callbacks;

    std::function<void(int)> handler = [](int a)->void { std::cout << "WTF " << a << std::endl;};
    // 1. Create callback
    callbacks.add([](int a)->void { std::cout << "WTF " << a << std::endl;});

    for(auto& handler: callbacks)
    {
        handler(20);
    }
}
