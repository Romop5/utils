#ifndef UTILSLIB_LOGGER_HPP
#define UTILSLIB_LOGGER_HPP
#include <fstream>
#include <streambuf>

namespace utilslib {
const std::string DEFAULT_LOG_FILENAME = "default_log.txt";

enum class LOG_STATUS
{
    LOG_ALL,
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR,
    LOG_NONE
};

/*
 * @Overrides ofstream serialization to provide support for adding prefix banner
 *
 * Note that operator<< adds banner in the beginning of the stream.
 */
class LoggerStream
{
    private:
    std::ofstream& m_stream;
    std::string m_streamBanner;

    public:
    LoggerStream(std::ofstream& streamHandle, std::string banner): m_stream(streamHandle), m_streamBanner(banner) 
    {
        if(!banner.empty())
            this->m_streamBanner = "["+banner+"] ";
    }
    std::ofstream& getStream() 
    {
        return m_stream;
    }
    std::ofstream& operator<<(const std::string rest)
    {
        m_stream << std::string(m_streamBanner).c_str() << rest.c_str();
        return m_stream;
    }
        
};

/*
 * @Simple logger class for storing notes into output file
 *
 * The class is based on singleton anti-patter. A single instance of logger is
 * created for the whole .exe file. Path can be set using 'openAs()' method.
 * Supports:
 * - prefix banner (e.g. [INFO])
 * - setting verbosity on-the-fly (setVerbosity()), @see LOG_STATUS
 */
class Logger {
private:
    LOG_STATUS m_currentVerbosityLevel;
    std::ofstream m_outputFile;
    std::ofstream m_emptyStream;
    Logger(): m_currentVerbosityLevel(LOG_STATUS::LOG_ALL) {}

public:
    static Logger* getLogger()
    {
        static Logger* logger = NULL;
        if (logger == NULL) {
            logger = new Logger();
        }
        return logger;
    }

    static LoggerStream getDebug() { return getLogger()->getStreamAs(LOG_STATUS::LOG_DEBUG); } 
    static LoggerStream getInfo() { return getLogger()->getStreamAs(LOG_STATUS::LOG_INFO); } 
    static LoggerStream getError() { return getLogger()->getStreamAs(LOG_STATUS::LOG_ERROR); } 

    LoggerStream getStreamAs(LOG_STATUS status)
    {
        std::string banner = "";
        switch(status)
        {
            case LOG_STATUS::LOG_DEBUG: banner = "DEBUG"; break;
            case LOG_STATUS::LOG_INFO: banner = "INFO"; break;
            case LOG_STATUS::LOG_ERROR: banner = "ERROR"; break;
        }
        return LoggerStream(status >= m_currentVerbosityLevel ? m_outputFile : m_emptyStream, banner);
    }

    void openAs(const std::string filename) { m_outputFile.close(); m_outputFile.open(filename, std::ofstream::trunc); }
    void setVerbosity(LOG_STATUS newLevel) { this->m_currentVerbosityLevel = newLevel;}
};
}
#endif
