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
    glUseProgram(m_glProgram->GetGLProgramID());

    for (std::pair<std::string, glUniform> uniform : m_uniforms)
    {
        int location = glGetUniformLocation(m_glProgram->GetGLProgramID(), uniform.first.c_str());
        if (location == -1)
        {
            // LOGGER.Log(Logger::WARNING, "Render(): Uniform '{}' does not exist for program '{}'", uniform.first, m_glProgram->GetGLProgramName());
            continue;
        }

        if (uniform.second.type == glUniformType::FLOAT)
        {
            switch (uniform.second.quantity)
            {
                case 1: glUniform1f(location, *(float*)(uniform.second.data[0])); break;
                case 2: glUniform2f(location, *(float*)(uniform.second.data[0]), *(float*)(uniform.second.data[1])); break;
                case 3: glUniform3f(location, *(float*)(uniform.second.data[0]), *(float*)(uniform.second.data[1]), *(float*)(uniform.second.data[2])); break;
                case 4: glUniform4f(location, *(float*)(uniform.second.data[0]), *(float*)(uniform.second.data[1]), *(float*)(uniform.second.data[2]), *(float*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::DOUBLE)
        {
            switch (uniform.second.quantity)
            {
                case 1: glUniform1d(location, *(double*)(uniform.second.data[0])); break;
                case 2: glUniform2d(location, *(double*)(uniform.second.data[0]), *(double*)(uniform.second.data[1])); break;
                case 3: glUniform3d(location, *(double*)(uniform.second.data[0]), *(double*)(uniform.second.data[1]), *(double*)(uniform.second.data[2])); break;
                case 4: glUniform4d(location, *(double*)(uniform.second.data[0]), *(double*)(uniform.second.data[1]), *(double*)(uniform.second.data[2]), *(double*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::INT)
        {
            switch (uniform.second.quantity)
            {
                case 1: glUniform1i(location, *(int*)(uniform.second.data[0])); break;
                case 2: glUniform2i(location, *(int*)(uniform.second.data[0]), *(int*)(uniform.second.data[1])); break;
                case 3: glUniform3i(location, *(int*)(uniform.second.data[0]), *(int*)(uniform.second.data[1]), *(int*)(uniform.second.data[2])); break;
                case 4: glUniform4i(location, *(int*)(uniform.second.data[0]), *(int*)(uniform.second.data[1]), *(int*)(uniform.second.data[2]), *(int*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::UINT)
        {
            switch (uniform.second.quantity)
            {
                case 1: glUniform1ui(location, *(unsigned int*)(uniform.second.data[0])); break;
                case 2: glUniform2ui(location, *(unsigned int*)(uniform.second.data[0]), *(unsigned int*)(uniform.second.data[1])); break;
                case 3: glUniform3ui(location, *(unsigned int*)(uniform.second.data[0]), *(unsigned int*)(uniform.second.data[1]), *(unsigned int*)(uniform.second.data[2])); break;
                case 4: glUniform4ui(location, *(unsigned int*)(uniform.second.data[0]), *(unsigned int*)(uniform.second.data[1]), *(unsigned int*)(uniform.second.data[2]), *(unsigned int*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::MAT4)
        {
            glUniformMatrix4fv(location, uniform.second.quantity, false, (float*)(uniform.second.data[0]) );
//            glUniformMatrix4fv(location, uniform.second.quantity, false, &((*(glm::mat4*)(uniform.second.data[0]))[0][0]));
        }
    }

    for (std::pair<uint64_t, GLTexture*> texture : m_textures)
    {
        texture.second->Bind(texture.first);
    }
}

std::map<uint64_t, std::list<GLRenderObject*>>& GLRenderObject::GetRenderObjects()
{
    return s_renderObjects;
}
