#include "Engine.h"
#include "LogFormatter.h"


ugly::Engine::Engine()
{
    initializePLog();

    auto path = std::filesystem::current_path();
    LOG_INFO << "Current path: " << path.c_str();
}


ugly::Engine::~Engine()
{
    shutdown();
}

void ugly::Engine::initialize()
{
    PLOG_INFO << "--- Initialize engine";

    if (!glfwInit())
    {
        PLOG_ERROR << "Failed to initialize GLFW";
        throw new std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    PLOG_INFO << "Display size: " << m_display_size.x << "*" << m_display_size.y;
    m_window = glfwCreateWindow(m_display_size.x, m_display_size.y, project::NAME.c_str(), NULL, NULL);
    if (m_window == nullptr)
    {
        PLOG_ERROR << "Failed to create GLFW window";
        throw new std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_window);

    LOG_DEBUG << "creeate display manager";
    try
    {
        m_display_manager = std::make_shared<DisplayManager>();
    }
    catch (const std::runtime_error& e)
    {
        PLOG_ERROR << "Failed to initialize display manager. Error: " << e.what();
        throw new std::runtime_error("Failed to initialize display manager");
    }

    m_display_manager->setViewport(0, 0, m_display_size.x, m_display_size.y);

    m_gui_manager = std::make_shared<GuiManager>(m_window);

    m_input_manager = std::make_shared<InputManager>();
}

void ugly::Engine::run(std::shared_ptr<Application> _application)
{
    LOG_INFO << "Run the engine";

    if (_application.get() == nullptr)
    {
        LOG_ERROR << "Invalid application";
        throw new std::runtime_error("Invalid application");
    }

    m_application = _application;
    LOG_INFO << "Run application: " << m_application->getName();

    mainLoop();
}


void ugly::Engine::quit()
{
    m_quit = true;
}


std::shared_ptr<ugly::InputManager> ugly::Engine::getInputManager() const
{
    return m_input_manager;
}


std::shared_ptr<ugly::DisplayManager> ugly::Engine::getDisplayManager() const
{
    return m_display_manager;
}

GLFWwindow* ugly::Engine::getWindow() const
{
    return m_window;
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
    static plog::RollingFileAppender<plog::LogFormatter> fileAppender(LOG_FILENAME.c_str(), 0, 0);
    static plog::ConsoleAppender<plog::LogFormatter> consoleAppender;

    plog::init(plog::debug, &consoleAppender).addAppender(&fileAppender);

    PLOG_INFO << "----- UglyEngine Log";
    PLOG_INFO << "----- Version: " << ugly::version::FULLVERSION_STRING;
}





/**
 * \breif Shutdown engine.
 */
void ugly::Engine::shutdown()
{
    PLOG_INFO << "--- Shutdown engine";

    if(m_application.get() != nullptr)
        m_application.reset();

    if (m_gui_manager.get() != nullptr)
        m_gui_manager.reset();

    if(m_input_manager.get() != nullptr)
        m_input_manager.reset();

    if (m_display_manager.get() != nullptr)
        m_display_manager.reset();


    m_window = nullptr;
    glfwTerminate();
}


void ugly::Engine::mainLoop()
{
    PLOG_INFO << "--- Enter main loop";

    while(!m_quit)
    {
        if(glfwWindowShouldClose(m_window))
            m_quit = true;

        m_application->update();
        m_gui_manager->beginFrame();
        m_application->renderGui();
        m_gui_manager->endFrame();
        
        m_input_manager->update();
        
        m_application->draw();
        m_gui_manager->draw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();    
    }
}