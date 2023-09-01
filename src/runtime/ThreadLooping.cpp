#include "ZydecoCommon.hpp"
#include "ThreadLooping.hpp"
#include "IUpdateable.hpp"


static Logger LOGGER("THREAD_LOOPING");


ThreadLooping::ThreadLooping(std::string thread_name, IUpdateable& thread_update):
    m_threadName(thread_name),
    m_rThreadUpdate(thread_update)
{
    LOGGER.Log(Logger::VERBOSE, "Creating ThreadLooping '{}'", m_threadName);

    std::atomic_init(&m_aShouldThreadTerminate, false);
    std::atomic_init(&m_aIsThreadRunning, false);
}

ThreadLooping::~ThreadLooping()
{
    LOGGER.Log(Logger::VERBOSE, "Destroying ThreadLooping '{}'", m_threadName);
    if (IsRunning())
    {
        Terminate();
        WaitUntilFinished();
    }
}

void ThreadLooping::Start()
{
    if (m_aIsThreadRunning.load() == false)
    {
        LOGGER.Log(Logger::VERBOSE, "Spawning ThreadLooping '{}'", m_threadName);
        m_thread = std::thread(&ThreadLooping::ThreadRunLoop, this);
    }
    else
    {
        LOGGER.Log(Logger::WARNING, "Attempt to start ThreadLooping '{}' ignored (already started)", m_threadName);
    }
}

void ThreadLooping::Terminate()
{
    LOGGER.Log(Logger::VERBOSE, "Attempting to externally terminate ThreadLooping '{}'", m_threadName);
    m_aShouldThreadTerminate.store(true);
}

bool ThreadLooping::IsRunning()
{
    return m_thread.joinable();
}

void ThreadLooping::WaitUntilFinished()
{
    if (IsRunning())
    {
        LOGGER.Log(Logger::VERBOSE, "Waiting for end of ThreadLooping '{}'", m_threadName);
        m_thread.join();
    }
    LOGGER.Log(Logger::VERBOSE, "ThreadLooping '{}' finished", m_threadName);
}

void ThreadLooping::ThreadRunLoop()
{
    m_aIsThreadRunning.store(true);

    while (m_aShouldThreadTerminate.load() == false)
    {
        bool should_exit = m_rThreadUpdate.Update(0);
        if (should_exit) { break; }
    }

    m_aIsThreadRunning.store(false);
}
