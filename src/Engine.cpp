#include <chrono>
#include <atomic>

#include <glm/ext.hpp>

#include "ZydecoCommon.hpp"
#include "Engine.hpp"
#include "Renderer.hpp"
#include "ThreadLooping.hpp"
#include "IEventHandler.hpp"
#include "IWindow.hpp"
#include "ITimer.hpp"

#include "GLTexture.hpp"

#include "Mandelbrot.hpp"

#include "GLRenderObjectImGui.hpp"


Logger LOGGER("Engine");


Engine::Engine(IEventHandler& r_event_handler, IWindow& r_window, ITimer& r_core_timer, Renderer& r_renderer)
{
    LOGGER.Log(Logger::TRACE, "Engine()");

    auto settings = new MandelbrotSettings;
    auto mandelbrot = new Mandelbrot(r_event_handler, r_window, settings);
    auto imgui = new GLRenderObjectImGui(settings);

    m_jobs.push_back(&r_event_handler);
    m_jobs.push_back(&r_core_timer);
    m_jobs.push_back(mandelbrot);
    m_jobs.push_back(&r_renderer);

    r_event_handler.RegisterQuitEventSubscriber(this);
}

Engine::~Engine()
{
    LOGGER.Log(Logger::TRACE, "~Engine()");
}

void Engine::OnQuitEvent()
{
    LOGGER.Log(Logger::VERBOSE, "OnQuitEvent(): Quit event received");

    m_isExiting = true;
}

void Engine::Execute()
{
    LOGGER.Log(Logger::TRACE, "Execute()");

    if (m_jobs.size() > 0)
    {
        LOGGER.Log(Logger::INFO, "Execute(): Entering engine main loop");

        while (!m_isExiting)
        {
            for (auto job : m_jobs)
            {
                m_isExiting = job->Update();
                if (m_isExiting) { break; }
            }
        }
    }
    else
    {
        LOGGER.Log(Logger::WARNING, "Execute(): No jobs in queue");
    }

    // All threads terminated. Exit main engine loop...
    LOGGER.Log(Logger::INFO, "Execute(): Exiting engine loop (thread handler)");
}
