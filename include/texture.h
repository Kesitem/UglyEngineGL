#pragma once

#include "core.h"

namespace ugly
{
    class Texture
    {
    public:

        /*! Filter list */
        static const std::array<GLint, 6> m_filters;

        /*! Filter list name */
        static const std::array<const char*, 6> m_filters_name;

    public:

        /**
         * @brief Constructor.
         */
        Texture();

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
         * @brief Create texture.
         * 
         * @param _path Path to texture
         * @param _min_filter Min filter
         * @param _mag_filter Mag filter
         * @param _wrap_s Wrap s
         * @param _wrap_t Wrap t
         */
        void create(const std::filesystem::path& _path,
            GLint _min_filter = GL_LINEAR_MIPMAP_LINEAR,
            GLint _mag_filter = GL_LINEAR, 
            GLint _wrap_s = GL_REPEAT,
            GLint _wrap_t = GL_REPEAT);

        /**
         * @brief Destroy texture.
         */
        void destroy();

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