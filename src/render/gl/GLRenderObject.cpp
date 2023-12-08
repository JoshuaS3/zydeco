#include <list>

#include "ZydecoCommon.hpp"
#include "GLRenderObject.hpp"
#include "GLProgram.hpp"
#include "GLTexture.hpp"


static Logger LOGGER("GLRenderObject");

// static initialize
std::map<uint64_t, std::list<GLRenderObject*>> GLRenderObject::s_renderObjects = {};


GLRenderObject::GLRenderObject(std::string gl_program_name, uint64_t render_order):
    m_renderOrder(render_order),
    m_renderEnabled(true)
{
    if (gl_program_name != "")
    {
        m_glProgram = GLProgram::GetGLProgram(gl_program_name);
        if (m_glProgram == nullptr) { ZydecoFault("GLRenderObject(): Program '{}' is nonexistent", gl_program_name); }
    }

    s_renderObjects.insert(std::pair<uint64_t, std::list<GLRenderObject*>>(render_order, {}));
    s_renderObjects.at(render_order).push_back(this);
}

GLRenderObject::~GLRenderObject()
{
    s_renderObjects.at(m_renderOrder).remove(this);
    if (s_renderObjects.at(m_renderOrder).empty())
    {
        s_renderObjects.erase(m_renderOrder);
    }
}

void GLRenderObject::RenderEnable()
{
    m_renderEnabled = true;
}

void GLRenderObject::RenderDisable()
{
    m_renderEnabled = false;
}

void GLRenderObject::AddTexture(uint64_t texture_unit, GLTexture *texture)
{
    m_textures[texture_unit] = texture;
}

void GLRenderObject::GLTargetSetup()
{
    int program = m_glProgram->GetGLProgramID();

    glUseProgram(program);

    UploadUniforms(program);

    for (std::pair<uint64_t, GLTexture*> texture : m_textures)
    {
        texture.second->BindAsTexture(texture.first);
    }
}

std::map<uint64_t, std::list<GLRenderObject*>>& GLRenderObject::GetRenderObjects()
{
    return s_renderObjects;
}
