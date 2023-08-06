#ifndef ENGINE_HPP_
#define ENGINE_HPP_


#include <chrono>
#include <atomic>
#include <map>
#include <thread>

#include "ZydecoCommon.hpp"
#include "IEventQuitSubscriber.hpp"


class IEventHandler;
class IWindow;


class Engine : public IEventQuitSubscriber
{
public:
    Engine(IEventHandler& r_event_handler, IWindow& r_window);
    ~Engine();

    void OnQuitEvent() override;

    void Start();
    void Kill();

protected:
    IEventHandler& m_rEventHandler;
    IWindow& m_rWindow;

    std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> m_currentTime;

    std::atomic<bool> m_aIsExiting;
    std::map<std::string, std::thread*> m_threads;
    void DoEventLoop();
    void DoRenderLoop();

    std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> m_frameRenderStartTime;
    double m_framerate;
    std::chrono::microseconds m_frameRenderTimeUs;
/*    Scene m_scene;
    Renderer m_renderer;
    EventHandler m_eventHandler;*/
};


#endif /* ENGINE_HPP_ */
