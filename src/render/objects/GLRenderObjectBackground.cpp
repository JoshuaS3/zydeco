#include <GL/gl3w.h>

#include "GLRenderObject.hpp"
#include "GLRenderObjectBackground.hpp"
#include "GLProgram.hpp"


GLRenderObjectBackground::GLRenderObjectBackground():
    GLRenderObject::GLRenderObject("Background", 0)
{

}

void GLRenderObjectBackground::Render()
{
    if (!m_renderEnabled) { return; }

    GLTargetSetup();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
