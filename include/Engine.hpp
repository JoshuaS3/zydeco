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

    void Execute();

protected:
    IEventHandler& m_rEventHandler;
    IWindow& m_rWindow;

    std::atomic<bool> m_aIsExiting;
    std::atomic<bool> m_aSceneUpdated;
    std::map<std::string, std::thread*> m_threads;
    void DoEventLoop();
    void DoRenderLoop();

    std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> m_currentTime;

    double m_framerate;
    std::chrono::microseconds m_frameRenderTimeUs;
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> m_frameRenderStartTime;
};


#endif /* ENGINE_HPP_ */
