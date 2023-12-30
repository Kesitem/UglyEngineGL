#pragma once

namespace ugly
{
    /**
     * @class Application
     * @brief Base application
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
         * @brief Initialize application
         */
        virtual void initialize();

        /**
         * @brief Shutdown application
         */
        virtual void shutdown();

        /**
         * @brief Update application
         */
        virtual void update();
    };

}//namespace ugly