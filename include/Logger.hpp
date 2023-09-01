#ifndef LOGGER_HPP_
#define LOGGER_HPP_


#include <ostream>
#include <string>
#include <fmt/format.h>


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

    template<typename... Args>
    void Log(Verbosity verbosity, fmt::format_string<Args...> message, Args&&... args)
    {
        Log(verbosity, fmt::vformat(message, fmt::make_format_args(args...)));
    }

protected:
    static std::ostream *s_ostream;
    static Verbosity s_maxVerbosity;
    static int s_loggerNameLongestLen;

    std::string m_loggerName;
    std::string m_leftPadding;
    int m_loggerNameLen;
    int m_loggerNameLongestLen;
};


#endif /* LOGGER_HPP_ */
