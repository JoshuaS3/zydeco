#ifndef IUPDATEABLE_HPP_
#define IUPDATEABLE_HPP_


#include <cstdint>


class IUpdateable
{
public:
    virtual bool Update() = 0;
};


#endif /* IUPDATEABLE_HPP_ */
