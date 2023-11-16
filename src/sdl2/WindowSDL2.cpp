#include "ZydecoCommon.hpp"
#include "CommonSDL2.hpp"
#include "WindowSDL2.hpp"


static Logger LOGGER("WindowSDL2");


WindowSDL2::WindowSDL2(std::string title, uint64_t window_config_flags):
    m_windowTitle(title)
{
    LOGGER.Log(Logger::TRACE, "WindowSDL2() for '{}'", title);

    SDL_CallPointerReturningFunction(SDL_CreateWindow, m_pSdlWindow,
        m_windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, window_config_flags);

    SDL_CallPointerReturningFunction(SDL_GL_CreateContext, m_glContextMain, m_pSdlWindow);

    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_RED_SIZE, 8);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_GREEN_SIZE, 8);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_BLUE_SIZE, 8);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_ALPHA_SIZE, 8);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_CallErrorReturningFunction(SDL_GL_SetAttribute, SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_CallErrorReturningFunction(SDL_GL_SetSwapInterval, 1);

    ImGui_ImplSDL2_InitForOpenGL(m_pSdlWindow, m_glContextMain);
    ImGui_ImplOpenGL3_Init();

    SDL_ShowWindow(m_pSdlWindow);
}

WindowSDL2::~WindowSDL2()
{
    LOGGER.Log(Logger::TRACE, "~WindowSDL2() for {}", m_windowTitle);
    SDL_GL_DeleteContext(m_glContextMain);
    SDL_DestroyWindow(m_pSdlWindow);
}

void WindowSDL2::MakeContextCurrent()
{
    SDL_CallErrorReturningFunction(SDL_GL_MakeCurrent, m_pSdlWindow, m_glContextMain);
}

void WindowSDL2::MakeNullCurrent()
{
    LOGGER.Log(Logger::TRACE, "MakeNullCurrent() for '{}'", m_windowTitle);
    SDL_CallErrorReturningFunction(SDL_GL_MakeCurrent, m_pSdlWindow, nullptr);
}

bool WindowSDL2::Update()
{
    SDL_GL_SwapWindow(m_pSdlWindow);

    SDL_Delay(1);

    return false;
}

void WindowSDL2::SetTitle(std::string new_title)
{
    LOGGER.Log(Logger::TRACE, "SetTitle({}) for '{}'", new_title, m_windowTitle);
    m_windowTitle = new_title;
    SDL_SetWindowTitle(m_pSdlWindow, m_windowTitle.c_str());
}

void WindowSDL2::SetFullscreen(bool is_fullscreen)
{
    LOGGER.Log(Logger::TRACE, "SetFullscreen({}) for '{}'", is_fullscreen, m_windowTitle);
    SDL_CallErrorReturningFunction(SDL_SetWindowFullscreen, m_pSdlWindow, is_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void WindowSDL2::SetSize(uint64_t new_width, uint64_t new_height)
{
    LOGGER.Log(Logger::TRACE, "SetSize(x: {}, y: {}) for '{}'", new_width, new_height, m_windowTitle);
    SDL_SetWindowSize(m_pSdlWindow, new_width, new_height);
}

void WindowSDL2::SetPosition(uint64_t new_x, uint64_t new_y)
{
    LOGGER.Log(Logger::TRACE, "SetPosition(x: {}, y: {}) for '{}'", new_x, new_y, m_windowTitle);
    SDL_SetWindowPosition(m_pSdlWindow, new_x, new_y);
}

int WindowSDL2::GetWidth()
{
    LOGGER.Log(Logger::TRACE, "GetWidth() for '{}'", m_windowTitle);
    int w;
    SDL_GL_GetDrawableSize(m_pSdlWindow, &w, nullptr);
    return w;
}

int WindowSDL2::GetHeight()
{
    LOGGER.Log(Logger::TRACE, "GetHeight() for '{}'", m_windowTitle);
    int h;
    SDL_GL_GetDrawableSize(m_pSdlWindow, nullptr, &h);
    return h;
}
