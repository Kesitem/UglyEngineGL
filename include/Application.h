#pragma once

#include "core.h"

namespace ugly
{
    /**
     * @brief Base application.
     */
    class Application
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
             * @brief Update application.
             */
            virtual void update();

            /**
             * @brief Render application.
             */
            virtual void draw();

            /**
             * @brief Render Gui.
             */
            virtual void renderGui();

            /**
             * @brief Get application name.
             * 
             * @return Application name
             */
            const std::string &getName() const;

        protected:

            /*! Application name */
            std::string m_name {"UglyBaseApplication"};
    };

}//namespace ugly