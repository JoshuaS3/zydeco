#include <iostream>
#include <thread>

#include <SDL2/SDL.h>
#include "GL/gl3w.h"
#include <GL/gl.h>

#include "ZydecoCommon.hpp"
#include "CommonSDL2.hpp"
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

    // Runtime environment setup
    std::set_terminate((std::terminate_handler)on_terminate);

    // Initialize logging
    Logger::InitializeLogging(Logger::VERBOSE, &std::cout);
    LOGGER.Log(Logger::INFO, "Logging initialized");

    // Initialize SDL environment
    LOGGER.Log(Logger::INFO, "Initializing SDL...");
    SDL_CallErrorReturningFunction(SDL_Init, SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    LOGGER.Log(Logger::INFO, "SDL initialized");

    // Create subsystems
    LOGGER.Log(Logger::INFO, "Creating subsystems...");
    EventHandlerSDL2 sdl_event_handler {};
    WindowSDL2 sdl_window {"Zydeco", SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE};
    
    // Load OpenGL
    LOGGER.Log(Logger::INFO, "Loading OpenGL with GL3W...");

    int gl3wRes = gl3wInit();
    if (gl3wRes != 0)
    {
        ZydecoFault("gl3wInit failed ({})", gl3wRes);
    }

    if (!gl3wIsSupported(GL_VERSION_MAJOR, GL_VERSION_MINOR))
    {
        ZydecoFault("OpenGL/GL3W {}.{} not supported", GL_VERSION_MAJOR, GL_VERSION_MINOR);
    }

    LOGGER.Log(Logger::DEBUG, "OpenGL {}, GLSL {}", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    LOGGER.Log(Logger::INFO, "OpenGL loaded with GL3W");

    LOGGER.Log(Logger::INFO, "Subsystems created");

    // Create engine
    LOGGER.Log(Logger::INFO, "Creating engine...");
    Engine engine {sdl_event_handler, sdl_window};
    LOGGER.Log(Logger::INFO, "Engine created");

    // Enter loop
    LOGGER.Log(Logger::INFO, "Entering engine loop");
    engine.Execute();

    // Loop returned
    LOGGER.Log(Logger::INFO, "Exiting engine loop");

    return 0;
}
