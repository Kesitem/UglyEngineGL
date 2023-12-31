#pragma once

#include "core.h"
namespace ugly
{
    class Application;
    class InputManager;

    class Engine
    {
    public:
    
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        /**
         * @brief Get the instance of the engine.
         */
        static Engine* getInstance()
        {
            if(!m_instance)
                m_instance = new Engine();
            return m_instance;
        }

        /**
         * @brief Run the engine.
         * 
         * @param application   Application to run
         */
        void run(Application* application);

        /**
         * @brief Quit the engine.
         */
        void quit();

        /**
         * @brief Get GLFW window
         * 
         * @return GLFW window 
         */
        GLFWwindow* getWindow() const;

        /**
         * @brief Get input manager.
         * 
         * @return Input manager
        */
        InputManager* getInputManager() const;
        
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
         * @brief Initialize engine.
         */
        void initialize();

        /**
         * @brief Shutdown engine.
         */
        void shutdown();

        /**
         * @brief Main loop.
         */
        void mainLoop();

    private:

        /*! Singleton instance */
        inline static Engine* m_instance {nullptr};

        /*! Application */
        std::unique_ptr<ugly::Application> m_application {nullptr};

        /*! Input manager */
        std::unique_ptr<ugly::InputManager> m_input_manager {nullptr};

        /*! Quit flag */
        bool m_quit {false};

        /*! GFLW window */
        GLFWwindow* m_window {nullptr};

        /*! Window width */
        int m_window_width {1280};

        /*! Window width */
        int m_window_height {720};


    };

}//namespace ugly