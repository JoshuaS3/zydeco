#include <iostream>
#include <thread>

#include "ZydecoCommon.hpp"
#include "Engine.hpp"

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
        std::cout << line << std::endl;
    }

    Logger::InitializeLogging(Logger::VERBOSE, &std::cout);
    LOGGER.Log(Logger::INFO, "Logging initialized.");

    LOGGER.Log(Logger::INFO, "Creating game...");
    Engine engine {};

    LOGGER.Log(Logger::INFO, "Entering game loop");
    engine.Start();

    LOGGER.Log(Logger::INFO, "Exiting game loop");

    return 0;
}
