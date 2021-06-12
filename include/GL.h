#pragma once

#include "Core.h"

namespace ugly
{
    /**
     * @brief OpenGL namespace
     * 
     */
    namespace gl
    {
        /**
         * @brief Set the viewport.
         * 
         * @param _x     left corner
         * @param _y     lower corner
         * @param _width     width
         * @param _height    height
         */
        void setViewport(GLint _x, GLint _y, GLsizei _width, GLsizei _height);

        /**
         * @brief Specify clear values for the color buffers.
         * 
         * @param _red      red value
         * @param _green    green value
         * @param _blue     blue value
         * @param _alpha    alpha value
         */
        void setClearColor(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _alpha);

        /**
         * @brief Clear buffers to preset values.
         * 
         * @param _mask Bitwise OR of masks that indicate the buffers to be cleared.
         */
        void clear(GLbitfield _mask);

        /**
         * @brief Select a polygon rasterization mode.
         * 
         * @param _face Specifies the polygons that mode applies to
         * @param _mode Specifies how polygons will be rasterized
         */
        void setPolygonMode(GLenum _face, GLenum _mode);

        /**
         * @brief Render primitives from array data.
         * 
         * @param _mode     Kind of primites to render
         * @param _first    Starting index
         * @param _count    Number of indices to render
         */
        void drawArrays(GLenum _mode, GLint _first, GLsizei _count);

        /**
         * @brief Render primitives from array data.
         * 
         * @param _mode     Kind of primites to render
         * @param _count    Number of elements to be rendered
         * @param _type     Type of the values in indices
         * @param _indices  Pointer to the location where the indices are stored
         */
        void drawElements(GLenum _mode, GLsizei _count, GLenum _type, const void * _indices);

    }//gl

}//namespace ugly