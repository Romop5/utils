#include "catch2/catch.hpp"
#include <iostream>
#include <fstream>
#include <utilslib/logger.hpp>
#include <utilslib/stringserializer.hpp>
#include <cstring>


TEST_CASE("Test basic logger functionality such as writing to real file, writin with banner, etc")
{
    auto logger = utilslib::Logger::getLogger();
    REQUIRE(logger != NULL);

    logger->openAs("test.output");
    logger->getDebug() << "Ehlo" << std::endl;

    // Check out if file was created
    std::ifstream file;
    file.open("test.output",std::fstream::in);
    REQUIRE(file.is_open() != false);

    char line[255];
    std::memset(line, 0, 255);

    file.getline(line, 254);


    std::string referenceString = "[DEBUG] Ehlo";
    auto fileContentAsHexDump = utilslib::toHex(line,1);
    auto referenceStringAsHexDump = utilslib::toHex(referenceString,1);
    // Compare strings
    std::cout << line << "[" << fileContentAsHexDump << "]" << " vs " << referenceString << "[" << referenceStringAsHexDump<< "]" << std::endl; 
    REQUIRE(line == referenceString);

}

TEST_CASE("Test verbosity - NONE")
{
    // Clear file
    auto logger = utilslib::Logger::getLogger();
    REQUIRE(logger != NULL);

    logger->openAs("test.output");
    logger->setVerbosity(utilslib::LOG_STATUS::NONE);
    logger->getDebug() << "Ehlo" << std::endl;

    std::ifstream file;
    file.open("test.output",std::fstream::in);
    REQUIRE(file.is_open() != false);
    std::string content;
    file >> content;

    // The file should not contain anything but new line character.
    REQUIRE(content.size() == 0);


}

TEST_CASE("Test verbosity - INFO")
{
    // Clear file
    auto logger = utilslib::Logger::getLogger();
    REQUIRE(logger != NULL);

    logger->openAs("test.output");
    logger->setVerbosity(utilslib::LOG_STATUS::INFO);
    logger->getDebug() << "Ehlo" << std::endl;

    std::ifstream file;
    file.open("test.output",std::fstream::in);
    REQUIRE(file.is_open() != false);
    std::string content;
    file >> content;

    // The file should not contain anything but new line character.
    REQUIRE(content.size() == 0);


}
