#include <fmt/core.h>

#include "ZydecoCommon.hpp"
#include "Logger.hpp"

static Logger LOGGER("LOGGER");

// static initialize members
std::ostream *Logger::s_ostream = nullptr;
Logger::Verbosity Logger::s_maxVerbosity = Logger::DEBUG;
int Logger::s_loggerNameLongestLen = 0;


static const char *VERBOSITY_STRINGS[] = {
    "", // DISABLED
    "\e[1;031m[   ERROR ]\e[0m",
    "\e[1;033m[ WARNING ]\e[0m",
    "\e[1;034m[    INFO ]\e[0m",
    "\e[1;035m[   DEBUG ]\e[0m",
    "\e[1;036m[ VERBOSE ]\e[0m",
    "\e[1;037m[   TRACE ]\e[0m",
};

// ctor
Logger::Logger(std::string logger_name):
    m_loggerName(logger_name),
    m_loggerNameLen(logger_name.length())
{
    if (m_loggerNameLen > s_loggerNameLongestLen) { s_loggerNameLongestLen = m_loggerNameLen; }
}

// should be called once
void Logger::InitializeLogging(Verbosity max_verbosity, std::ostream *stream)
{
    if (stream != nullptr)
    {
        s_maxVerbosity = max_verbosity;
        s_ostream = stream;

        LOGGER.Log(INFO, "Initialized logger with max verbosity {0}", VERBOSITY_STRINGS[max_verbosity]);
    }
}

// output debug message
void Logger::Log(Verbosity verbosity, std::string message)
{
    if (s_ostream != nullptr && verbosity <= s_maxVerbosity)
    {
        if (s_loggerNameLongestLen != m_loggerNameLongestLen)
        {
            m_loggerNameLongestLen = s_loggerNameLongestLen;

            int left_padding_count = m_loggerNameLongestLen - m_loggerNameLen;
            char left_padding[left_padding_count + 1];

            for (int i = 0; i < left_padding_count; i++)
            {
                left_padding[i] = ' ';
            }
            left_padding[left_padding_count] = '\0';
            m_leftPadding = std::string(left_padding);
        }
        *s_ostream << VERBOSITY_STRINGS[verbosity] << m_leftPadding << " \e[090m" << m_loggerName << "\e[0m :: " << message << "\n";
    }
}
