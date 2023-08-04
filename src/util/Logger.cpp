#include <fmt/core.h>

#include "ZydecoCommon.hpp"
#include "Logger.hpp"

static Logger LOGGER("LOGGER");

// static initialize members
std::ostream *Logger::s_ostream = nullptr;
Logger::Verbosity Logger::s_maxVerbosity = Logger::DEBUG;


static const char *VERBOSITY_STRINGS[] = {
    "", // DISABLED
    "\e[1;031m[ERROR]\e[0m",
    "\e[1;033m[WARNING]\e[0m",
    "\e[1;034m[INFO]\e[0m",
    "\e[1;035m[DEBUG]\e[0m",
    "\e[1;036m[VERBOSE]\e[0m",
    "\e[1;037m[TRACE]\e[0m",
};

// ctor
Logger::Logger(std::string logger_name):
    m_loggerName(logger_name)
{

}

// should be called once
void Logger::InitializeLogging(Verbosity max_verbosity, std::ostream *stream)
{
    if (stream != nullptr)
    {
        s_maxVerbosity = max_verbosity;
        s_ostream = stream;

        std::string message = fmt::format("Initialized logger with max verbosity {0}", VERBOSITY_STRINGS[max_verbosity]);
        LOGGER.Log(INFO, message);
    }
}

// output debug message
void Logger::Log(Verbosity verbosity, std::string message)
{
    if (s_ostream != nullptr && verbosity <= s_maxVerbosity)
    {
        *s_ostream << VERBOSITY_STRINGS[verbosity] << " \e[090m" << m_loggerName << "\e[0m: " << message << "\n";
    }
}
