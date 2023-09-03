#ifndef EVENT_HANDLER_SDL2_HPP_
#define EVENT_HANDLER_SDL2_HPP_


#include <cstdint>
#include <vector>

#include "IEventHandler.hpp"


class IEventKeyboardSubscriber;
class IEventMouseSubscriber;
class IEventQuitSubscriber;
class IEventWindowSubscriber;


class EventHandlerSDL2 : public IEventHandler
{
public:
    EventHandlerSDL2();
    ~EventHandlerSDL2();

    bool Update() override;

    bool RegisterKeyboardEventSubscriber(IEventKeyboardSubscriber *p_event_keyboard_subscriber) override;
    bool RegisterMouseEventSubscriber(IEventMouseSubscriber *p_event_mouse_subscriber) override;
    bool RegisterQuitEventSubscriber(IEventQuitSubscriber *p_event_quit_subscriber) override;
    bool RegisterWindowEventSubscriber(IEventWindowSubscriber *p_event_window_subscriber) override;

private:
    static constexpr uint64_t MAXIMUM_EVENT_SUBSCRIBERS = 8;

    std::vector<IEventKeyboardSubscriber*> m_eventKeyboardSubscribers;
    std::vector<IEventMouseSubscriber*>    m_eventMouseSubscribers;
    std::vector<IEventQuitSubscriber*>     m_eventQuitSubscribers;
    std::vector<IEventWindowSubscriber*>   m_eventWindowSubscribers;
};


#endif /* EVENT_HANDLER_SDL2_HPP_ */
