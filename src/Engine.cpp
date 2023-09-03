#include <chrono>
#include <atomic>

#include "ZydecoCommon.hpp"
#include "Engine.hpp"
#include "Renderer.hpp"
#include "ThreadLooping.hpp"
#include "IEventHandler.hpp"
#include "IWindow.hpp"
#include "ITimer.hpp"


#include "GLRenderObjectBackground.hpp"
#include "GLRenderObjectRainbowTriangle.hpp"


Logger LOGGER("Engine");


Engine::Engine(IEventHandler& r_event_handler, ITimer& r_core_timer, Renderer& r_renderer):
    m_rEventHandler(r_event_handler),
    m_rCoreTimer(r_core_timer),
    m_rRenderer(r_renderer)
{
    LOGGER.Log(Logger::TRACE, "Engine()");



    // <in some game logic thread>
    auto bg = new GLRenderObjectBackground {};
    // GLRenderObject.RenderSetUniform<var count, var type>("uniform name", { pointers to vars } )
    bg->RenderSetUniform<1, unsigned int>("time", { r_core_timer.GetGlobalTimePointer() });


    // <in some other game logic thread>
    auto tringle = new GLRenderObjectRainbowTriangle {};
    tringle->RenderSetUniform<1, unsigned int>("time", { r_core_timer.GetGlobalTimePointer() });



    r_event_handler.RegisterQuitEventSubscriber(this);
    std::atomic_init(&m_aIsExiting, false);
}

Engine::~Engine()
{
    LOGGER.Log(Logger::TRACE, "~Engine()");
}

void Engine::OnQuitEvent()
{
    LOGGER.Log(Logger::VERBOSE, "OnQuitEvent(): Quit event received");

    m_aIsExiting.store(true);
}

void Engine::Execute()
{
    LOGGER.Log(Logger::TRACE, "Execute()");

    // Called from main()
    LOGGER.Log(Logger::INFO, "Execute(): Entering engine main loop");

    // Create and start subsystem threads
    LOGGER.Log(Logger::DEBUG, "Execute(): Spawning subsystem threads");

    ThreadLooping event_thread {"Event Handler", m_rEventHandler};
    m_threads.push_back(&event_thread);
    ThreadLooping timer_thread {"Core Timer", m_rCoreTimer};
    m_threads.push_back(&timer_thread);
    ThreadLooping render_thread {"Renderer", m_rRenderer};
    m_threads.push_back(&render_thread);

    for (auto* thread : m_threads)
    {
        thread->Start();
    }

    // Main thread busy wait until signalled to exit, or until a thread exits
    m_rCoreTimer.SetTimeout(1000);
    m_rCoreTimer.Start();
    while (m_aIsExiting.load() == false)
    {
        // While waiting: periodically run debug output commands
        if (m_rCoreTimer.IsExpired())
        {
            LOGGER.Log(Logger::VERBOSE, "Execute(): Dispatching debug commands");
            LOGGER.Log(Logger::VERBOSE, "Execute(): Time: {}", *m_rCoreTimer.GetGlobalTimePointer());
            m_rRenderer.UpdateDebug();
            m_rCoreTimer.Reset();
            m_rCoreTimer.Start();
        }

        // Check for any thread exit
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
    LOGGER.Log(Logger::DEBUG, "Execute(): Signal to quit. Terminating threads...");

    // Signal any running threads to terminate, and wait for termination
    for (auto* thread : m_threads)
    {
        thread->Terminate();
        thread->WaitUntilFinished();
    }

    // All threads terminated. Exit main engine loop...
    LOGGER.Log(Logger::INFO, "Execute(): Exiting engine loop (thread handler)");
}
