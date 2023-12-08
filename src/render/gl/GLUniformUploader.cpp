#include "ZydecoCommon.hpp"
#include "GLUniformUploader.hpp"


static Logger LOGGER("GLUniformUploader");


void GLUniformUploader::UploadUniforms(uint64_t program_id)
{
    for (std::pair<std::string, glUniform> uniform : m_uniforms)
    {
        int location = glGetUniformLocation(program_id, uniform.first.c_str());
        if (location == -1)
        {
            LOGGER.Log(Logger::WARNING, "UploadUniforms(): {} not found", uniform.first);
            continue;
        }

        if (uniform.second.type == glUniformType::FLOAT)
        {
            switch (uniform.second.quantity)
            {
                case 1: glProgramUniform1f(program_id, location, *(float*)(uniform.second.data[0])); break;
                case 2: glProgramUniform2f(program_id, location, *(float*)(uniform.second.data[0]), *(float*)(uniform.second.data[1])); break;
                case 3: glProgramUniform3f(program_id, location, *(float*)(uniform.second.data[0]), *(float*)(uniform.second.data[1]), *(float*)(uniform.second.data[2])); break;
                case 4: glProgramUniform4f(program_id, location, *(float*)(uniform.second.data[0]), *(float*)(uniform.second.data[1]), *(float*)(uniform.second.data[2]), *(float*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::DOUBLE)
        {
            switch (uniform.second.quantity)
            {
                case 1: glProgramUniform1d(program_id, location, *(double*)(uniform.second.data[0])); break;
                case 2: glProgramUniform2d(program_id, location, *(double*)(uniform.second.data[0]), *(double*)(uniform.second.data[1])); break;
                case 3: glProgramUniform3d(program_id, location, *(double*)(uniform.second.data[0]), *(double*)(uniform.second.data[1]), *(double*)(uniform.second.data[2])); break;
                case 4: glProgramUniform4d(program_id, location, *(double*)(uniform.second.data[0]), *(double*)(uniform.second.data[1]), *(double*)(uniform.second.data[2]), *(double*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::INT)
        {
            switch (uniform.second.quantity)
            {
                case 1: glProgramUniform1i(program_id, location, *(int*)(uniform.second.data[0])); break;
                case 2: glProgramUniform2i(program_id, location, *(int*)(uniform.second.data[0]), *(int*)(uniform.second.data[1])); break;
                case 3: glProgramUniform3i(program_id, location, *(int*)(uniform.second.data[0]), *(int*)(uniform.second.data[1]), *(int*)(uniform.second.data[2])); break;
                case 4: glProgramUniform4i(program_id, location, *(int*)(uniform.second.data[0]), *(int*)(uniform.second.data[1]), *(int*)(uniform.second.data[2]), *(int*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::UINT)
        {
            switch (uniform.second.quantity)
            {
                case 1: glProgramUniform1ui(program_id, location, *(unsigned int*)(uniform.second.data[0])); break;
                case 2: glProgramUniform2ui(program_id, location, *(unsigned int*)(uniform.second.data[0]), *(unsigned int*)(uniform.second.data[1])); break;
                case 3: glProgramUniform3ui(program_id, location, *(unsigned int*)(uniform.second.data[0]), *(unsigned int*)(uniform.second.data[1]), *(unsigned int*)(uniform.second.data[2])); break;
                case 4: glProgramUniform4ui(program_id, location, *(unsigned int*)(uniform.second.data[0]), *(unsigned int*)(uniform.second.data[1]), *(unsigned int*)(uniform.second.data[2]), *(unsigned int*)(uniform.second.data[3])); break;
            }
        }
        else if (uniform.second.type == glUniformType::MAT4)
        {
            glProgramUniformMatrix4fv(program_id, location, uniform.second.quantity, false, (float*)(uniform.second.data[0]) );
        }
    }
}
