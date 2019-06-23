#include "catch2/catch.hpp"
#include <iostream>
#include <fstream>
#include <utilslib/register.hpp>

using firstType = UTILSLIB_SINGLETON_CLASS(first);
#define REGISTER_STRING(str)\
{\
static auto anonym = utilslib::RegisterIt<firstType, const char*>(str);\
}

//REGISTER_STRING("This string has been registered outside any function")

TEST_CASE("Simple load-time register")
{
    REGISTER_STRING("This string was registed during program load-time, before main() was called");
    REGISTER_STRING("This one, too");

    auto globalRegister = utilslib::Register<firstType, const char*>::getInstance();
    std::cout << "Write down all items: " << std::endl;
    // Print out all strings
    for(auto i : *globalRegister)
    {
        const char* str = i;
        printf("Item: %s\n", str);
        //std::cout << str << std::end;
    }
    
    const char* str = "runtime";
    globalRegister->add(str);

    std::cout << "Write down all items: " << std::endl;
    // Print out all strings
    for(auto i : *globalRegister)
    {
        const char* str = i;
        printf("Item: %s\n", str);
        //std::cout << str << std::end;
    }
    
}
