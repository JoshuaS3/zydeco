#ifndef GL_RENDER_OBJECT_RAINBOW_TRIANGLE_HPP_
#define GL_RENDER_OBJECT_RAINBOW_TRIANGLE_HPP_


#include "GLRenderObject.hpp"


class GLRenderObjectRainbowTriangle : public GLRenderObject
{
public:
    GLRenderObjectRainbowTriangle();
    ~GLRenderObjectRainbowTriangle() = default;

private:
    void Render() override;
    void Generate();

    bool m_geometryGenerated = false;
    uint32_t m_VAO = 0;
};


#endif /* GL_RENDER_OBJECT_RAINBOW_TRIANGLE_HPP_ */
