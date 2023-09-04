#ifndef GL_RENDER_OBJECT_HPP_
#define GL_RENDER_OBJECT_HPP_


#include <list>
#include <map>

#include <GL/gl3w.h>
#include <glm/glm.hpp>

#include "ZydecoCommon.hpp"


class GLProgram;


enum class glUniformType
{
    FLOAT, INT, UINT
};

struct glUniform
{
public:
    enum glUniformType type;
    uint8_t quantity;
    void **data;
};


class GLRenderObject
{
public:
    void RenderEnable();
    void RenderDisable();

    template<int N, typename T>
    constexpr void RenderSetUniform(std::string name, std::array<void*, N> data)
    {
        glUniform uniform;
        if (std::is_same<T, float>::value)                  { uniform.type = glUniformType::FLOAT; }
        else if (std::is_same<T, int>::value)               { uniform.type = glUniformType::INT; }
        else if (std::is_same<T, long int>::value)          { uniform.type = glUniformType::INT; }
        else if (std::is_same<T, unsigned int>::value)      { uniform.type = glUniformType::UINT; }
        else if (std::is_same<T, long unsigned int>::value) { uniform.type = glUniformType::UINT; }
        else { ZydecoFault("RenderSetUniform({}): Unknown data type {}", name, typeid(T).name()); }

        uniform.quantity = N;
        uniform.data = new void *[N];
        std::copy(std::begin(data), std::end(data), uniform.data);


        m_uniforms.insert(std::pair<std::string, glUniform>(name, uniform));
    }

protected:
    friend class Renderer;

    GLRenderObject(std::string gl_program_name, uint64_t render_order);
    ~GLRenderObject();

    virtual void Render() = 0;
    static std::map<uint64_t, std::list<GLRenderObject*>>& GetRenderObjects();
    void GLTargetSetup();
    bool m_renderEnabled;

private:
    static std::map<uint64_t, std::list<GLRenderObject*>> s_renderObjects;

    GLProgram *m_glProgram;
    uint64_t m_renderOrder;
    std::map<std::string, glUniform> m_uniforms;
};

#endif /* GL_RENDER_OBJECT_HPP_ */