#ifndef IEVENT_HANDLER_HPP_
#define IEVENT_HANDLER_HPP_


#include <cstdint>

#include "IUpdateable.hpp"


class IEventKeyboardSubscriber;
class IEventMouseSubscriber;
class IEventQuitSubscriber;
class IEventWindowSubscriber;


class IEventHandler : public IUpdateable
{
public:
    virtual bool Update(uint64_t time_since_last_update_us) = 0;

    virtual bool RegisterKeyboardEventSubscriber(IEventKeyboardSubscriber *p_event_keyboard_subscriber) = 0;
    virtual bool RegisterMouseEventSubscriber(IEventMouseSubscriber *p_event_mouse_subscriber) = 0;
    virtual bool RegisterQuitEventSubscriber(IEventQuitSubscriber *p_event_quit_subscriber) = 0;
    virtual bool RegisterWindowEventSubscriber(IEventWindowSubscriber *p_event_window_subscriber) = 0;
};


#endif /* IEVENT_HANDLER_HPP_ */
