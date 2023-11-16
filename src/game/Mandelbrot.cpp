#include "ZydecoCommon.hpp"
#include "Mandelbrot.hpp"
#include "IEventHandler.hpp"
#include "IWindow.hpp"
#include "IEventMouseSubscriber.hpp"
#include "GLRenderObjectFractal.hpp"
#include "GLProgram.hpp"
#include "GLTexture.hpp"

static Logger LOGGER("Mandelbrot");


ldvec3 ComplexSquare(ldvec3 in)
{
    long double real_part = in.x*in.x - in.y*in.y;
    long double complex_part = 2.*in.x*in.y;
    return ldvec3{real_part, complex_part, in.z};
}


Mandelbrot::Mandelbrot(IEventHandler& r_event_handler, IWindow& r_window, MandelbrotSettings *p_settings):
    m_rEventHandler(r_event_handler),
    m_rWindow(r_window),
    m_pSettings(p_settings)
{
    r_event_handler.RegisterMouseEventSubscriber(this);

    m_windowWidth = r_window.GetWidth();
    m_windowHeight = r_window.GetHeight();


    m_pTexture = new GLTexture("Mandelbrot", nullptr, m_windowWidth, m_windowHeight);

    m_pSettings->restart = true;
    m_pRenderObject = new GLRenderObjectFractal {};
    m_pRenderObject->AddTexture(0, m_pTexture);
    m_pTexture->Regenerate(m_windowWidth, m_windowHeight);
    m_pRenderObject->RenderSetUniform<1, int>("texture0", {new int {0}});
    m_pRenderObject->RenderSetUniform<2, int>("screensize", {&m_windowWidth, &m_windowHeight});
    m_pRenderObject->RenderSetUniform<1, int>("it_count", {&m_pSettings->adjusted_iteration_step});
    m_pRenderObject->RenderSetUniform<1, double>("zoom", {&m_pSettings->zoom});
    m_pRenderObject->RenderSetUniform<1, float>("brightness", {&m_pSettings->brightness});
    m_pRenderObject->RenderSetUniform<1, int>("enable_interlacing", {&m_pSettings->do_interlacing});
    m_pRenderObject->RenderSetUniform<1, int>("interlace_layer", {&m_pSettings->interlace_layer});
    m_pRenderObject->RenderSetUniform<1, int>("first_interlace", {&m_pSettings->first_interlace});
}

Mandelbrot::~Mandelbrot()
{
    delete m_pRenderObject;
    delete m_pTexture;
}

bool Mandelbrot::Update()
{
    uint64_t updated_window_width = m_rWindow.GetWidth();
    uint64_t updated_window_height = m_rWindow.GetHeight();
    if (updated_window_width != m_windowWidth || updated_window_height != m_windowHeight)
    {
        m_windowWidth = updated_window_width;
        m_windowHeight = updated_window_height;
        m_pSettings->current_iteration = 0;
        m_pSettings->interlace_layer = 0;
        m_pSettings->first_interlace = 1;
        m_pSettings->restart = false;
        m_pTexture->Regenerate(m_windowWidth, m_windowHeight);
    }
    else if (m_pSettings->restart)
    {
        m_pSettings->current_iteration = 0;
        m_pSettings->interlace_layer = 0;
        m_pSettings->first_interlace = 1;
    }

    if (m_pSettings->current_iteration >= m_pSettings->adjusted_iteration_step) { return false; }

    m_pSettings->adjusted_iteration_step = m_pSettings->iteration_step * log2(2.0 + 1./m_pSettings->zoom);


    bool waiting = false;
    if (m_glSyncObject != nullptr)
    {
        int previous_invocation_finished = 0;
        glGetSynciv(m_glSyncObject, GL_SYNC_STATUS, 1, nullptr, &previous_invocation_finished);
        if (previous_invocation_finished == GL_SIGNALED)
        {
            waiting = false;
            glDeleteSync(m_glSyncObject);
            m_glSyncObject = nullptr;
        }
        else
        {
            waiting = true;
        }
    }


    if (!waiting)
    {
        if (m_pSettings->do_interlacing)
        {
            if (m_pSettings->interlace_layer == 7)
            {
                m_pSettings->current_iteration += m_pSettings->adjusted_iteration_step;
                m_pSettings->interlace_layer = 1;
                m_pSettings->first_interlace = 0;
                //if (m_pSettings->current_iteration >= m_pSettings->iteration_count) { return false; }
            }
            else
            {
                m_pSettings->interlace_layer++;
            }
        }
        else
        {
            m_pSettings->interlace_layer = 1;
            m_pSettings->first_interlace = 1;
        }

        if (m_pSettings->restart)
        {
            m_pSettings->restart = false;
            m_pTexture->Regenerate(m_windowWidth, m_windowHeight);
        }

        LOGGER.Log(Logger::INFO, "Dispatching compute (interlace layer {})", m_pSettings->interlace_layer);

        int program = GLProgram::GetGLProgram("FractalCompute")->GetGLProgramID();

        glUseProgram(program);

        glBindImageTexture(0, m_pTexture->m_glTextureID, 0, false, 0, GL_READ_WRITE, GL_RGBA32F);

        glUniform1i(glGetUniformLocation(program, "texture0"),           0);
        glUniform2i(glGetUniformLocation(program, "screensize"),         m_windowWidth, m_windowHeight);
        glUniform2d(glGetUniformLocation(program, "offset"),             m_pSettings->pos_x, m_pSettings->pos_y);
        glUniform1d(glGetUniformLocation(program, "zoom"),               m_pSettings->zoom);
        glUniform1d(glGetUniformLocation(program, "z"),                  m_pSettings->param_z);
        glUniform1d(glGetUniformLocation(program, "discard_threshold"),  m_pSettings->discard_threshold);
        glUniform1i(glGetUniformLocation(program, "current_iteration"),  m_pSettings->current_iteration);
        glUniform1i(glGetUniformLocation(program, "it_steps"),           m_pSettings->adjusted_iteration_step);
        glUniform1i(glGetUniformLocation(program, "enable_interlacing"), m_pSettings->do_interlacing);
        glUniform1i(glGetUniformLocation(program, "interlace_layer"),    m_pSettings->interlace_layer);
        glUniform1i(glGetUniformLocation(program, "first_interlace"),    m_pSettings->first_interlace);

        glDispatchCompute((updated_window_width+31)/32, (updated_window_height+31)/32, 1);

        if (!m_pSettings->do_interlacing)
        {
            m_pSettings->current_iteration += m_pSettings->adjusted_iteration_step;
        }

        glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }

    return false;
}

void Mandelbrot::OnMouseLeftDownEvent(uint64_t x, uint64_t y)
{
    m_mouseDown = true;
}

void Mandelbrot::OnMouseLeftUpEvent(uint64_t x, uint64_t y)
{
    m_mouseDown = false;
}

void Mandelbrot::OnMouseMiddleDownEvent(uint64_t x, uint64_t y)
{

}

void Mandelbrot::OnMouseMiddleUpEvent(uint64_t x, uint64_t y)
{

}

void Mandelbrot::OnMouseRightDownEvent(uint64_t x, uint64_t y)
{

}

void Mandelbrot::OnMouseRightUpEvent(uint64_t x, uint64_t y)
{

}

void Mandelbrot::OnMouseMoveEvent(uint64_t x, uint64_t y, int64_t dx, int64_t dy)
{
    m_mousex = x;
    m_mousey = y;

    if (m_mouseDown) {
        m_pSettings->pos_x += static_cast<long double>(dx) * m_pSettings->zoom;
        m_pSettings->pos_y -= static_cast<long double>(dy) * m_pSettings->zoom;

        m_pSettings->restart = true;

        LOGGER.Log(Logger::INFO, "X, Y: <{}, {}>", m_pSettings->pos_x, m_pSettings->pos_y);
    }
}

void Mandelbrot::OnMouseWheelScrollEvent(int64_t dx, int64_t dy)
{
    float factor = static_cast<long double>(dy) / 1'000'000'000.;

    double old_view_width = (long double)m_windowWidth * m_pSettings->zoom;
    double old_view_height = (long double)m_windowHeight * m_pSettings->zoom;

    if (dy > 0)
    {
        m_pSettings->zoom /= factor;
    }
    else if (dy < 0)
    {
        m_pSettings->zoom *= -factor;
    }

    long double xrel = ((long double)m_mousex / (long double)m_windowWidth) - 0.5;
    long double yrel = ((long double)m_mousey / (long double)m_windowHeight) - 0.5;

    long double new_view_width = (long double)m_windowWidth * m_pSettings->zoom;
    long double new_view_height = (long double)m_windowHeight * m_pSettings->zoom;

    long double xdelta = xrel*(new_view_width - old_view_width);
    long double ydelta = yrel*(new_view_height - old_view_height);

    m_pSettings->pos_x += xdelta;
    m_pSettings->pos_y -= ydelta;

    m_pSettings->restart = true;

    LOGGER.Log(Logger::INFO, "Zoom level: {}", m_pSettings->zoom);
}
