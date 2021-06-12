#include "GL.h"

/**
 * @brief Set the viewport.
 * 
 * @param x     left corner
 * @param y     lower corner
 * @param width     width
 * @param height    height
*/
void ugly::gl::setViewport(GLint _x, GLint _y, GLsizei _width, GLsizei _height)
{
    // Set default viewport
    glViewport(_x, _y, _width, _height);
}


/**
 * @brief Specify clear values for the color buffers
 * 
 * @param _red      red value
 * @param _green    green value
 * @param _blue      blue value
 * @param _alpha     alpha value
 */
void ugly::gl::setClearColor(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _alpha)
{
    glClearColor(_red, _green, _blue, _alpha);
}


/**
 * @brief Clear buffers to preset values.
 * 
 * @param _mask Bitwise OR of masks that indicate the buffers to be cleared.
 */
void ugly::gl::clear(GLbitfield _mask)
{
    glClear(_mask);
}


/**
 * @brief Select a polygon rasterization mode.
 * 
 * @param _face Specifies the polygons that mode applies to
 * @param _mode Specifies how polygons will be rasterized
 */
void ugly::gl::setPolygonMode(GLenum _face, GLenum _mode)
{
    glPolygonMode(_face, _mode);
}


/**
 * @brief Render primitives from array data.
 * 
 * @param _mode     Kind of primites to render
 * @param _first    Starting index
 * @param _count    Number of indices to render
 */
void ugly::gl::drawArrays(GLenum _mode, GLint _first, GLsizei _count)
{
    glDrawArrays(_mode, _first, _count);
}


/**
 * @brief Render primitives from array data.
 * 
 * @param _mode     Kind of primites to render
 * @param _count    Number of elements to be rendered
 * @param _type     Type of the values in indices
 * @param _indices  Pointer to the location where the indices are stored
 */
void ugly::gl::drawElements(GLenum _mode, GLsizei _count, GLenum _type, const void * _indices)
{
    glDrawElements(_mode, _count, _type, _indices);
}