#include "shader.h"

ugly::Shader::Shader(GLenum _shader_type, const char* _source)
{
    create(_shader_type, _source);
}


ugly::Shader::Shader(GLenum _shader_type, const std::filesystem::path& _path)
{
    // Open file
    std::ifstream ifs(_path, std::ios::in);
    if (!ifs)
    {
        PLOG_ERROR << "Failed to open shader file: " << _path.c_str();
        throw new std::runtime_error("Failed to open shader file");
    }

    // Read file buffer
    std::ostringstream sstr;
    sstr << ifs.rdbuf();

    // Close stream
    ifs.close();

    create(_shader_type, sstr.str().c_str());
}


ugly::Shader::~Shader()
{
    if (m_id != 0)
    {
        glDeleteShader(m_id);
        m_id = 0;
    }
}


uint32_t ugly::Shader::getId() const
{
    return m_id;
}


void ugly::Shader::create(GLenum _shader_type, const char* _source)
{
    m_id = glCreateShader((uint32_t)_shader_type);
    glShaderSource(m_id, 1, &_source, NULL);
    glCompileShader(m_id);

    int  success;
    char info_log[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, NULL, info_log);
        PLOG_ERROR << (_shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compilation failed: " << info_log;
        PLOG_DEBUG << "shader source: " << _source;
        glDeleteShader(m_id);
        throw new std::runtime_error("Failed to create shader");
    }
}