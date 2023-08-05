#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <chrono>

#include <ZydecoCommon.hpp>
#include "IUpdateable.hpp"
#include "Window.hpp"

class Engine : public IUpdateable
{
public:
    Engine();
    ~Engine();

    void Start();
    void Kill();

    bool Update(uint64_t time_since_last_update_us);

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_tickStartTime;
    uint64_t m_tickLengthUs;
    Window m_sdlWindow;
/*    Scene m_scene;
    Renderer m_renderer;
    EventHandler m_eventHandler;*/
};

#endif /* ENGINE_HPP_ */
