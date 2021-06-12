#pragma once

#include "Core.h"

namespace ugly::gl
{
    /**
     * @brief Buffer object. 
     */
    class BufferObject
    {
    public:

        /**
         * @brief Constructor.
         */
        BufferObject();

        /**
         * @brief Destructor.
         */
        virtual ~BufferObject();

        /**
         * @brief Create a buffer object.
         *  
         * @param _target   Target 
         * @param _size     Size in bytes
         * @param _data     Data or nullptr
         * @param _usage    Usage pattern
         * @return false if error
         */
        bool create(GLenum _target, GLsizeiptr _size, const void * _data, GLenum _usage);

        /**
         * @brief Destroy buffer objet.
         */
        void destroy();

    private:

        /** Object id */
        GLuint m_id;
    };
}