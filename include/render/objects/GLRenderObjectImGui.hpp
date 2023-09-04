#ifndef GL_RENDER_OBJECT_IMGUI_HPP_
#define GL_RENDER_OBJECT_IMGUI_HPP_


#include "GLRenderObject.hpp"


class ImFont;


class GLRenderObjectImGui : public GLRenderObject
{
public:
    GLRenderObjectImGui();
    ~GLRenderObjectImGui() = default;

private:
    void Render() override;

    ImFont *m_font;
};


#endif /* GL_RENDER_OBJECT_IMGUI_HPP_ */
