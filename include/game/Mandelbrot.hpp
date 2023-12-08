#ifndef GAME_MANDELBROT_HPP
#define GAME_MANDELBROT_HPP


#include "ZydecoCommon.hpp"
#include "IUpdateable.hpp"
#include "IEventMouseSubscriber.hpp"


class IEventHandler;
class IWindow;
class GLRenderObjectFractal;
class GLTexture;
class GLUniformUploader;


struct MandelbrotSettings
{
    double zoom = 2.0;
    double pos_x = 0.0;
    double pos_y = 0.0;

    bool restart = true;
    int do_interlacing = false;
    int first_interlace = 1;
    int interlace_layer = 0;
    float param_z = 0.0;
    float brightness = 1.0;
    int iteration_count = 100;
    int iteration_step = 50;
    int adjusted_iteration_step = 50;
    int current_iteration = 0;
    float discard_threshold = 4.;
};


const int ADAM7_MATRIX[8][8] = {
    {1, 6, 4, 6, 2, 6, 4, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
    {5, 6, 5, 6, 5, 6, 5, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
    {3, 6, 4, 6, 3, 6, 4, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
    {5, 6, 5, 6, 5, 6, 5, 6},
    {7, 7, 7, 7, 7, 7, 7, 7},
};


struct ldvec3 {
    long double x = 0.0;
    long double y = 0.0;
    long double z = 0.0;

    ldvec3 operator +(const ldvec3& lhs)
    {
        return ldvec3{lhs.x + x, lhs.y + y, lhs.z + z};
    }

    ldvec3 operator -(const ldvec3& lhs)
    {
        return ldvec3{lhs.x - x, lhs.y - y, lhs.z - z};
    }

    long double operator *(const ldvec3& lhs)
    {
        return lhs.x * x + lhs.y * y + 0.0;
    }

    ldvec3 operator *(const double& lhs)
    {
        return ldvec3{lhs * x, lhs * y, lhs * z};
    }

    ldvec3 operator /(const ldvec3& lhs)
    {
        return ldvec3{x/lhs.x, y/lhs.y, z/lhs.z};
    }
};


class Mandelbrot : public IUpdateable, public IEventMouseSubscriber
{
public:
    Mandelbrot(IEventHandler& r_event_handler, IWindow& r_window, MandelbrotSettings *p_settings);
    ~Mandelbrot();

    bool Update() override;

    void OnMouseLeftDownEvent(uint64_t x, uint64_t y) override;
    void OnMouseLeftUpEvent(uint64_t x, uint64_t y) override;

    void OnMouseMiddleDownEvent(uint64_t x, uint64_t y) override;
    void OnMouseMiddleUpEvent(uint64_t x, uint64_t y) override;

    void OnMouseRightDownEvent(uint64_t x, uint64_t y) override;
    void OnMouseRightUpEvent(uint64_t x, uint64_t y) override;

    void OnMouseMoveEvent(uint64_t x, uint64_t y, int64_t dx, int64_t dy) override;

    void OnMouseWheelScrollEvent(int64_t dx, int64_t dy) override;

private:
    MandelbrotSettings *m_pSettings;

    uint64_t m_windowWidth;
    uint64_t m_windowHeight;

    GLsync m_glSyncObject = nullptr;

    uint64_t m_mousex = 0;
    uint64_t m_mousey = 0;
    bool m_mouseDown = false;
    bool m_restart = true;

    GLUniformUploader *m_pComputeUniformUploader;
    GLRenderObjectFractal *m_pRenderObject;
    GLTexture *m_pTexture;

    IEventHandler& m_rEventHandler;
    IWindow& m_rWindow;
};


#endif
