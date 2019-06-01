#include <utilslib/callbacks/callbacks.hpp>
#include <cassert>
#include <iostream>

int main()
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
    return 0;
}
