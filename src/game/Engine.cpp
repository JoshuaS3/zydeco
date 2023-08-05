#include <chrono>
#include <thread>

#include "Engine.hpp"
#include "ZydecoCommon.hpp"

Logger LOGGER("ENGINE");

Engine::Engine():
    m_sdlWindow("Zydeco", SDL_WINDOW_MAXIMIZED),
    m_tickLengthUs(1'000'000 / 60)
{
    LOGGER.Log(Logger::INFO, "Initializing engine");
}

Engine::~Engine()
{

}

void Engine::Start()
{
    LOGGER.Log(Logger::INFO, "Entering engine loop");

    while (1)
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed = current_time - m_tickStartTime;
        m_tickStartTime = current_time;
        if (!Update(elapsed.count())) { break; }

        current_time = std::chrono::high_resolution_clock::now();

        if ((current_time - m_tickStartTime).count() < m_tickLengthUs)
        {
            std::this_thread::sleep_for(std::chrono::duration<double, std::micro>(16667));
        }
    }
}

void Engine::Kill()
{

}

bool Engine::Update(uint64_t time_since_last_update_us)
{
    m_tickStartTime = std::chrono::high_resolution_clock::now();
    // Update members
    bool ret = m_sdlWindow.Update(time_since_last_update_us);
    return ret;
}

/*
class Engine
{
public:
    Engine();
    ~Engine();

    void Start();
    void Kill();

    void Update();

protected:
    Window m_sdlWindow;
    Scene m_scene;
    Renderer m_renderer;
    EventHandler m_eventHandler;
};
*/
