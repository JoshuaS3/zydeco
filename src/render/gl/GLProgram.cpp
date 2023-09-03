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

GLProgram::GLProgram(std::string name, std::vector<GLShader*> shaders)
{
    LOGGER.Log(Logger::TRACE, "GLProgram(name: {}, ...)", name);
    m_glProgramId = glCreateProgram();
    m_glProgramName = name;

    for (GLShader *p_shader : shaders)
    {
        glAttachShader(m_glProgramId, p_shader->GetGLShaderID());
    }

    glLinkProgram(m_glProgramId);

    int success;
    char infoLog[512];
    glGetProgramiv(m_glProgramId, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_glProgramId, 512, NULL, infoLog);
        ZydecoFault("Shader program linking failed:\n{}", infoLog);
    }

    for (GLShader *p_shader : shaders)
    {
        glDetachShader(m_glProgramId, p_shader->GetGLShaderID());
    }

    s_glPrograms.emplace(std::pair<std::string, GLProgram*>(m_glProgramName, this));
}

GLProgram::~GLProgram()
{
    LOGGER.Log(Logger::TRACE, "~GLProgram() for '{}'", m_glProgramName);
    glDeleteProgram(m_glProgramId);
    s_glPrograms.erase(m_glProgramName);
}

uint64_t GLProgram::GetGLProgramID()
{
    return m_glProgramId;
}

std::string GLProgram::GetGLProgramName()
{
    return m_glProgramName;
}
