#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <ostream>
#include <string>

class Logger
{
public:
    Logger(std::string logger_name);
    ~Logger() = default;

    enum Verbosity
    {
        DISABLED,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        VERBOSE,
        TRACE,
    };

    static void InitializeLogging(Verbosity max_verbosity, std::ostream *ostream);

    void Log(Verbosity verbosity, std::string message);

protected:
    static std::ostream *s_ostream;
    static Verbosity s_maxVerbosity;

    std::string m_loggerName;
};

#endif /* LOGGER_HPP_ */
