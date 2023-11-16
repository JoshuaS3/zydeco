#include <GL/gl3w.h>

#include "GLRenderObject.hpp"
#include "GLRenderObjectFractal.hpp"
#include "GLProgram.hpp"


GLRenderObjectFractal::GLRenderObjectFractal():
    GLRenderObject::GLRenderObject("FractalDisplay", 0)
{

}

void GLRenderObjectFractal::Render()
{
    if (!m_renderEnabled) { return; }

    GLTargetSetup();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
