#ifndef GLSHADER_HPP_
#define GLSHADER_HPP_


#include "ZydecoCommon.hpp"


class GLShader
{
public:
    GLShader(uint64_t shader_type, const char *shader_source);
    ~GLShader();
    uint64_t GetGLShaderID();

private:
    uint64_t m_shaderType;
    uint64_t m_glShaderId;
};


#endif /* GLSHADER_HPP_ */
