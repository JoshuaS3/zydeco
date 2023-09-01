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

    SDL_CallPointerReturningFunction(SDL_GL_CreateContext, m_glContextMain, m_pSdlWindow);

    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_CallErrorReturningFunction(SDL_GL_SetSwapInterval, 1);

    SDL_ShowWindow(m_pSdlWindow);

    LOGGER.Log(Logger::DEBUG, "WindowSDL2 created", title);
}

WindowSDL2::~WindowSDL2()
{
    LOGGER.Log(Logger::DEBUG, "Destroying window '{}'", m_windowTitle);
    SDL_GL_DeleteContext(m_glContextRender);
    SDL_GL_DeleteContext(m_glContextMain);
    SDL_DestroyWindow(m_pSdlWindow);
}

void WindowSDL2::MakeContextCurrent()
{
    SDL_CallErrorReturningFunction(SDL_GL_MakeCurrent, m_pSdlWindow, m_glContextMain);
}

void WindowSDL2::MakeNullCurrent()
{
    SDL_CallErrorReturningFunction(SDL_GL_MakeCurrent, m_pSdlWindow, nullptr);
}

bool WindowSDL2::Update(uint64_t time_since_last_update_us)
{
    LOGGER.Log(Logger::TRACE, "Refreshing SDL window {} {}", SDL_GL_GetSwapInterval(), time_since_last_update_us);

    SDL_GL_SwapWindow(m_pSdlWindow);

    SDL_Delay(1);

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
