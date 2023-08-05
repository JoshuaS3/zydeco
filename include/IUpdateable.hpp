#ifndef IUPDATEABLE_HPP_
#define IUPDATEABLE_HPP_

#include <cstdint>

class IUpdateable
{
public:
    bool Update(uint64_t time_since_last_update_us);
};

#endif /* IUPDATEABLE_HPP_ */
