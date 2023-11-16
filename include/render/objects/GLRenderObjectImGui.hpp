#ifndef GL_RENDER_OBJECT_IMGUI_HPP_
#define GL_RENDER_OBJECT_IMGUI_HPP_


#include "GLRenderObject.hpp"


class ImFont;
class MandelbrotSettings;


class GLRenderObjectImGui : public GLRenderObject
{
public:
    GLRenderObjectImGui(MandelbrotSettings *p_settings);
    ~GLRenderObjectImGui() = default;

private:
    void Render() override;

    ImFont *m_font;
    MandelbrotSettings *m_pSettings;
};


#endif /* GL_RENDER_OBJECT_IMGUI_HPP_ */
