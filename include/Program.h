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
         * @brief Destroy program.
         */
        void destroy();

        /**
         * @brief Use shader program.
         */
        void use();
        
    private: 

        /*! Program id */
        GLuint m_id{0};
    };
}