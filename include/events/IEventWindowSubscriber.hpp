#ifndef IEVENT_WINDOW_SUBSCRIBER_HPP_
#define IEVENT_WINDOW_SUBSCRIBER_HPP_


#include <cstdint>


class IEventWindowSubscriber
{
public:
    virtual void OnWindowMinimizedEvent() = 0;
    virtual void OnWindowMaximizedEvent() = 0;
    virtual void OnWindowRestoredEvent() = 0;
    virtual void OnWindowExposedEvent() = 0;
    virtual void OnWindowResizedEvent(uint64_t new_width, uint64_t new_height) = 0;
    virtual void OnWindowRequestedCloseEvent() = 0;
};


#endif /* IEVENT_WINDOW_SUBSCRIBER_HPP_ */
