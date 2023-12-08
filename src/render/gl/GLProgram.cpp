#include <GL/gl3w.h>

#include "ZydecoCommon.hpp"
#include "GLProgram.hpp"
#include "GLShader.hpp"


static Logger LOGGER("GLProgram");


// static initialize members
std::map<std::string, GLProgram*> GLProgram::s_glPrograms {};


GLProgram *GLProgram::GetGLProgram(std::string name)
{
    if (!s_glPrograms.count(name)) { ZydecoFault("GetGLProgram(): Program '{}' does not exist", name); }
    return s_glPrograms.at(name);
}

GLProgram::GLProgram(std::string name):
    m_glProgramId(-1),
    m_glProgramName(name)
{
    LOGGER.Log(Logger::TRACE, "GLProgram(name: {})", name);

    s_glPrograms.emplace(std::pair<std::string, GLProgram*>(m_glProgramName, this));
}

GLProgram::~GLProgram()
{
    LOGGER.Log(Logger::TRACE, "~GLProgram() for '{}'", m_glProgramName);
    if (m_glProgramId != -1) { glDeleteProgram(m_glProgramId); }
    s_glPrograms.erase(m_glProgramName);
}

void GLProgram::Generate(std::vector<GLShader*> shaders)
{
    uint64_t pid = glCreateProgram();

    for (GLShader *p_shader : shaders)
    {
        glAttachShader(pid, p_shader->GetGLShaderID());
    }

    glLinkProgram(pid);

    for (GLShader *p_shader : shaders)
    {
        glDetachShader(pid, p_shader->GetGLShaderID());
    }

    int success;
    char infoLog[512];
    glGetProgramiv(pid, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(pid, 512, NULL, infoLog);
        ZydecoFault("Shader program linking failed:\n{}", infoLog);
        return;
    }
    else
    {
        if (m_glProgramId != -1) { glDeleteProgram(m_glProgramId); }
        m_glProgramId = pid;
    }
}

uint64_t GLProgram::GetGLProgramID()
{
    return m_glProgramId;
}

std::string GLProgram::GetGLProgramName()
{
    return m_glProgramName;
}
