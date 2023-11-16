#ifndef GLTEXTURE_HPP_
#define GLTEXTURE_HPP_


#include <map>
#include "ZydecoCommon.hpp"


class GLTexture
{
public:
    static GLTexture& GetGLTexture(std::string name);

    GLTexture(std::string texture_name, void *data_source, uint32_t width, uint32_t height);
    ~GLTexture();

    void Regenerate(int width, int height);
    void Bind(uint64_t texture_unit);

    uint32_t m_glTextureID;
private:
    static std::map<std::string, GLTexture*> s_textures;

    bool m_doRegen = false;
    std::string m_name;
    void *m_pDataSource;
    uint32_t m_width;
    uint32_t m_height;
};


#endif /* GLTEXTURE_HPP_ */
