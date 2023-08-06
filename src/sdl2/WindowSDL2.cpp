#include "ZydecoCommon.hpp"
#include "CommonSDL2.hpp"
#include "WindowSDL2.hpp"


static Logger LOGGER("WINDOW");


WindowSDL2::WindowSDL2(std::string title, uint64_t window_config_flags):
    m_windowTitle(title)
{
    LOGGER.Log(Logger::DEBUG, "WindowSDL2 creating ('{}')", title);

    SDL_CallPointerReturningFunction(SDL_CreateWindow, m_pSdlWindow,
        m_windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, window_config_flags);

    SDL_CallPointerReturningFunction(SDL_CreateRenderer, m_pSdlRenderer,
        m_pSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_CallPointerReturningFunction(SDL_GL_CreateContext, m_glContext, m_pSdlWindow);

    SDL_ShowWindow(m_pSdlWindow);

    LOGGER.Log(Logger::DEBUG, "WindowSDL2 created", title);
}

WindowSDL2::~WindowSDL2()
{
    LOGGER.Log(Logger::DEBUG, "Destroying window '{}'", m_windowTitle);
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyRenderer(m_pSdlRenderer);
    SDL_DestroyWindow(m_pSdlWindow);
}

bool WindowSDL2::Update(uint64_t time_since_last_update_us)
{
    LOGGER.Log(Logger::TRACE, "Refreshing SDL window {}", time_since_last_update_us);

    // Update SDL renderer display
    SDL_CallErrorReturningFunction(SDL_RenderClear, m_pSdlRenderer);

    // Update OpenGL context display
    SDL_GL_SwapWindow(m_pSdlWindow);

    SDL_RenderPresent(m_pSdlRenderer);

    return false;
}

void WindowSDL2::SetTitle(std::string new_title)
{
    m_windowTitle = new_title;
    SDL_SetWindowTitle(m_pSdlWindow, m_windowTitle.c_str());
}

void WindowSDL2::SetFullscreen(bool is_fullscreen)
{
    SDL_CallErrorReturningFunction(SDL_SetWindowFullscreen, m_pSdlWindow, is_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void WindowSDL2::SetSize(uint64_t new_width, uint64_t new_height)
{
    SDL_SetWindowSize(m_pSdlWindow, new_width, new_height);
}

void WindowSDL2::SetPosition(uint64_t new_x, uint64_t new_y)
{
    SDL_SetWindowPosition(m_pSdlWindow, new_x, new_y);
}
