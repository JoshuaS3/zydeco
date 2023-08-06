#ifndef IEVENT_QUIT_SUBSCRIBER_HPP_
#define IEVENT_QUIT_SUBSCRIBER_HPP_


class IEventQuitSubscriber
{
public:
    virtual void OnQuitEvent() = 0;
};


#endif /* IEVENT_QUIT_SUBSCRIBER_HPP_ */
