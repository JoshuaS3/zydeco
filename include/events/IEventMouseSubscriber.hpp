#ifndef IEVENT_MOUSE_SUBSCRIBER_HPP
#define IEVENT_MOUSE_SUBSCRIBER_HPP


#include <cstdint>


class IEventMouseSubscriber
{
public:
    virtual void OnMouseLeftDownEvent(uint64_t x, uint64_t y) = 0;
    virtual void OnMouseLeftUpEvent(uint64_t x, uint64_t y) = 0;

    virtual void OnMouseMiddleDownEvent(uint64_t x, uint64_t y) = 0;
    virtual void OnMouseMiddleUpEvent(uint64_t x, uint64_t y) = 0;

    virtual void OnMouseRightDownEvent(uint64_t x, uint64_t y) = 0;
    virtual void OnMouseRightUpEvent(uint64_t x, uint64_t y) = 0;

    virtual void OnMouseMoveEvent(uint64_t x, uint64_t y, int64_t dx, int64_t dy) = 0;

    virtual void OnMouseWheelScrollEvent(int64_t dx, int64_t dy) = 0;
};


#endif /* IEVENT_MOUSE_SUBSCRIBER_HPP */
