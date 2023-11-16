#ifndef ENGINE_HPP_
#define ENGINE_HPP_


#include <chrono>
#include <atomic>
#include <vector>

#include "ZydecoCommon.hpp"
#include "IEventQuitSubscriber.hpp"
#include "IUpdateable.hpp"


class IEventHandler;
class IWindow;
class ITimer;
class Renderer;


class Engine : public IEventQuitSubscriber
{
public:
    Engine(IEventHandler& r_event_handler, IWindow& r_window, ITimer& r_core_timer, Renderer& r_renderer);
    ~Engine();

    void OnQuitEvent() override;

    void Execute();

protected:
    std::vector<IUpdateable*> m_jobs;
    bool m_isExiting = false;
};


#endif /* ENGINE_HPP_ */
