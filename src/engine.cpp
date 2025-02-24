#include "engine.h"
#include "config.h"
#include "core.h"
#include "log_formatter.h"
#include "application.h"
#include "input_manager.h"
#include "renderer.h"
#include "imgui_manager.h"


ugly::Engine::Engine()
{
    initializePLog();

    auto path = std::filesystem::current_path();
    LOG_INFO << "Current path: " << path.c_str();    
}


ugly::Engine::~Engine()
{
}


void ugly::Engine::initialize()
{
    LOG_INFO << "Initialize engine";

    if (!glfwInit())
    {
        LOG_ERROR << "Failed to init GLFW";
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    LOG_INFO << "Window size: " << m_window_width << "x" << m_window_height;
    m_window = glfwCreateWindow(m_window_width, m_window_height, ugly::project::NAME, NULL, NULL);
    if (!m_window)
    {
        LOG_ERROR << "Failed to create GLFW window";
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);

    m_renderer = std::make_unique<Renderer>();
    m_input_manager = std::make_unique<InputManager>();
    m_imgui_manager = std::make_unique<ImguiManager>(m_window);

    m_renderer->setViewport(0, 0, m_window_width, m_window_height);
}



void ugly::Engine::shutdown()
{
    LOG_INFO << "Shutdown engine";

    if(m_imgui_manager.get() != nullptr)
        m_imgui_manager.reset();

    if(m_input_manager.get() != nullptr)
        m_input_manager.reset();

    if (m_renderer.get() != nullptr)
        m_renderer.reset();

    glfwTerminate();
}

void ugly::Engine::run(Application* _application)
{
    LOG_INFO << "--- Run the application";

    if(_application == nullptr)
    {
        LOG_ERROR << "Invalid application";
        throw std::runtime_error("Invalid application");
    }
    m_application.reset(_application);

    try
    {
        m_application->initialize();
    }
    catch(const std::runtime_error& e)
    {
        LOG_ERROR << e.what();
        m_application->shutdown();
        m_application.reset();
        throw std::runtime_error("Failed to initialize application");
    }
    
    try
    {
        mainLoop();
    }
    catch(const std::runtime_error& e)
    {
        LOG_ERROR << e.what();
        throw std::runtime_error("Error while running main loop");
    }
    
    m_application->shutdown();
    m_application.reset();
}


void ugly::Engine::quit()
{
    m_quit = true;
}


GLFWwindow* ugly::Engine::getWindow() const
{
    return m_window;
}


ugly::InputManager* ugly::Engine::get_input_manager() const
{
    return m_input_manager.get();
}


ugly::Renderer* ugly::Engine::getRenderer() const
{
    return m_renderer.get();
}


int ugly::Engine::get_window_with() const
{
    return m_window_width;
}


int ugly::Engine::get_window_height() const
{
    return m_window_height;
}


void ugly::Engine::initializePLog()
{
    // Remove log file if exists
    struct stat buffer;
    if (stat(LOG_FILENAME.c_str(), &buffer) == 0)
    {
        if (remove(LOG_FILENAME.c_str()) != 0)
        {
            LOG_ERROR << "Cannnot remove log file";
        }
    }

    // Create log
    static plog::RollingFileAppender<plog::LogFormatter> file_appender(LOG_FILENAME.c_str(), 0, 0);
    static plog::ConsoleAppender<plog::LogFormatter> console_appender;

    plog::init(plog::debug, &console_appender).addAppender(&file_appender);
}


void ugly::Engine::mainLoop()
{
    LOG_INFO << "Enter main loop";

    while (!m_quit)
    {
        if(glfwWindowShouldClose(m_window))
            m_quit = true;

        m_application->update();

        m_imgui_manager->beginFrame();
        m_application->updateImgui();
        m_imgui_manager->endFrame();

        m_input_manager->update();

        m_imgui_manager->draw();
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}