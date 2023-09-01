#include <cstdint>


#include "SDL2/SDL.h"
#include "GL/gl3w.h"


#include "Renderer.hpp"
#include "IWindow.hpp"


Renderer::Renderer(IWindow& r_window):
    m_rWindow(r_window)
{

};

bool Renderer::Update(uint64_t time_since_last_update_us)
{
    m_rWindow.MakeContextCurrent();
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_rWindow.Update(1);
    return false;
}
