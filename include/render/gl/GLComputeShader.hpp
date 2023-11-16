#ifndef GLCOMPUTESHADER_HPP_
#define GLCOMPUTESHADER_HPP_


#include "ZydecoCommon.hpp"
#include "GLShader.hpp"


class GLComputeShader : public GLShader
{
public:
    GLComputeShader(const char *shader_source);
    ~GLComputeShader() = default;
    uint64_t GetGLShaderID();

private:
    uint64_t m_shaderType;
    uint64_t m_glShaderId;
};


#endif /* GLCOMPUTESHADER_HPP_ */
