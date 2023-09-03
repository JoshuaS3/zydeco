#include "ZydecoCommon.hpp"
#include "ThreadLooping.hpp"
#include "IUpdateable.hpp"


static Logger LOGGER("ThreadLooping");


ThreadLooping::ThreadLooping(std::string thread_name, IUpdateable& thread_update):
    m_threadName(thread_name),
    m_rThreadUpdate(thread_update)
{
    LOGGER.Log(Logger::TRACE, "ThreadLooping('{}', ...)", m_threadName);

    std::atomic_init(&m_aShouldThreadTerminate, false);
    std::atomic_init(&m_aIsThreadRunning, false);
}

ThreadLooping::~ThreadLooping()
{
    LOGGER.Log(Logger::TRACE, "~ThreadLooping() for '{}'", m_threadName);
    Terminate();
    WaitUntilFinished();
}

void ThreadLooping::Start()
{
    LOGGER.Log(Logger::TRACE, "Start() for '{}'", m_threadName);

    if (m_aIsThreadRunning.load() == false)
    {
        LOGGER.Log(Logger::VERBOSE, "Start(): Spawning '{}'", m_threadName);
        m_aIsThreadRunning.store(true);
        m_thread = std::thread(&ThreadLooping::ThreadRunLoop, this);
    }
    else
    {
        LOGGER.Log(Logger::WARNING, "Start(): Attempt to spawn '{}' ignored (already running)", m_threadName);
    }
}

void ThreadLooping::Terminate()
{
    LOGGER.Log(Logger::TRACE, "Terminate() for '{}'", m_threadName);

    LOGGER.Log(Logger::VERBOSE, "Terminate(): Attempting to externally terminate '{}'", m_threadName);
    m_aShouldThreadTerminate.store(true);
}

bool ThreadLooping::IsRunning()
{
    return m_aIsThreadRunning.load();
}

void ThreadLooping::WaitUntilFinished()
{
    LOGGER.Log(Logger::TRACE, "WaitUntilFinished() for '{}'", m_threadName);

    if (m_thread.joinable())
    {
        LOGGER.Log(Logger::VERBOSE, "WaitUntilFinished(): Waiting for end of '{}'", m_threadName);
        m_thread.join();
    }
    LOGGER.Log(Logger::VERBOSE, "WaitUntilFinished(): '{}' finished", m_threadName);
}

void ThreadLooping::ThreadRunLoop()
{
    LOGGER.Log(Logger::TRACE, "ThreadRunLoop() for '{}'", m_threadName);

    while (m_aShouldThreadTerminate.load() == false)
    {
        bool should_exit = m_rThreadUpdate.Update();
        if (should_exit) { break; }
    }

    LOGGER.Log(Logger::DEBUG, "ThreadRunLoop(): Thread '{}' exiting", m_threadName);
    m_aIsThreadRunning.store(false);
    return;
}
