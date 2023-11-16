#include <GL/gl3w.h>

#include "GLShader.hpp"
#include "GLComputeShader.hpp"


GLComputeShader::GLComputeShader(const char *shader_source):
    GLShader::GLShader(GL_COMPUTE_SHADER, shader_source)
{

}
