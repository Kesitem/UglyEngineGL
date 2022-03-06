#include "DisplayManager.h"


ugly::DisplayManager::DisplayManager()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PLOG_ERROR << "Failed to initialize GLAD";
        throw new std::runtime_error("Failed to initialize GLAD");
    }
}


ugly::DisplayManager::~DisplayManager()
{
}


void ugly::DisplayManager::setViewport(int _x, int _y, unsigned int _width, unsigned int _height)
{
    // Set default viewport
    glViewport(_x, _y, _width, _height);
}


void ugly::DisplayManager::setClearColor(float _red, float _green, float _blue, float _alpha)
{
    glClearColor(_red, _green, _blue, _alpha);
}


void ugly::DisplayManager::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


void ugly::DisplayManager::setPolygonMode(PolygoneMode _mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, (GLenum)_mode);
}


void ugly::DisplayManager::drawArrays(uint32_t _count, int32_t _first)
{
    glDrawArrays(GL_TRIANGLES, _first, _count);
}


void ugly::DisplayManager::drawElements(uint32_t _count)
{
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);
}