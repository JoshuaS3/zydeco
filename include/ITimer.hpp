#ifndef ITIMER_HPP_
#define ITIMER_HPP_


#include <cstdint>
#include "IUpdateable.hpp"


class ITimer : public IUpdateable
{
public:
    // IUpdateable
    virtual bool Update() = 0;

    // ITimer
    virtual void Reset() = 0;
    virtual void SetTimeout(uint64_t timeout_ms) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool IsExpired() = 0;
    virtual uint64_t *GetGlobalTimePointer() = 0;
};


#endif /* ITIMER_HPP_ */
