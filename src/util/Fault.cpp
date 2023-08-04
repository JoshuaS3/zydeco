#include <cstdlib>
#include <cpptrace/cpptrace.hpp>
#include "ZydecoCommon.hpp"

static Logger LOGGER("FAULT");

[[noreturn]] void ZydecoFault(std::string fault_message)
{
    LOGGER.Log(Logger::ERROR, fault_message);
    cpptrace::print_trace();
    std::abort();
}
