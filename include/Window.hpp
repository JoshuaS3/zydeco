#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cstdint>
#include <SDL2/SDL.h>
#include "IUpdateable.hpp"

class Window : public IUpdateable
{
public:
    Window(std::string title, uint64_t sdl_window_flags);
    ~Window();

    // Basic public interface
    bool Update(uint64_t time_since_last_update_us);
    void SetTitle(std::string new_title);
    void SetFullscreen(bool is_fullscreen);
    void SetSize(uint64_t new_width, uint64_t new_height);
    void SetPosition(uint64_t new_x, uint64_t new_y);
    bool HandleEvents();

protected:
    // One-time SDL_Init()
    static bool s_sdlInitialized;
    static void _SdlInitialize();

    // Window object info
    SDL_Window *m_pSdlWindow;
    SDL_Renderer *m_pSdlRenderer;
    SDL_GLContext m_pGlContext;
    std::string m_windowTitle;
};

#endif /* WINDOW_HPP_ */
