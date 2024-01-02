#include "program.h"
#include "shader.h"


ugly::Program::Program(const ugly::Shader& _vertex_shader, const ugly::Shader& _fragment_shader)
{
    m_id = glCreateProgram();
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


ugly::Program::Program(const char* _vertex_shader_source, const char* _fragment_shader_source) : 
    Program(ugly::Shader(ShaderType::VERTEX, _vertex_shader_source), 
            ugly::Shader(ShaderType::FRAGMENT, _fragment_shader_source))
{
}


ugly::Program::Program( const std::filesystem::path& _vertex_sharder_path,
                        const std::filesystem::path& _fragment_shader_path) : 
    Program(Shader(ShaderType::VERTEX, _vertex_sharder_path), 
            Shader(ShaderType::FRAGMENT, _fragment_shader_path))
{
}


ugly::Program::~Program()
{
    if(m_uniforms_location.size() != 0)
    {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}


void ugly::Program::use()
{
    glUseProgram(m_id);
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