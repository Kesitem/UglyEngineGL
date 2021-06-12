#include "Program.h"
#include "Shader.h"


/**
 * @brief Constructor.
 */
ugly::gl::Program::Program()
{
}


/**
 * @brief Destructor.
 */
ugly::gl::Program::~Program()
{
    destroy();
}


/**
 * @brief Create program
 * 
 * @param _vertex_shader    Vertex shader 
 * @param _fragment_shader  Program shader
 * @return false if error
 */
bool ugly::gl::Program::create(const ugly::gl::Shader *_vertex_shader, const ugly::gl::Shader *_fragment_shader)
{
    m_id = glCreateProgram();
    glAttachShader(m_id, _vertex_shader->getId());
    glAttachShader(m_id, _fragment_shader->getId());
    glLinkProgram(m_id);

    int  success;
    char info_log[512];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(m_id, 512, NULL, info_log);
        PLOG_ERROR << "program link failed: " << info_log;
        return false;
    }

    return true;
}

/**
 * @brief Destroy program.
 */
void ugly::gl::Program::destroy()
{
    if(m_id != 0)
    {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}


/**
 * @brief Use shader program.
 */
void ugly::gl::Program::use()
{
    glUseProgram(m_id);
}