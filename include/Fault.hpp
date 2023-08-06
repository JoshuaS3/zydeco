#ifndef FAULT_HPP_
#define FAULT_HPP_


#include <fmt/format.h>

[[noreturn]] void ZydecoFault(std::string fault_message);

template<typename... Args>
[[noreturn]] void ZydecoFault(fmt::format_string<Args...> fault_message, Args&&... args)
{
    ZydecoFault(fmt::vformat(fault_message, fmt::make_format_args(args...)));
}



#endif /* FAULT_HPP_ */
