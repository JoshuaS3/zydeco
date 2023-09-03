#include <GL/gl3w.h>

#include "GLShader.hpp"


GLShader::GLShader(uint64_t shader_type, const char *shader_source)
{
    m_glShaderId = glCreateShader(shader_type);
    glShaderSource(m_glShaderId, 1, &shader_source, nullptr);
    glCompileShader(m_glShaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(m_glShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_glShaderId, 512, nullptr, infoLog);
        ZydecoFault("Shader compilation failed (type {}):\n{}", shader_type, infoLog);
    }
}

GLShader::~GLShader()
{
    glDeleteShader(m_glShaderId);
}

uint64_t GLShader::GetGLShaderID()
{
    return m_glShaderId;
}
