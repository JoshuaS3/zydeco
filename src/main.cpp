#include <iostream>
#include <fmt/core.h>

using std::cout;
using std::endl;

#include "ZydecoCommon.hpp"
#include "Window.hpp"
static Logger LOGGER("MAIN");

static const char *ZYDECO_TERMOUT[] = {
    "Zydeco v0.1.0 Copyright (c) Joshua Stockin 2023",
    "<https://joshstock.in> <josh@joshstock.in>",
};

int main(int argc, char *argv[])
{
    // Print boilerplate copyright output
    for (const char *line : ZYDECO_TERMOUT)
    {
        cout << line << endl;
    }

    Logger::InitializeLogging(Logger::TRACE, &std::cout);
    LOGGER.Log(Logger::INFO, "Entering main routine");

    LOGGER.Log(Logger::INFO, "Creating SDL window");
    Window w = Window("Zydeco");

    while(1){}
    return 0;
}
