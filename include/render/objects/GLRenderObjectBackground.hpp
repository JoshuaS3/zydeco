#ifndef GL_RENDER_OBJECT_BACKGROUND_HPP_
#define GL_RENDER_OBJECT_BACKGROUND_HPP_


#include "GLRenderObject.hpp"


class GLRenderObjectBackground : public GLRenderObject
{
public:
    GLRenderObjectBackground();
    ~GLRenderObjectBackground() = default;

private:
    void Render() override;
};


#endif /* GL_RENDER_OBJECT_BACKGROUND_HPP_ */
