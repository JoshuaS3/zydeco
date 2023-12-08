#ifndef GL_UNIFORM_UPLOADER_HPP_
#define GL_UNIFORM_UPLOADER_HPP_


#include <string>
#include <array>
#include <map>


enum class glUniformType
{
    FLOAT, DOUBLE, INT, UINT, MAT4
};

struct glUniform
{
public:
    enum glUniformType type;
    uint8_t quantity;
    void **data;
};


class GLUniformUploader
{
public:
    GLUniformUploader() = default;
    ~GLUniformUploader() = default;

    // todo: interface for removing/updating uniform pointer?
    template<int N, typename T>
    void AssignUniformPointer(std::string name, std::array<void*, N> data)
    {
        glUniform uniform;
        if (std::is_same<T, float>::value)                  { uniform.type = glUniformType::FLOAT; }
        else if (std::is_same<T, double>::value)            { uniform.type = glUniformType::DOUBLE; }
        else if (std::is_same<T, int>::value)               { uniform.type = glUniformType::INT; }
        else if (std::is_same<T, long int>::value)          { uniform.type = glUniformType::INT; }
        else if (std::is_same<T, unsigned int>::value)      { uniform.type = glUniformType::UINT; }
        else if (std::is_same<T, unsigned long int>::value) { uniform.type = glUniformType::UINT; }
        else if (std::is_same<T, glm::mat4>::value)         { uniform.type = glUniformType::MAT4; }
        else { ZydecoFault("RenderSetUniform('{}'): Unknown data type {}", name, typeid(T).name()); }

        uniform.quantity = N;
        uniform.data = new void *[N];
        std::copy(std::begin(data), std::end(data), uniform.data);

        m_uniforms.insert(std::pair<std::string, glUniform>(name, uniform));
    }

    void UploadUniforms(uint64_t program_id);

public:
    std::map<std::string, glUniform> m_uniforms;
};


#endif
