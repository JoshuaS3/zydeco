#ifndef RENDERER_HPP_
#define RENDERER_HPP_


#include "IUpdateable.hpp"
#include "IEventWindowSubscriber.hpp"


class IEventHandler;
class IWindow;
class ITimer;


class Renderer : public IUpdateable, public IEventWindowSubscriber
{
public:
    Renderer(IEventHandler& r_event_handler, IWindow& r_window, ITimer& r_timer);
    ~Renderer() = default;

    // public IUpdateable
    bool Update() override;

    // public IEventWindowSubscriber
    void OnWindowMinimizedEvent() override;
    void OnWindowMaximizedEvent() override;
    void OnWindowRestoredEvent() override;
    void OnWindowExposedEvent() override;
    void OnWindowResizedEvent(uint64_t new_width, uint64_t new_height) override;
    void OnWindowRequestedCloseEvent() override;

    // Renderer
    void UpdateDebug();

private:
    IWindow& m_rWindow;
    ITimer& m_rTimer;
    uint64_t m_windowWidth;
    uint64_t m_windowHeight;

    std::string m_glString;
    std::string m_rendererString;
    uint64_t m_frameTimeSum = 0;
    uint64_t m_frameCount = 0;
    float m_framerate = 0.0;

    bool m_doRender;
};


#endif /* RENDERER_HPP_ */
