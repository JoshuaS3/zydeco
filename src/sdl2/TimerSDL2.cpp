#include <SDL2/SDL.h>

#include "ZydecoCommon.hpp"
#include "TimerSDL2.hpp"


static Logger LOGGER("TimerSDL2");

// static initialize members
uint64_t TimerSDL2::s_globalCounterMs = 0;
bool TimerSDL2::s_globalCounterInitialized = false;


TimerSDL2::TimerSDL2()
{
    LOGGER.Log(Logger::TRACE, "TimerSDL2()");
    if (!s_globalCounterInitialized)
    {
        LOGGER.Log(Logger::DEBUG, "TimerSDL2(): First TimerSDL2 instance created...");
        if (SDL_WasInit(SDL_INIT_EVENTS) & SDL_INIT_EVENTS)
        {
            LOGGER.Log(Logger::DEBUG, "TimerSDL2(): SDL timer was initialized correctly");
            s_globalCounterInitialized = true;
            s_globalCounterMs = SDL_GetTicks64();
        }
        else
        {
            LOGGER.Log(Logger::DEBUG, "TimerSDL2(): SDL timer was not initialized correctly");
        }
    }
}

// IUpdateable
bool TimerSDL2::Update()
{
    if (!s_globalCounterInitialized)
    {
        LOGGER.Log(Logger::ERROR, "Update(): SDL timer was not initialized correctly");
        return true;
    }
    s_globalCounterMs = SDL_GetTicks64();
    SDL_Delay(1);
    return false;
}

// ITimer
void TimerSDL2::Reset()
{
    m_instanceExpired = false;
    m_instanceRunning = false;
    m_instanceStartTimeMs = -1;
}

void TimerSDL2::SetTimeout(uint64_t timeout_ms)
{
    m_instanceTimeoutMs = timeout_ms;
}

void TimerSDL2::Start()
{
    if (!m_instanceRunning)
    {
        m_instanceStartTimeMs = s_globalCounterMs;
        m_instanceRunning = true;
    }
}

void TimerSDL2::Stop()
{
    if (m_instanceRunning)
    {
        m_instanceRunning = false;
        m_instanceExpired = (s_globalCounterMs >= (m_instanceStartTimeMs + m_instanceTimeoutMs));
    }
}

bool TimerSDL2::IsExpired()
{
    if (m_instanceExpired) { return true; }
    if (s_globalCounterMs >= (m_instanceStartTimeMs + m_instanceTimeoutMs))
    {
        m_instanceRunning = false;
        m_instanceExpired = true;
        return true;
    }
    return false;
}

uint64_t *TimerSDL2::GetGlobalTimePointer()
{
    return &s_globalCounterMs;
}
