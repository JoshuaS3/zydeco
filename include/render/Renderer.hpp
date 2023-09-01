#ifndef RENDERER_HPP_
#define RENDERER_HPP_


#include "IUpdateable.hpp"


class IWindow;


class Renderer : public IUpdateable
{
public:
    Renderer(IWindow& r_window);
    ~Renderer() = default;
    bool Update(uint64_t time_since_last_update_us) override;

private:
    IWindow& m_rWindow;
};

#endif /* RENDERER_HPP_ */
