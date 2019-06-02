#include "catch2/catch.hpp"
#include <iostream>
#include <fstream>
#include <utilslib/logger.hpp>


TEST_CASE("A simple logger API test")
{
/*    auto logger = utilslib::Logger::getLogger();
    REQUIRE(logger != NULL);

    logger->openAs("test.output");
    logger->getStream() << "Ehlo" << std::endl;

    // Check out if file was created
    std::ifstream file;
    file.open("test.output",std::fstream::in);
    REQUIRE(file.is_open() != false);
    std::string content;
    file >> content;

    // Compare strings
    std::cout << content << " vs " << "Ehlo" << std::endl; 
    REQUIRE(content == "Ehlo");
*/
    auto logger = utilslib::Logger::getLogger();
    logger->openAs("test.output");
    logger->setVerbosity(utilslib::LOG_STATUS::ALL);
    logger->getDebug() << "Hello from the other side" << std::endl;
    logger->getInfo() << "Hello from the other side" << std::endl;

}
