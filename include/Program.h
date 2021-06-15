#pragma once

#include "Core.h"

namespace ugly::gl
{
    class Shader;

    /**
     * @brief OpenGL program.
     */
    class Program
    {
    public:

        /**
         * @brief Constructor.
         */
        Program();

        /**
         * @brief Destructor.
         */
        virtual ~Program();

        /**
         * @brief Create program
         * 
         * @param _vertex_shader    Vertex shader 
         * @param _fragment_shader  Program shader
         * @return false if error
         */
        bool create(const Shader * _vertex_shader, const Shader * _fragment_shader);

        /**
         * @brief Create program from shader source file.
         * 
         * @param _vertex_shader_file   Vertex shader source file 
         * @param _fragment_shader_file Fragment shader source file
         * @return false  if error
         */
        bool createFromFile(const char * _vertex_shader_file, const char * _fragment_shader_file);

        /**
         * @brief Destroy program.
         */
        void destroy();

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