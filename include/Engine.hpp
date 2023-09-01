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
class Renderer;


class Engine : public IEventQuitSubscriber
{
public:
    Engine(IEventHandler& r_event_handler, Renderer& r_renderer);
    ~Engine();

    void OnQuitEvent() override;

    void Execute();

protected:
    IEventHandler& m_rEventHandler;
    Renderer& m_rRenderer;

    std::vector<ThreadLooping*> m_threads;
    std::atomic<bool> m_aIsExiting;
};


#endif /* ENGINE_HPP_ */
