#include <SDL2/SDL.h>
#include "ZydecoCommon.hpp"
#include "Window.hpp"
#include <GL/gl.h>

static Logger LOGGER("WINDOW");

#define SDL_CallErrorReturningFunction(FUNC_NAME, PARAMS...) \
    if (FUNC_NAME(PARAMS) < 0) \
    { \
        std::string fault_message = fmt::format(#FUNC_NAME " error: {}", SDL_GetError()); \
        ZydecoFault(fault_message); \
    }

#define SDL_CallPointerReturningFunction(FUNC_NAME, NEW_PTR, PARAMS...) \
    NEW_PTR = FUNC_NAME(PARAMS); \
    if (NEW_PTR == nullptr) \
    { \
        std::string fault_message = fmt::format(#FUNC_NAME " error: {}", SDL_GetError()); \
        ZydecoFault(fault_message); \
    }

// Static initialize
bool Window::s_sdlInitialized = false;

Window::Window(std::string title, uint64_t sdl_window_flags):
    m_windowTitle(title)
{
    _SdlInitialize();

    LOGGER.Log(Logger::INFO, fmt::format("SDL Creating OpenGL Window (\"{}\")", title));

    SDL_CallPointerReturningFunction(SDL_CreateWindow, m_pSdlWindow,
        m_windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, sdl_window_flags);

    SDL_CallPointerReturningFunction(SDL_CreateRenderer, m_pSdlRenderer,
        m_pSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_CallPointerReturningFunction(SDL_GL_CreateContext, m_pGlContext, m_pSdlWindow);

    Update(0);

    SDL_ShowWindow(m_pSdlWindow);

    SDL_CallErrorReturningFunction(SDL_GL_SetSwapInterval, 1);
}

Window::~Window()
{
    LOGGER.Log(Logger::DEBUG, fmt::format("Destroying window {}", m_windowTitle));
    SDL_GL_DeleteContext(m_pGlContext);
    SDL_DestroyRenderer(m_pSdlRenderer);
    SDL_DestroyWindow(m_pSdlWindow);
}

bool Window::Update(uint64_t time_since_last_update_us)
{
    // Update SDL renderer display
    SDL_CallErrorReturningFunction(SDL_RenderClear, m_pSdlRenderer);

    // Update OpenGL context display
    glClearColor(0.18, 0.1, 0.18, 1.);
    SDL_GL_SwapWindow(m_pSdlWindow);

    SDL_RenderPresent(m_pSdlRenderer);

    return HandleEvents();
}

void Window::SetTitle(std::string new_title)
{
    m_windowTitle = new_title;
    SDL_SetWindowTitle(m_pSdlWindow, m_windowTitle.c_str());
}

void Window::SetFullscreen(bool is_fullscreen)
{
    SDL_CallErrorReturningFunction(SDL_SetWindowFullscreen, m_pSdlWindow, is_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void Window::SetSize(uint64_t new_width, uint64_t new_height)
{
    SDL_SetWindowSize(m_pSdlWindow, new_width, new_height);
}

void Window::SetPosition(uint64_t new_x, uint64_t new_y)
{
    SDL_SetWindowPosition(m_pSdlWindow, new_x, new_y);
}

bool Window::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        LOGGER.Log(Logger::TRACE, fmt::format("Received event: {}", event.type));
        switch (event.type)
        {
            case SDL_QUIT:
                LOGGER.Log(Logger::DEBUG, fmt::format("Received SDL_QUIT event"));
                return false;
        }
    }
    return true;
}

void Window::_SdlInitialize()
{
    if (s_sdlInitialized) { return; }

    LOGGER.Log(Logger::INFO, "SDL Init");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::string fault_message = fmt::format("SDL_Init error: {}", SDL_GetError());
        ZydecoFault(fault_message);
    }

    s_sdlInitialized = true;
}
