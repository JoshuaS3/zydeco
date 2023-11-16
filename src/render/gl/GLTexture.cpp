#include "GLTexture.hpp"
#include "ZydecoCommon.hpp"


static Logger LOGGER("GLTexture");


// static initialize
std::map<std::string, GLTexture*> GLTexture::s_textures = {};


GLTexture& GLTexture::GetGLTexture(std::string name)
{
    if (s_textures.contains(name)) { return *s_textures.at(name); }
    
    ZydecoFault("GetGLTexture({}): Texture not found", name);
}

GLTexture::GLTexture(std::string texture_name, void *data_source, uint32_t width, uint32_t height):
    m_pDataSource(data_source),
    m_name(texture_name),
    m_width(width),
    m_height(height)
{
    s_textures.insert({m_name, this});

    glGenTextures(1, &m_glTextureID);
    Regenerate(width, height);
}

GLTexture::~GLTexture()
{
    s_textures.erase(m_name);
    glDeleteTextures(1, &m_glTextureID);
}

void GLTexture::Regenerate(int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, m_glTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, m_pDataSource);
    glFlush();
}

void GLTexture::Bind(uint64_t texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    //glBindTextureUnit(texture_unit, m_glTextureID);
    glBindTexture(GL_TEXTURE_2D, m_glTextureID);
}
