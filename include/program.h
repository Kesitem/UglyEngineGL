#pragma once

#include "core.h"

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
         * @brief Default constructor.
         */
        Program();
        
        /**
         * @brief Constructor from Shader objects.
         * 
         * @param _vertex_shader    Vertex shader 
         * @param _fragment_shader  Program shader
         */
        Program(const Shader& _vertex_shader, const Shader& _fragment_shader);

        /**
         * @brief Destructor.
         */
        virtual ~Program();

        /**
         * @Brief Create program from shader objects.
         * 
         * @param _vertex_shader    Vertex shader 
         * @param _fragment_shader  Program shader
         */
        void create(const Shader& _vertex_shader, const Shader& _fragment_shader);

        /**
         * @brief Use shader program.
         */
        void use();

        /**
         * @brief Set the Uniform float value
         * 
         * @param name     Uniform name
         * @param value    Value
         */
        void setUniform(const std::string &_name, float _value);

        /**
         * @brief Set the Uniform vec4 value
         * 
         * @param name     Uniform name
         * @param value    Value
         */
        void setUniform(const std::string& _name, const glm::vec4& _value);

        /**
         * @brief Set the Uniform mat4 value
         *
         * @param name     Uniform name
         * @param value    Value
         */
        void setUniform(const std::string& _name, const glm::mat4& _value);

        /**
         * @brief Set the Uniform unsigned int value
         *
         * @param name     Uniform name
         * @param value    Value
         */
        void setUniform(const std::string& _name, const uint32_t& _value);

        /**
         * @brief Set the Uniform unsigned int value
         *
         * @param name     Uniform name
         * @param value    Value
         */
        void setUniform(const std::string& _name, const int32_t& _value);

    private:

        /**
         * @brief Get the uniform location.
         * 
         * @param name     Location name
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