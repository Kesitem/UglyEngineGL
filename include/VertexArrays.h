#pragma once

#include "Core.h"

namespace ugly
{
    namespace gl
    {
        class VertexArrays
        {
        public:

            /**
             * @brief Constructor.
             */
            VertexArrays();

            /**
             * @brief Destructor. 
             */
            virtual ~VertexArrays();

            /**
             * @brief Create vertex array.
             * 
             * @return false if error 
             */
            bool create();

            /**
             * @brief Destroy vertex array.
             */
            void destroy();

            /**
             * @brief Define an array of generic vertex attribute data.
             * 
             * @param _index        Index of the generic vertex attribute
             * @param _size         Number of components per generic vertex attribute
             * @param _type         Data type of each component
             * @param _normalized   Specifies whether fixed-point data values should be normalized 
             * @param _stride       Byte offset between consecutive generic vertex attributes
             * @param _pointer      offset of the first component
             */
            void setVertexAttribPointer(GLuint _index, GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const void * _pointer);

            /**
             * @brief Enable a generic vertex attribute array.
             * 
             * @param _index Index of the generic vertex attribute
             */
            void enableVertexAttribArray(GLuint _index);

            /**
             * @brief Bind the vertex arrays.
             */
            void bind();

            /**
             * @brief Unbind the vertex arrays.
             */
            void unbind();

        private:

            /*! Vertex arrays id */
            GLuint m_id{0};
        };

    }//namespace gl

}//namespace ugly