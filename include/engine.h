#pragma once

namespace ugly
{
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

    private:

        /*! Singleton instance */
        inline static Engine* m_instance {nullptr};

    };

}//namespace ugly