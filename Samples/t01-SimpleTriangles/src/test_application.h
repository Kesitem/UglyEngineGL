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

    /**
     * @brief Update IMGUI
     */
    void updateImgui();

private:

    /*! Engine */
    ugly::Engine* m_engine {nullptr};

    /*! Input manager */
    ugly::InputManager* m_input_manager {nullptr};

    /*! Shader program orange*/
    ugly::Program m_program_orange;

    /*! Shader program yellow*/
    ugly::Program m_program_yellow;

    /*! Vertex array for simple triangle */
    GLuint m_va_triangle {0};

    /*! Vertex array for the quad */
    GLuint m_va_quad {0};

    /*! Vertex array for the double triangle */
    GLuint m_va_double_triangle;

    /*! Vertex array for simple triangle 0 */
    GLuint m_va_triangle_0;

    /*! Vertex array for simple triangle 1 */
    GLuint m_va_triangle_1;

    /*! Selected sample */
    int m_sample {0};

    /*! Render mode (wireframe or fill) */
    int m_render_mode{ 1 };
};