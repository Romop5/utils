#ifndef C_LOG_HPP
#define C_LOG_HPP
#include <fstream>
#include <streambuf>

namespace utilslib {
const std::string DEFAULT_LOG_FILENAME = "default_log.txt";

enum LOG_STATUS
{
    DEBUG,
    INFO,
    ERROR
};

class LoggerStream
{
    private:
    std::ofstream m_stream;
    std::string m_streamBanner;

    public:
    LoggerStream(std::ofstream streamHandle, const std::string& banner): m_streamBanner(banner), m_stream(streamHandle) {}
    std::ofstream& getStream() 
    {
        return m_stream;
    }
    std::ofstream& operator<<(const std::string rest)
    {
        m_stream << std::string("[WTF] ") << rest;
        return m_stream;
    }
        
};

class Logger {
private:

    std::ofstream m_outputFile;
    Logger() {}

public:
    static Logger* getLogger()
    {
        static Logger* logger = NULL;
        if (logger == NULL) {
            logger = new Logger();
        }
        return logger;
    }

    static LoggerStream& asDebug() { return getLogger()->m_outputStream; } const

    LoggerStream& getStreamAs(LOG_STATUS status)
    {
        switch(status)
        {
            case DEBUG: return LoggerStream(m_outputStream, "DEBUG"):
            case INFO: return LoggerStream(m_outputStream, "INFO"):
            case ERROR: return LoggerStream(m_outputStream, "ERROR"):
        }
    }

    void openAs(const std::string filename) { m_outputStream.getStream().open(filename); }
};
}
#endif
