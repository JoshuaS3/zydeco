#include <chrono>
#include <atomic>

#include "ZydecoCommon.hpp"
#include "Engine.hpp"
#include "Renderer.hpp"
#include "ThreadLooping.hpp"
#include "IEventHandler.hpp"
#include "IWindow.hpp"


Logger LOGGER("ENGINE");
Logger EVENT_LOGGER("ENGINE::EVENT");
Logger RENDER_LOGGER("ENGINE::RENDER");


Engine::Engine(IEventHandler& r_event_handler, Renderer& r_renderer):
    m_rEventHandler(r_event_handler),
    m_rRenderer(r_renderer)
{
    LOGGER.Log(Logger::TRACE, "Engine::Engine()");

    r_event_handler.RegisterQuitEventSubscriber(this);
    std::atomic_init(&m_aIsExiting, false);
}

Engine::~Engine()
{
    LOGGER.Log(Logger::TRACE, "Engine::~Engine()");
}

void Engine::OnQuitEvent()
{
    LOGGER.Log(Logger::VERBOSE, "QuitEvent occurred. Trigger exit.");

    m_aIsExiting.store(true);
}

void Engine::Execute()
{
    // Called from main()
    LOGGER.Log(Logger::INFO, "Entering engine loop (thread handler)");

    // Create and start subsystem threads
    LOGGER.Log(Logger::DEBUG, "Spawning subsystem threads");

    ThreadLooping event_thread {"Event Handler", m_rEventHandler};
    m_threads.push_back(&event_thread);
    ThreadLooping render_thread {"Renderer", m_rRenderer};
    m_threads.push_back(&render_thread);

    for (auto* thread : m_threads)
    {
        thread->Start();
    }

    // Main thread busy wait until signalled to exit, or until a thread exits
    while (m_aIsExiting.load() == false)
    {
        for (auto* thread : m_threads)
        {
            if (thread->IsRunning() == false)
            {
                m_aIsExiting.store(true);
                break;
            }
        }
    }

    // Subsystem signaled exiting
    LOGGER.Log(Logger::DEBUG, "Signal to quit");

    // Signal any running threads to terminate, and wait for termination
    for (auto* thread : m_threads)
    {
        if (thread->IsRunning())
        {
            thread->Terminate();
            thread->WaitUntilFinished();
        }
    }

    // All threads terminated. Exit main engine loop...
    LOGGER.Log(Logger::INFO, "Exiting engine loop (thread handler)");
}
