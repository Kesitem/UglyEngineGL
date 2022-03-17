#include "DisplayManager.h"


void GLAPIENTRY OpenGLMessageCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity,
    GLsizei _length, const GLchar* _message, const void* _user_param)
{
    static std::string source;
    switch (_source)
    {
    case GL_DEBUG_SOURCE_API:
        source = "OpenGL API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source = "Window - system API";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source = "Shading language compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source = "Third party application";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        source = "Source application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        source = "Other";
        break;
    }

    static std::string type;
    switch (_type)
    {
    case GL_DEBUG_TYPE_ERROR:
        type = "Error API";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type = "deprecated behavior"; 
        break; 
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type = "Undefined behavior";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type = "Functionality not portable";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type = "Performance issues";
        break;
    case GL_DEBUG_TYPE_MARKER:
        type = "Command stream annotation";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        type = "Group pushing";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        type = "Group popping";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type = "Other";
        break;
    }

    switch (_severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        LOG_ERROR << "Source: " << source << " - Type: " << type << " - Message: " << _message;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        LOG_WARNING << "Source: " << source << " - Type: " << type << " - Message: " << _message;
        break;
    case GL_DEBUG_SEVERITY_LOW:
        LOG_INFO << "Source: " << source << " - Type: " << type << " - Message: " << _message;
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        LOG_DEBUG << "Source: " << source << " - Type: " << type << " - Message: " << _message;
        break;
    }
}


ugly::DisplayManager::DisplayManager()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PLOG_ERROR << "Failed to initialize GLAD";
        throw new std::runtime_error("Failed to initialize GLAD");
    }

    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, 0);
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