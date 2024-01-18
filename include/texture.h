#pragma once

#include "core.h"

namespace ugly
{
    class Texture
    {
    public:

        enum class MinMagFilter
        {
            NEAREST = GL_NEAREST,
            LINEAR = GL_LINEAR,
            NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
            LINEAR_MIPMAP_NEAREST =  GL_LINEAR_MIPMAP_NEAREST,
            NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
            LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
        };

        enum class WrapFilter
        {
            REPEAT = GL_REPEAT,
            MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
            CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
            CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
        };

        /**
         * @brief Constructor.
         */
        Texture(const std::filesystem::path& _path,
            MinMagFilter _min_filter = MinMagFilter::LINEAR_MIPMAP_LINEAR,
            MinMagFilter _mag_filter = MinMagFilter::LINEAR, 
            WrapFilter _wrap_s = WrapFilter::REPEAT,
            WrapFilter _wrap_t = WrapFilter::REPEAT);

        /**
         * @brief Destructor.
         */
        virtual ~Texture();

        /**
         * @brief Bind texture.
         * 
         * @param _unit Texture unit
         */
        void bind(uint32_t _unit = 0);

        /**
         * @brief Set texture filtering paramaters
         * 
         * @param min_filter Minifying parameter
         * @param mag_filter Magnifying parameter
         */
        void setFilter(MinMagFilter min_filter, MinMagFilter mag_filter);

        /**
         * @brief Set the texture wrap paramaters.
         * 
         * @param wrap_s Wrapping paramater on s
         * @param wrap_t Wrapping paramater on t
         */
        void setWrap(WrapFilter wrap_s, WrapFilter wrap_t);

    private:

        /*! Texture id */
        uint32_t m_id {0};
    };

}//namespace ugly