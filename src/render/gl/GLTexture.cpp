#include "ZydecoCommon.hpp"
#include "GLTexture.hpp"


static Logger LOGGER("GLTexture");


std::map<uint32_t, std::array<uint32_t, 3>> TEXTURE_FORMAT_LOOKUP = {
    {GL_RGB32F, {GL_RGB, GL_FLOAT}},
    {GL_RGBA32F, {GL_RGBA, GL_FLOAT}},
};


GLTexture::GLTexture(uint32_t sized_format, void *data_source, uint32_t width, uint32_t height):
    m_sizedFormat(sized_format),
    m_baseFormat(TEXTURE_FORMAT_LOOKUP[sized_format][0]),
    m_dataType(TEXTURE_FORMAT_LOOKUP[sized_format][1])
{
    glGenTextures(1, &m_glTextureID);
    SetDataSourceAndReload(data_source, width, height);
    assert(glIsTexture(m_glTextureID) == GL_TRUE);
    assert(m_baseFormat == GL_RGBA);
    assert(m_sizedFormat == GL_RGBA32F);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &m_glTextureID);
}

uint32_t GLTexture::GetID()
{
    return m_glTextureID;
}

void GLTexture::SetDataSourceAndReload(void *data_source, int width, int height)
{
    m_pDataSource = data_source;
    m_width = width;
    m_height = height;
    ReloadFromDataSource();
}

void GLTexture::ReloadFromDataSource()
{
    glBindTexture(GL_TEXTURE_2D, m_glTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, m_sizedFormat, m_width, m_height, 0, m_baseFormat, m_dataType, m_pDataSource);
}

void GLTexture::BindAsTexture(uint64_t texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_glTextureID);
}

void GLTexture::BindAsImage(uint64_t texture_unit)
{
    glActiveTexture(GL_TEXTURE0);
    glBindImageTexture(texture_unit, m_glTextureID, 0, false, 0, GL_READ_WRITE, m_sizedFormat);
}
