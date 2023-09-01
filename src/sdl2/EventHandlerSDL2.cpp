#include <SDL2/SDL.h>

#include "ZydecoCommon.hpp"
#include "CommonSDL2.hpp"
#include "EventHandlerSDL2.hpp"

#include "IEventKeyboardSubscriber.hpp"
#include "IEventMouseSubscriber.hpp"
#include "IEventQuitSubscriber.hpp"
#include "IEventWindowSubscriber.hpp"


static Logger LOGGER("EVENTHANDLER");


#define DISPATCH_EVENT(TYPE, EVENT, VALS...) \
    for (IEvent ## TYPE ## Subscriber *subscriber : m_event ## TYPE ## Subscribers) \
    { \
        if (subscriber == nullptr) { break; } \
        LOGGER.Log(Logger::TRACE, "Dispatching " #TYPE "Event.On" #EVENT); \
        subscriber->On##EVENT(VALS); \
    } \
    break;


EventHandlerSDL2::EventHandlerSDL2()
{
    LOGGER.Log(Logger::DEBUG, "EventHandlerSDL2 creating");
}

EventHandlerSDL2::~EventHandlerSDL2()
{
    LOGGER.Log(Logger::DEBUG, "EventHandlerSDL2 destroying");
}

bool EventHandlerSDL2::Update(uint64_t time_since_last_update_us)
{
    LOGGER.Log(Logger::DEBUG, "Entering EventHandler loop");

    bool quit = false;
    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
        LOGGER.Log(Logger::TRACE, "Received event {}", event.type);

        switch (event.type)
        {
            case SDL_KEYDOWN: DISPATCH_EVENT(Keyboard, KeyPressEvent, event.key.keysym.sym, event.key.keysym.mod);
            case SDL_KEYUP: DISPATCH_EVENT(Keyboard, KeyReleaseEvent, event.key.keysym.sym, event.key.keysym.mod);
            case SDL_MOUSEBUTTONDOWN:
            {
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: DISPATCH_EVENT(Mouse, MouseLeftDownEvent, event.button.x, event.button.y);
                    case SDL_BUTTON_MIDDLE: DISPATCH_EVENT(Mouse, MouseMiddleDownEvent, event.button.x, event.button.y);
                    case SDL_BUTTON_RIGHT: DISPATCH_EVENT(Mouse, MouseRightDownEvent, event.button.x, event.button.y);
                    default: break;
                }
            }
            case SDL_MOUSEBUTTONUP:
            {
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: DISPATCH_EVENT(Mouse, MouseLeftUpEvent, event.button.x, event.button.y);
                    case SDL_BUTTON_MIDDLE: DISPATCH_EVENT(Mouse, MouseMiddleUpEvent, event.button.x, event.button.y);
                    case SDL_BUTTON_RIGHT: DISPATCH_EVENT(Mouse, MouseRightUpEvent, event.button.x, event.button.y);
                    default: break;
                }
            }
            case SDL_MOUSEMOTION: DISPATCH_EVENT(Mouse, MouseMoveEvent, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            case SDL_MOUSEWHEEL: DISPATCH_EVENT(Mouse, MouseWheelScrollEvent, event.motion.xrel, event.motion.yrel);
            case SDL_QUIT: quit = true; DISPATCH_EVENT(Quit, QuitEvent);
            case SDL_WINDOWEVENT:
            {
                switch (event.window.type)
                {
                    case SDL_WINDOWEVENT_MINIMIZED: DISPATCH_EVENT(Window, WindowMinimizedEvent);
                    case SDL_WINDOWEVENT_MAXIMIZED: DISPATCH_EVENT(Window, WindowMaximizedEvent);
                    case SDL_WINDOWEVENT_RESTORED: DISPATCH_EVENT(Window, WindowRestoredEvent);
                    case SDL_WINDOWEVENT_EXPOSED: DISPATCH_EVENT(Window, WindowExposedEvent);
                    case SDL_WINDOWEVENT_RESIZED: DISPATCH_EVENT(Window, WindowResizedEvent, event.window.data1, event.window.data2);
                    case SDL_WINDOWEVENT_CLOSE: DISPATCH_EVENT(Window, WindowRequestedCloseEvent);
                    default: break;
                }
            }
            default: break;
        }

        if (quit) { break; }
    }

    LOGGER.Log(Logger::DEBUG, "Exiting EventHandler loop");

    return true;
}

bool EventHandlerSDL2::RegisterKeyboardEventSubscriber(IEventKeyboardSubscriber *p_event_keyboard_subscriber)
{
    LOGGER.Log(Logger::VERBOSE, "Registering IEventKeyboardSubscriber");

    if (m_eventKeyboardSubscribers.size() >= MAXIMUM_EVENT_SUBSCRIBERS)
    {
        LOGGER.Log(Logger::ERROR, "Failed to register IEventKeyboardSubscriber; too many registered");
        return false;
    }

    m_eventKeyboardSubscribers.push_back(p_event_keyboard_subscriber);
    return true;
}

bool EventHandlerSDL2::RegisterMouseEventSubscriber(IEventMouseSubscriber *p_event_mouse_subscriber)
{
    LOGGER.Log(Logger::VERBOSE, "Registering IEventMouseSubscriber");

    if (m_eventMouseSubscribers.size() >= MAXIMUM_EVENT_SUBSCRIBERS)
    {
        LOGGER.Log(Logger::ERROR, "Failed to register IEventMouseSubscriber; too many registered");
        return false;
    }

    m_eventMouseSubscribers.push_back(p_event_mouse_subscriber);
    return true;
}

bool EventHandlerSDL2::RegisterQuitEventSubscriber(IEventQuitSubscriber *p_event_quit_subscriber)
{
    LOGGER.Log(Logger::VERBOSE, "Registering IEventQuitSubscriber");

    if (m_eventQuitSubscribers.size() >= MAXIMUM_EVENT_SUBSCRIBERS)
    {
        LOGGER.Log(Logger::ERROR, "Failed to register IEventQuitSubscriber; too many registered");
        return false;
    }

    m_eventQuitSubscribers.push_back(p_event_quit_subscriber);
    return true;
}

bool EventHandlerSDL2::RegisterWindowEventSubscriber(IEventWindowSubscriber *p_event_window_subscriber)
{
    LOGGER.Log(Logger::VERBOSE, "Registering IEventWindowSubscriber");

    if (m_eventWindowSubscribers.size() >= MAXIMUM_EVENT_SUBSCRIBERS)
    {
        LOGGER.Log(Logger::ERROR, "Failed to register IEventWindowSubscriber; too many registered");
        return false;
    }

    m_eventWindowSubscribers.push_back(p_event_window_subscriber);
    return true;
}
