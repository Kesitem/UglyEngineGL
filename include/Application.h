#pragma once

#include "core.h"
#include "Task.h"
#include "TaskManager.h"
#include "DisplayManager.h"
#include "InputManager.h"

namespace ugly
{
    /**
     * @brief Base application.
     */
    class Application : public Task
    {
        public:

            /**
             * @brief Constructor.
             */
            Application();

            /**
             * @brief Destructor.
             */
            virtual ~Application();

            /**
             * @brief Initialize application.
             */
            virtual void initialize();

            /**
             * @brief Shutdown application.
             */
            virtual void shutdown();

            /**
             * @brief Update application.
             */
            virtual void update();

            /**
             * @brief Update Gui.
             */
            virtual void updateGui();

            /**
             * @brief Render application.
             */
            virtual void render();

            /**
             * @brief Get application title.
             * 
             * @return Application title
             */
            const std::string &getTitle() const;

        protected:

            /*! Application name */
            std::string m_title {"UglyBaseApplication"};

            /*! Reference to the engine */
            std::shared_ptr<TaskManager> m_task_manager;

            /*! Input manager */
            std::shared_ptr<ugly::InputManager> m_input_manager{ nullptr };

            /*! Display manager */
            std::shared_ptr<ugly::DisplayManager> m_display_manager{ nullptr };
    };

}//namespace ugly