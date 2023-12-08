#ifndef GLTEXTURE_HPP_
#define GLTEXTURE_HPP_


#include <map>
#include "ZydecoCommon.hpp"


class GLTexture
{
public:
    GLTexture(uint32_t sized_format, void *data_source, uint32_t width, uint32_t height);
    ~GLTexture();

    uint32_t GetID();

    void SetDataSourceAndReload(void *data_source, int width, int height);
    void ReloadFromDataSource();

    void BindAsTexture(uint64_t texture_unit);
    void BindAsImage(uint64_t texture_unit);

private:
    uint32_t m_glTextureID = 0;
    uint32_t m_baseFormat = 0;
    uint32_t m_sizedFormat = 0;
    uint32_t m_dataType = 0;

    void *m_pDataSource;
    uint32_t m_width;
    uint32_t m_height;
};


#endif /* GLTEXTURE_HPP_ */
