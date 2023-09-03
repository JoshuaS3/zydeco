#ifndef TIMER_SDL2_HPP_
#define TIMER_SDL2_HPP_


#include "IUpdateable.hpp"
#include "ITimer.hpp"


class TimerSDL2 : public ITimer
{
public:
    // TimerSDL2
    TimerSDL2();
    ~TimerSDL2() = default;

    // IUpdateable
    bool Update() override;

    // ITimer
    void Reset() override;
    void SetTimeout(uint64_t timeout_ms) override;
    void Start() override;
    void Stop() override;
    bool IsExpired() override;
    uint64_t *GetGlobalTimePointer() override;

private:
    static uint64_t s_globalCounterMs;
    static bool s_globalCounterInitialized;

    uint64_t m_instanceStartTimeMs;
    uint64_t m_instanceTimeoutMs;
    bool m_instanceRunning;
    bool m_instanceExpired;
};


#endif /* TIMER_SDL2_HPP_ */
