#include "texture.h"

// Include stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


ugly::Texture::Texture(const std::filesystem::path& _path, MinMagFilter _min_filter, MinMagFilter _mag_filter, WrapFilter _wrap_s, WrapFilter _wrap_t)
{
    // Load texture from file
    int width, height, num_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(_path.string().c_str(), &width, &height, &num_channels, 0);
    if (data == nullptr)
    {
        PLOG_ERROR << "Failed to load image from file";
        throw new std::runtime_error("Failed to load image from file");
    }

    GLint format;
    GLenum internal_format;
    switch (num_channels)
    {
    case 1:
        format = GL_RED;
        internal_format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        internal_format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        internal_format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        internal_format = GL_RGBA;
        break;
    }

    glGenTextures(1, &m_id);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    setWrap(_wrap_s, _wrap_t);
    setFilter(_min_filter, _mag_filter);

    // Destroy texture data
    stbi_image_free(data);
}


ugly::Texture::~Texture()
{
    if (m_id != 0)
    {
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}


void ugly::Texture::bind(uint32_t _unit)
{
    glActiveTexture(GL_TEXTURE0 + _unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}


void ugly::Texture::setFilter(MinMagFilter min_filter, MinMagFilter mag_filter)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int32_t)min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int32_t)mag_filter);
}


void ugly::Texture::setWrap(WrapFilter _wrap_s, WrapFilter _wrap_t)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int32_t)_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int32_t)_wrap_t);
}