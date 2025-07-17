#include "program.h"
#include "shader.h"


ugly::Program::Program()
{
    m_id = glCreateProgram();
}


ugly::Program::Program(const ugly::Shader& _vertex_shader, const ugly::Shader& _fragment_shader) : Program()
{
    create(_vertex_shader, _fragment_shader);
}


ugly::Program::~Program()
{
    if(m_uniforms_location.size() != 0)
    {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}


void ugly::Program::create(const Shader& _vertex_shader, const Shader& _fragment_shader)
{
    glAttachShader(m_id, _vertex_shader.getId());
    glAttachShader(m_id, _fragment_shader.getId());
    glLinkProgram(m_id);
    glValidateProgram(m_id);

    int  success;
    char info_log[512];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, info_log);
        PLOG_ERROR << "program link failed: " << info_log;
        throw new std::runtime_error("Failed to link program");
    }
}


GLuint ugly::Program::getId() const
{
    return m_id;
}


void ugly::Program::setUniform(const std::string& _name, float _value)
{
    glUniform1f(getUniformLocation(_name), _value); 
}


void ugly::Program::setUniform(const std::string& _name, const glm::vec4& _value)
{
    glUniform4f(getUniformLocation(_name),
                _value.x,
                _value.y,
                _value.z,
                _value.w);
}


void ugly::Program::setUniform(const std::string& _name, const glm::mat4& _value)
{
    glUniformMatrix4fv(getUniformLocation(_name), 1, GL_FALSE, glm::value_ptr(_value));
}


void ugly::Program::setUniform(const std::string& _name, const uint32_t& _value)
{
    glUniform1ui(getUniformLocation(_name), _value);
}


void ugly::Program::setUniform(const std::string& _name, const int32_t& _value)
{
    glUniform1i(getUniformLocation(_name), _value);
}


GLint ugly::Program::getUniformLocation(const std::string& _name)
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