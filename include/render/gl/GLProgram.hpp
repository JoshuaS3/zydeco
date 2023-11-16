#ifndef GL_PROGRAM_HPP_
#define GL_PROGRAM_HPP_


#include <vector>
#include <map>

#include "ZydecoCommon.hpp"


class GLShader;


class GLProgram
{
public:
    static GLProgram *GetGLProgram(std::string name);

    GLProgram(std::string name);
    ~GLProgram();
    void Generate(std::vector<GLShader*> shaders);
    int64_t GetGLProgramID();
    std::string GetGLProgramName();

private:
    static std::map<std::string, GLProgram*> s_glPrograms;

    int64_t m_glProgramId;
    std::string m_glProgramName;
};


#endif /* GL_PROGRAM_HPP_ */
