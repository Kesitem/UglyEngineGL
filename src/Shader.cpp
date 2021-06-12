#include "Shader.h"


/**
 * @brief Constructor.
 */
ugly::gl::Shader::Shader()
{
}


/**
 * @brief Destructor.
 */
ugly::gl::Shader::~Shader()
{
    destroy();
}


/**
 * @brief Create a shader.
 * 
 * @param _shader_type  Type of shader
 * @param _source       Source
 * @return false if error
 */
bool ugly::gl::Shader::create(GLenum _shader_type, const char* _source)
{
    m_id = glCreateShader(_shader_type);
    glShaderSource(m_id, 1, &_source, NULL);
    glCompileShader(m_id);

    int  success;
    char info_log[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_id, 512, NULL, info_log);
        PLOG_ERROR << "Shader compilation failed: " << info_log;
        return false;
    }

    return true;
}


/**
 * @brief Destroy shader. 
 */
void ugly::gl::Shader::destroy()
{
    if(m_id != 0)
    {
        glDeleteShader(m_id);
        m_id = 0;
    }
}


/**
 * @brief Get the Id object.
 * 
 * @return Id
 */
GLuint ugly::gl::Shader::getId() const
{
    return m_id;
}