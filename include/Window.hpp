#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cstdint>
#include <string>
#include <SDL2/SDL.h>

class Window
{
public:
    Window(std::string title);
    ~Window();

    void SetTitle(std::string new_title);
    void SetFullscreen(bool is_fullscreen);
    void SetSize(uint64_t new_width, uint64_t new_height);
    void SetPosition(uint64_t new_x, uint64_t new_y);

protected:
    SDL_Window *sdl_window;
};

#endif /* WINDOW_HPP_ */
