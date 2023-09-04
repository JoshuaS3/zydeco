#include "ZydecoCommon.hpp"
#include "Renderer.hpp"
#include "IEventHandler.hpp"
#include "IWindow.hpp"
#include "ITimer.hpp"
#include "GLShader.hpp"
#include "GLProgram.hpp"
#include "GLRenderObject.hpp"
#include "GLRenderObjectBackground.hpp"
#include "GLRenderObjectRainbowTriangle.hpp"


static Logger LOGGER("Renderer");
static uint64_t frame_start;


// Set up OpenGL error handling
void MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    if (type == GL_DEBUG_TYPE_ERROR)
    {
        ZydecoFault("OpenGL Error: type = {}, severity = {}, message = {}", type, severity, message);
    }
}


Renderer::Renderer(IEventHandler& r_event_handler, IWindow& r_window, ITimer& r_timer):
    m_rWindow(r_window),
    m_rTimer(r_timer),
    m_windowWidth(800),
    m_windowHeight(600),
    m_glString(std::string((char*)glGetString(GL_VERSION))),
    m_rendererString(std::string((char*)glGetString(GL_RENDERER))),
    m_frameTimeSum(0),
    m_frameCount(0),
    m_doRender(true)
{
    LOGGER.Log(Logger::TRACE, "Renderer()");

    r_event_handler.RegisterWindowEventSubscriber(this);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);


    GLShader vert_shader {GL_VERTEX_SHADER,
        #include "triangle.vs.glsl"
        };
    GLShader frag_shader {GL_FRAGMENT_SHADER,
        #include "triangle.fs.glsl"
        };
    new GLProgram { "RainbowTriangle", {&vert_shader, &frag_shader} };

    GLShader sky_vert_shader {GL_VERTEX_SHADER,
        #include "background.vs.glsl"
        };
    GLShader sky_frag_shader {GL_FRAGMENT_SHADER,
        #include "background.fs.glsl"
        };
    new GLProgram { "Background", {&sky_vert_shader, &sky_frag_shader} };
};

bool Renderer::Update()
{
    // Render loop
    frame_start = *m_rTimer.GetGlobalTimePointer();

    if (m_doRender)
    {
        m_rWindow.MakeContextCurrent();

        glClearColor(0.18f, 0.18f, 0.18f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);

        glViewport(0, 0, m_windowWidth, m_windowHeight);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Render objects are mapped with {int: order, list<GLRenderObject*>: objects}
        // TODO: preliminary testing shows this iterator automatically sorts order keys, determine if actually true
        std::map<uint64_t, std::list<GLRenderObject*>> objects = GLRenderObject::GetRenderObjects();
        for (std::pair<uint64_t, std::list<GLRenderObject*>> order_list : objects)
        {
            for (GLRenderObject *render_object : order_list.second)
            {
                LOGGER.Log(Logger::TRACE,
                        "Update(): Rendering {}",
                        (void*)render_object);
                render_object->Render();
            }
        }
    }

    m_rWindow.Update();

    m_frameTimeSum += (*m_rTimer.GetGlobalTimePointer() - frame_start);
    m_frameCount++;

    return false;
}

void Renderer::OnWindowMinimizedEvent()
{
    m_doRender = false;
}

void Renderer::OnWindowMaximizedEvent()
{
    m_doRender = true;
}

void Renderer::OnWindowRestoredEvent()
{
    m_doRender = true;
}

void Renderer::OnWindowExposedEvent()
{
    m_doRender = true;
}

void Renderer::OnWindowResizedEvent(uint64_t new_width, uint64_t new_height)
{
    LOGGER.Log(Logger::VERBOSE, "Window resized: {}x{}", new_width, new_height);
    m_windowWidth = new_width;
    m_windowHeight = new_height;
}

void Renderer::OnWindowRequestedCloseEvent()
{

}

// Called periodically from Engine::Execute (main thread)
void Renderer::UpdateDebug()
{
    m_framerate = static_cast<float>(m_frameCount) / (static_cast<float>(m_frameTimeSum) / 1000.);
    m_rWindow.SetTitle(fmt::format("Zydeco ({:.1f} FPS, OpenGL {})", m_framerate, m_glString));
    m_frameTimeSum = 0;
    m_frameCount = 0;
}
