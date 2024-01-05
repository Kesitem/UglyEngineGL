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

    /*! Display manager */
    ugly::DisplayManager* m_display_manager {nullptr};

    /*! Selected sample */
    int m_sample {0};

    /*! Render mode (wireframe or fill) */
    int m_render_mode{ 1 };

    /*! Vertex array for simple triangle */
    ugly::VertexArrays m_va_triangle;

    /*! Shader program */
    ugly::Program m_program;

    /*! Shader program for uniform */
    ugly::Program m_program_uniform;
};