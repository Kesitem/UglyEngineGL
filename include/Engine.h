#pragma once

#include "Core.h"
#include "Application.h"
#include "TaskManager.h"
#include "InputManager.h"
#include "GuiManager.h"
#include "DisplayManager.h"


namespace ugly
{

/**
 * \class Engine
 * \brief Main class of the engine.
 * Engine is a singleton to easily use it anywhere.
 */
class Engine
{
public:

    /**
     * \brief Get the instance of the engine.
     */
    static Engine * const getInstance()
    {
        static Engine engine;
        return &engine;
    }

    /**
     * @brief Initialize engine.
     */
    void initialize();

    /**
     * @brief Run the application.
     * Engine take ownership of the application. It will destroy application.
     * 
     * @param _application  Application to run
     */
    void run(std::shared_ptr<Application> _application);

    /**
     * \brief Request application to quit.
     */
    void quit();

    /**
     * \brief Get display manager.
     *
     * \return Display manager
     */
    std::shared_ptr<DisplayManager> getDisplayManager() const;

    /**
     * \brief Get input manager.
     *
     * \return Input manager
     */
    std::shared_ptr<InputManager> getInputManager() const;

    /**
     * \brief Get task manager.
     *
     * \return Task manager
     */
    std::shared_ptr<TaskManager> getTaskManager() const;

    /**
     * \brief Get GLFW window.
     *
     * \return GLFW window.
     */
    GLFWwindow* getWindow() const;

private:

    /**
     * @brief Constructor.
     */
    Engine();

    /**
     * @brief Destructor.
     */
    virtual ~Engine();

    /**
     * @brief Initialize plog.
     */
    void initializePLog();

    /**
     * @brief Shutdown engine.
     */
    void shutdown();

    /**
     * @brief Execute main loop.
     * 
     * @return false if error
     */
    void mainLoop();

private:

    /*! GLFW Window */
    GLFWwindow* m_window {nullptr};

    /*! Display size */
    glm::ivec2 m_display_size {glm::ivec2(960, 540)};

    /*! Quit flag */
    bool m_quit {false};
    
    /*! Input manager */
    std::shared_ptr<InputManager> m_input_manager {nullptr};

    /*! Display manager */
    std::shared_ptr<DisplayManager> m_display_manager{ nullptr };

    /*! GUI manager */
    std::shared_ptr<GuiManager> m_gui_manager{ nullptr };

    /*! Task manager */
    std::shared_ptr<TaskManager> m_task_manager{ nullptr };

    /*! Application */
    std::shared_ptr<Application> m_application{ nullptr };
};

}//namespace ugly