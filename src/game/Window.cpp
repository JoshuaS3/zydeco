#include <SDL2/SDL.h>
#include "ZydecoCommon.hpp"
#include "Window.hpp"

static Logger LOGGER("WINDOW");

Window::Window(std::string title)
{
    LOGGER.Log(Logger::INFO, "SDL Init");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | 39812398123) < 0)
    {
        std::string fault_message = fmt::format("SDL_Init error {}", SDL_GetError());
        ZydecoFault(fault_message);
    }

    LOGGER.Log(Logger::INFO, "SDL Create Window");
    sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (sdl_window == nullptr)
    {
        std::string fault_message = fmt::format("SDL_CreateWindow error {}", SDL_GetError());
        ZydecoFault(fault_message);
    }

    SDL_ShowWindow(sdl_window);
}

Window::~Window()
{

}

void Window::SetTitle(std::string new_title)
{
    SDL_SetWindowTitle(sdl_window, new_title.c_str());
}

void Window::SetFullscreen(bool is_fullscreen)
{

}

void SetSize(uint64_t new_width, uint64_t new_height)
{

}

void SetPosition(uint64_t new_x, uint64_t new_y)
{

}
