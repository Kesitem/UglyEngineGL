#include "texture.h"

// Include stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


ugly::Texture::Texture(const std::filesystem::path& _path, GLint _min_filter, GLint _mag_filter, GLint _wrap_s, GLint _wrap_t)
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

    // Create texture object
    glGenTextures(1, &m_id);
    
    // Set wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap_t);

    // Set filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _mag_filter);

    // Create texture data
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Destroy texture data
    stbi_image_free(data);
}


ugly::Texture::~Texture()
{
}


GLuint ugly::Texture::get_id() const
{
    return m_id;
}

