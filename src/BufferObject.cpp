#include "BufferObject.h"

/**
 * @brief Constructor.
 */
ugly::gl::BufferObject::BufferObject()
{
}


/**
 * @brief Destructor.
 */
ugly::gl::BufferObject::~BufferObject()
{
    destroy();
}


/**
 * @brief Create a buffer object.
 *  
 * @param _target   Target 
 * @param _size     Size in bytes
 * @param _data     Data or nullptr
 * @param _usage    Usage pattern
 * @return false if error
 */
bool ugly::gl::BufferObject::create(GLenum _target, GLsizeiptr _size, const void * _data, GLenum _usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(_target, m_id);  
    glBufferData(_target, _size, _data, _usage);

    return true;
}


/**
 * @brief Destroy buffer objet.
 */
void ugly::gl::BufferObject::destroy()
{
    if(m_id != 0)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}