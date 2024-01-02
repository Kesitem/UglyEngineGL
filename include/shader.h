#pragma once

#include "core.h"

namespace ugly
{
    enum class ShaderType
    {
        VERTEX = 35633,
        FRAGMENT = 35632
    };

    class Shader
    {
    public:

        Shader(const Shader& _shader) = delete;

        /**
         * @brief Constructor from shader source.
         * 
         * @param _shader_type  Type of shader
         * @param _source       Source
         */
        Shader(ShaderType _shader_type, const char* _source);

        /**
         * @brief Constructor from shader source file.
         *
         * @param _shader_type  Type of shader
         * @param _path         Source file path
         */
        Shader(ShaderType _shader_type, const std::filesystem::path& _path);

        /**
         * @brief Destructor.
         */
        virtual ~Shader();

        /**
         * @brief Create a shader from file source.
         * 
         * @param _shader_type Type of shader
         * @param _path        Path to the source
         * @return false if error
         */
        bool createFromFile(ShaderType _shader_type, const char* _path);

        /**
         * @brief Get the Id object.
         * 
         * @return Id
         */
        uint32_t getId() const;

    private:

        /**
         * @brief Create the shader from source.
         *
         * @param   shader_type    Type of shader
         * @param   source         Source of the shader
         */
        void create(ShaderType _shader_type, const char* _source);

    private:

        /*! shader id */
        uint32_t m_id{0};
    };
}