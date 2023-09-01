#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_


#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

#include "IUpdateable.hpp"


class IWindow : public IUpdateable
{
public:
    virtual bool Update(uint64_t time_since_last_update_us) = 0;

    // Basic public interface
    virtual void SetTitle(std::string new_title) = 0;
    virtual void SetFullscreen(bool is_fullscreen) = 0;
    virtual void SetSize(uint64_t new_width, uint64_t new_height) = 0;
    virtual void SetPosition(uint64_t new_x, uint64_t new_y) = 0;

    virtual void MakeContextCurrent() = 0;
    virtual void MakeNullCurrent() = 0;
};


#endif /* IWINDOW_HPP_ */
