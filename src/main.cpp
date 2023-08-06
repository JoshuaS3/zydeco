#include <iostream>
#include <thread>

#include "ZydecoCommon.hpp"
#include "EventHandlerSDL2.hpp"
#include "WindowSDL2.hpp"
#include "Engine.hpp"

static Logger LOGGER("MAIN");

static const char *ZYDECO_TERMOUT[] = {
    "Zydeco v0.1.0 Copyright (c) Joshua Stockin 2023",
    "<https://joshstock.in> <josh@joshstock.in>",
};

void on_terminate(void)
{
    ZydecoFault("TERMINATED");
}

int main(int argc, char *argv[])
{
    // Print boilerplate copyright output
    for (const char *line : ZYDECO_TERMOUT)
    {
        std::cout << line << std::endl;
    }

    std::set_terminate((std::terminate_handler)on_terminate);

    Logger::InitializeLogging(Logger::VERBOSE, &std::cout);
    LOGGER.Log(Logger::INFO, "Logging initialized.");

    EventHandlerSDL2 sdl_event_handler {};
    WindowSDL2 sdl_window {"Zydeco", SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE};

    LOGGER.Log(Logger::INFO, "Creating engine...");
    Engine engine(sdl_event_handler, sdl_window);

    LOGGER.Log(Logger::INFO, "Entering engine loop");
    engine.Start();

    LOGGER.Log(Logger::INFO, "Exiting");

    return 0;
}
