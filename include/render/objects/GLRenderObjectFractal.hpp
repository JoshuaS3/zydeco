#ifndef GL_RENDER_OBJECT_FRACTAL_HPP_
#define GL_RENDER_OBJECT_FRACTAL_HPP_


#include "GLRenderObject.hpp"


class GLRenderObjectFractal : public GLRenderObject
{
public:
    GLRenderObjectFractal();
    ~GLRenderObjectFractal() = default;

private:
    void Render() override;
};


#endif /* GL_RENDER_OBJECT_FRACTAL_HPP_ */
