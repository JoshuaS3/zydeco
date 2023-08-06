#ifndef IEVENT_KEYBOARD_SUBSCRIBER_HPP_
#define IEVENT_KEYBOARD_SUBSCRIBER_HPP_


#include <cstdint>


class IEventKeyboardSubscriber
{
public:
    virtual void OnKeyPressEvent(uint64_t key_code, uint64_t key_mod) = 0;
    virtual void OnKeyReleaseEvent(uint64_t key_code, uint64_t key_mod) = 0;
};


#endif /* IEVENT_KEYBOARD_SUBSCRIBER_HPP_ */
