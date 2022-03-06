#pragma once

#include "Core.h"

namespace ugly
{
    class Shader;

    /**
     * @brief OpenGL program.
     */
    class Program
    {
    public:

        /**
         * @brief Constructor from Shader objects.
         * 
         * @param _vertex_shader    Vertex shader 
         * @param _fragment_shader  Program shader
         */
        Program(std::shared_ptr<Shader> _vertex_shader, std::shared_ptr<Shader> _fragment_shader);

        /**
         * @brief Constructor from path to shader files.
         *
         * @param _vertex_shader_path    Vertex shader path
         * @param _fragment_shader_path  Program shader path
         */
        Program(const std::filesystem::path& _vertex_sharder_path, const std::filesystem::path& _fragment_shader_path);

        /**
         * @brief Destructor.
         */
        virtual ~Program();

        /**
         * @brief Use shader program.
         */
        void use();

        /**
         * @brief Set the Uniform float value
         * 
         * @param _name     Uniform name
         * @param _value    Value
         */
        void setUniform(const std::string &_name, float _value);

        /**
         * @brief Set the Uniform vec4 value
         * 
         * @param _name     Uniform name
         * @param _value    Value
         */
        void setUniform(const std::string &_name, const glm::vec4 &_value);

        /**
         * @brief Set the Uniform unsigned int value
         *
         * @param _name     Uniform name
         * @param _value    Value
         */
        void setUniform(const std::string& _name, const uint32_t& _value);

        /**
         * @brief Set the Uniform unsigned int value
         *
         * @param _name     Uniform name
         * @param _value    Value
         */
        void setUniform(const std::string& _name, const int32_t& _value);

    private:

        /**
         * @brief Get the uniform location.
         * 
         * @param _name     Location name
         * @return GLint    Location
         */
        GLint getUniformLocation(const std::string &_name);
        
    private: 

        /*! Program id */
        GLuint m_id{0};

        
        /*! Uniforms location */
        std::map<std::string, GLint> m_uniforms_location;
    };
}