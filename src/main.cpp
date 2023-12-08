#include <iostream>

#include "ZydecoCommon.hpp"
#include "CommonSDL2.hpp"
#include "EventHandlerSDL2.hpp"
#include "WindowSDL2.hpp"
#include "TimerSDL2.hpp"
#include "Renderer.hpp"
#include "Engine.hpp"


static Logger LOGGER("main");

static const char *ZYDECO_TERMOUT[] = {
    "Zydeco v0.1.0 Copyright (c) Joshua Stockin 2023",
    "<https://joshstock.in> <josh@joshstock.in>",
};


void on_terminate(void)
{
    ZydecoFault("PROGRAM TERMINATED UNEXPECTEDLY.");
}

int main(int argc, char *argv[])
{
    // Print boilerplate copyright output
    for (const char *line : ZYDECO_TERMOUT)
    {
        std::cout << line << std::endl;
    }

    // Runtime environment setup
    std::set_terminate(static_cast<std::terminate_handler>(on_terminate));

    // Initialize logging
    Logger::InitializeLogging(Logger::VERBOSE, &std::cout);
    LOGGER.Log(Logger::INFO, "main(): Logging initialized");

    // Initialize SDL environment
    LOGGER.Log(Logger::INFO, "main(): Initializing SDL...");
    SDL_CallErrorReturningFunction(SDL_Init, SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    LOGGER.Log(Logger::INFO, "main(): SDL initialized");

    // Load ImGui
    LOGGER.Log(Logger::INFO, "main(): Loading ImGui...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //imgui_io.ConfigDockingWithShift = false;

    // Create subsystems
    LOGGER.Log(Logger::INFO, "main(): Creating subsystems...");
    EventHandlerSDL2 sdl_event_handler {};
    WindowSDL2 sdl_window {"Zydeco", SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE};
    TimerSDL2 sdl_core_timer {};

    // Load OpenGL
    LOGGER.Log(Logger::INFO, "main(): Loading OpenGL with GL3W...");

    sdl_window.MakeContextCurrent();
    int gl3wRes = gl3wInit();
    if (gl3wRes != 0)
    {
        ZydecoFault("gl3wInit failed ({})", gl3wRes);
    }

    if (!gl3wIsSupported(GL_VERSION_MAJOR, GL_VERSION_MINOR))
    {
        ZydecoFault("OpenGL/GL3W {}.{} not supported", GL_VERSION_MAJOR, GL_VERSION_MINOR);
    }

    LOGGER.Log(Logger::DEBUG, "main(): OpenGL {}, GLSL {}", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    LOGGER.Log(Logger::DEBUG, "main(): Renderer: {}", glGetString(GL_RENDERER));
    LOGGER.Log(Logger::INFO, "main(): OpenGL loaded with GL3W");

    TimerSDL2 sdl_renderer_timer {};
    Renderer gl_renderer {sdl_event_handler, sdl_window, sdl_renderer_timer};

    LOGGER.Log(Logger::INFO, "main(): Subsystems created");

    // Create engine
    LOGGER.Log(Logger::INFO, "main(): Creating engine...");
    Engine engine {sdl_event_handler, sdl_window, sdl_core_timer, gl_renderer};
    LOGGER.Log(Logger::INFO, "main(): Engine created");

    // Enter loop
    LOGGER.Log(Logger::INFO, "main(): Entering engine loop");
    engine.Execute();

    // Engine exited
    LOGGER.Log(Logger::INFO, "main(): Engine exited");

    // Quit ImGui
    LOGGER.Log(Logger::INFO, "main(): Quitting ImGui");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Quit SDL
    LOGGER.Log(Logger::INFO, "main(): Quitting SDL");
    SDL_Quit();

    // Exiting program
    LOGGER.Log(Logger::INFO, "main(): Exiting");
    return 0;
}
