#ifndef THREAD_LOOPING_HPP_
#define THREAD_LOOPING_HPP_


#include <thread>
#include <atomic>
#include <string>

#include "IThread.hpp"


class IUpdateable;


class ThreadLooping : IThread
{
public:
    ThreadLooping(std::string thread_name, IUpdateable& thread_update);
    ~ThreadLooping();

    void Start() override;
    void Terminate() override;

    bool IsRunning() override;
    void WaitUntilFinished() override;

protected:
    void ThreadRunLoop();

    IUpdateable& m_rThreadUpdate;
    std::string m_threadName;
    std::thread m_thread;
    std::atomic<bool> m_aShouldThreadTerminate;
    std::atomic<bool> m_aIsThreadRunning;
};


#endif /* THREAD_LOOPING_HPP_ */
