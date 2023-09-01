#ifndef ITHREAD_HPP_
#define ITHREAD_HPP_


class IThread
{
public:
    virtual void Start() = 0;
    virtual void Terminate() = 0;
    virtual bool IsRunning() = 0;
    virtual void WaitUntilFinished() = 0;
};


#endif /* ITHREAD_HPP_ */
