#pragma once

#include "core.h"

namespace ugly
{
    class Texture
    {
    public:
        /**
         * @brief Constructor.
         */
        Texture(const std::filesystem::path& _path,
            GLint _min_filter = GL_LINEAR_MIPMAP_LINEAR,
            GLint _mag_filter = GL_LINEAR, 
            GLint _wrap_s = GL_REPEAT,
            GLint _wrap_t = GL_REPEAT);

        /**
         * @brief Destructor.
         */
        virtual ~Texture();

        /**
         * @brief Get texture id.
         * 
         * @return Texture id
         */
        GLuint get_id() const;

    private:

        /*! Texture id */
        uint32_t m_id {0};
    };

}//namespace ugly