#include <chrono>
#include <atomic>
#include <thread>

#include "ZydecoCommon.hpp"
#include "Engine.hpp"
#include "IEventHandler.hpp"
#include "IWindow.hpp"


Logger LOGGER("ENGINE");
Logger RENDER_LOGGER("ENGINE::RENDER");

Engine::Engine(IEventHandler& r_event_handler, IWindow& r_window):
    m_rEventHandler(r_event_handler),
    m_rWindow(r_window),
    m_framerate(60),
    m_frameRenderTimeUs(static_cast<int64_t>(1'000'000 / m_framerate))
{
    LOGGER.Log(Logger::INFO, "Initializing engine");
    LOGGER.Log(Logger::DEBUG, "Frame render time: {}us", m_frameRenderTimeUs.count());

    r_event_handler.RegisterQuitEventSubscriber(this);

    std::atomic_init(&m_aIsExiting, false);
}

Engine::~Engine()
{
    LOGGER.Log(Logger::DEBUG, "Destroy engine");
}

void Engine::OnQuitEvent()
{
    LOGGER.Log(Logger::DEBUG, "Received QuitEvent");

    m_aIsExiting.store(true);
}

void Engine::Start()
{
    LOGGER.Log(Logger::INFO, "Entering engine loop (thread handler)");

    LOGGER.Log(Logger::DEBUG, "Starting event handler thread");
    std::thread event_thread(&Engine::DoEventLoop, this);
    m_threads["Event Handler"] = &event_thread;

    LOGGER.Log(Logger::DEBUG, "Starting render thread");
    std::thread render_thread(&Engine::DoRenderLoop, this);
    m_threads["Renderer"] = &render_thread;

    // std::thread(&Engine::DoEventLoop, this);
    // std::thread(&Engine::DoGameLoop, this);

    // Step clock while subsystems are running
    while (m_aIsExiting.load() == false)
    {
        m_currentTime = std::chrono::time_point_cast<std::chrono::microseconds, std::chrono::steady_clock, std::chrono::nanoseconds>(
            std::chrono::steady_clock::now()
        );
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    // Subsystem signaled exiting
    LOGGER.Log(Logger::DEBUG, "Signal to quit");

    // Wait for program completion
    for (auto active_thread : m_threads)
    {
        while (active_thread.second->joinable()) {
            LOGGER.Log(Logger::DEBUG, "Exiting thread {}", active_thread.first);
            active_thread.second->join();
        }
    }

    LOGGER.Log(Logger::INFO, "Exiting engine loop (thread handler)");
}

void Engine::Kill()
{

}

void Engine::DoEventLoop()
{
    m_rEventHandler.Update(0);

    m_aIsExiting.store(true);
}

void Engine::DoRenderLoop()
{
    RENDER_LOGGER.Log(Logger::DEBUG, "Starting render loop");

    std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> expected_end_time;
    std::chrono::microseconds time_since_last_tick;
    std::chrono::microseconds remaining_time_before_next_tick;

    // Loop while not exiting
    while (m_aIsExiting.load() == false)
    {
        // Calculate time since last tick, update tick start/end times
        time_since_last_tick = std::chrono::duration_cast<std::chrono::microseconds>(m_currentTime - m_frameRenderStartTime);
        m_frameRenderStartTime = m_currentTime;
        expected_end_time = m_currentTime + m_frameRenderTimeUs;

        // Update system with time since last tick
        bool exiting = m_rWindow.Update(time_since_last_tick.count());
        if (exiting) { break; }

        // Calculate remaining tick time; if >0, sleep until next tick
        remaining_time_before_next_tick = expected_end_time - m_currentTime;
        if (remaining_time_before_next_tick.count() > 0)
        {
            std::this_thread::sleep_until(expected_end_time);
        }
        else
        {
            int64_t tick_time = (m_currentTime - m_frameRenderStartTime).count();
            RENDER_LOGGER.Log(Logger::WARNING, "Overutilized! Tick time: {}us ({} ticks per second)", tick_time, 1'000'000./(float)tick_time);
        }
    }

    RENDER_LOGGER.Log(Logger::INFO, "Exiting render loop");
    m_aIsExiting.store(true);
    std::this_thread::yield();
}

/*
class Engine
{
public:
    Engine();
    ~Engine();

    void Start();
    void Kill();

    void Update();

protected:
    Window m_sdlWindow;
    Scene m_scene;
    Renderer m_renderer;
    EventHandler m_eventHandler;
};
*/
