#ifndef UTILSLIB_STRINGSERIALIZER_HPP
#define UTILSLIB_STRINGSERIALIZER_HPP
#include <string>
#include <sstream>
namespace utilslib
{
    std::string createSpacePadding(size_t length)
    {
        // Note: hopefully, this gonna lead to tail-recursion optimization
        if(length == 0)
            return "";
        else
            return " "+createSpacePadding(length-1);
    }
    std::string toHex(const std::string inputString,size_t paddingSize)
    {
        std::stringstream outputStream;
        std::string padding = createSpacePadding(paddingSize);
        outputStream << std::hex;
        for(auto character: inputString)
        {
            outputStream << static_cast<size_t>(character) << padding;
        }
        return outputStream.str();
    }
}//utilslib
#endif
