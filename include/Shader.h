#pragma once

#include "Core.h"

namespace ugly::gl
{
    class Shader
    {
    public:

        /**
         * @brief Constructor.
         */
        Shader();

        /**
         * @brief Destructor.
         */
        virtual ~Shader();

        /**
         * @brief Create a shader.
         * 
         * @param _shader_type  Type of shader
         * @param _source       Source
         * @return false if error
         */
        bool create(GLenum _shader_type, const char* _source);

        /**
         * @brief Destroy shader. 
         */
        void destroy();

        /**
         * @brief Get the Id object.
         * 
         * @return Id
         */
        GLuint getId() const;

    private:

        /*! Shader id */
        GLuint m_id{0};
    };
}