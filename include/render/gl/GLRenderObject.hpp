#ifndef GL_RENDER_OBJECT_HPP_
#define GL_RENDER_OBJECT_HPP_


#include <list>
#include <map>

#include "ZydecoCommon.hpp"
#include "GLUniformUploader.hpp"


class GLProgram;
class GLTexture;


class GLRenderObject : public GLUniformUploader
{
public:
    void RenderEnable();
    void RenderDisable();

    void AddTexture(uint64_t texture_unit, GLTexture *texture);

protected:
    friend class Renderer;

    GLRenderObject(std::string gl_program_name, uint64_t render_order);
    ~GLRenderObject();

    virtual void Render() = 0;
    static std::map<uint64_t, std::list<GLRenderObject*>>& GetRenderObjects();
    void GLTargetSetup();
    bool m_renderEnabled = true;

private:
    static std::map<uint64_t, std::list<GLRenderObject*>> s_renderObjects;

    GLProgram *m_glProgram;
    uint64_t m_renderOrder;
    std::map<uint64_t, GLTexture*> m_textures;
};

#endif /* GL_RENDER_OBJECT_HPP_ */
