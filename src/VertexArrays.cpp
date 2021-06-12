#include "VertexArrays.h"


/**
 * @brief Constructor.
 */
ugly::gl::VertexArrays::VertexArrays()
{
}


/**
 * @brief Destructor. 
 */
ugly::gl::VertexArrays::~VertexArrays()
{
    destroy();
}


/**
 * @brief Create vertex array.
 * 
 * @return false if error 
 */
bool ugly::gl::VertexArrays::create()
{
    glGenVertexArrays(1, &m_id);
    bind();

    return true;
}


/**
 * @brief Destroy vertex array.
 */
void ugly::gl::VertexArrays::destroy()
{
    if(m_id != 0)
    {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}


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
void ugly::gl::VertexArrays::setVertexAttribPointer(GLuint _index, GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const void * _pointer)
{
    glVertexAttribPointer(_index, _size, _type, _normalized, _stride, _pointer);
}


/**
 * @brief Enable a generic vertex attribute array.
 * 
 * @param _index Index of the generic vertex attribute
 */
void ugly::gl::VertexArrays::enableVertexAttribArray(GLuint _index)
{
    glEnableVertexAttribArray(_index);
}


/**
 * @brief Bind the vertex arrays.
 */
void ugly::gl::VertexArrays::bind()
{
    glBindVertexArray(m_id);
}

/**
 * @brief Unbind the vertex arrays.
 */
void ugly::gl::VertexArrays::unbind()
{
    glBindVertexArray(0);
}