#ifndef WINDOW_SDL2_HPP_
#define WINDOW_SDL2_HPP_


#include "IWindow.hpp"
#include <cstdint>
#include <string>
#include <SDL2/SDL.h>

class WindowSDL2 : public IWindow
{
public:
    WindowSDL2(std::string title, uint64_t window_config_flags);
    ~WindowSDL2();

    bool Update(uint64_t time_since_last_update_us) override;

    // Basic public interface
    void SetTitle(std::string new_title) override;
    void SetFullscreen(bool is_fullscreen) override;
    void SetSize(uint64_t new_width, uint64_t new_height) override;
    void SetPosition(uint64_t new_x, uint64_t new_y) override;

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


#endif /* WINDOW_SDL2_HPP_ */
