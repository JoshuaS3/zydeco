#ifndef ENGINE_HPP_
#define ENGINE_HPP_


#include <chrono>
#include <atomic>
#include <vector>

#include "ZydecoCommon.hpp"
#include "ThreadLooping.hpp"
#include "IEventQuitSubscriber.hpp"
#include "IUpdateable.hpp"


class IEventHandler;
class ITimer;
class Renderer;


class Engine : public IEventQuitSubscriber
{
public:
    Engine(IEventHandler& r_event_handler, ITimer& r_core_timer, Renderer& r_renderer);
    ~Engine();

    void OnQuitEvent() override;

    void Execute();

protected:
    IEventHandler& m_rEventHandler;
    ITimer& m_rCoreTimer;
    Renderer& m_rRenderer;

    std::vector<ThreadLooping*> m_threads;
    std::atomic<bool> m_aIsExiting;
};


#endif /* ENGINE_HPP_ */
