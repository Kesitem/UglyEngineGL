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
 * @brief Create program from shader source file.
 * 
 * @param _vertex_shader_file   Vertex shader source file 
 * @param _fragment_shader_file Fragment shader source file
 * @return false  if error
 */
bool ugly::gl::Program::createFromFile(const char * _vertex_shader_file, const char * _fragment_shader_file)
{
    // Create vertex shader
    Shader vertex_shader;
    if(!vertex_shader.createFromFile(GL_VERTEX_SHADER, _vertex_shader_file))
    {
        PLOG_ERROR << "Failed to create vertex shader";
        return false;
    }

    // Create fragment shader
    Shader fragment_shader;
    if(!fragment_shader.createFromFile(GL_FRAGMENT_SHADER, _fragment_shader_file))
    {
        PLOG_ERROR << "Failed to create fragment shader";
        return false;
    }

    return create(&vertex_shader, &fragment_shader);
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


/**
 * @brief Set the Uniform float value
 * 
 * @param _name     Uniform name
 * @param _value    Value
 */
void ugly::gl::Program::setUniform(const std::string &_name, float _value)
{
    glUniform1f(getUniformLocation(_name), _value); 
}


/**
 * @brief Set the Uniform vec4 value
 * 
 * @param _name     Uniform name
 * @param _value    Value
 */
void ugly::gl::Program::setUniform(const std::string &_name, const glm::vec4 &_value)
{
    glUniform4f(getUniformLocation(_name),
                _value.x,
                _value.y,
                _value.z,
                _value.w);
}


/**
 * @brief Get the uniform location.
 * 
 * @param _name     Location name
 * @return GLint    Location
 */
GLint ugly::gl::Program::getUniformLocation(const std::string &_name)
{
    GLint location;
    auto it = m_uniforms_location.find(_name);
    if(it == m_uniforms_location.end())
    {
        location = glGetUniformLocation(m_id, _name.c_str());
        m_uniforms_location.insert(std::make_pair(_name, location));
    }
    else
    {
        location = it->second;
    }

    return location;
}