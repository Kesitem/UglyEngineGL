#include "UglyEngine.h"

class TestApplication : public ugly::Application
{
public:

    /**
     * @brief Constructor.
     */
    TestApplication();

    /**
     * @brief Destructor.
     */
    virtual ~TestApplication();

    /**
     * @brief Initialize application
     */
    void initialize();

    /**
     * @brief Shutdown application
     */
    void shutdown();

    /**
     * @brief Update application
     */
    void update();

private:

    /*! Engine */
    ugly::Engine* m_engine {nullptr};

    /*! Input manager */
    ugly::InputManager* m_input_manager {nullptr};

    /*! Basic program */
    ugly::Program m_program;

    /*! Vertex array for simple triangle */
    GLuint m_va_triangle {0};

    /*! Vertex array for simple quad */
    GLuint m_va_quad {0};

    /*! Texture */
    unsigned int m_texture_wall {0};
};