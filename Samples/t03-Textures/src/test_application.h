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

    /*! Current sample */
    int m_sample {0};

    /*! Render mode (wireframe or fill) */
    int m_render_mode{ 1 };

    /*! Basic program */
    ugly::Program m_program;

    /*! Vertex array for simple triangle */
    GLuint m_va_triangle {0};

    /*! Vertex array for simple quad */
    GLuint m_va_quad {0};

    /*! Quad program .*/
    ugly::Program m_program_quad;

    /*! Quad program with color.*/
    ugly::Program m_program_quad_color;

    /*! Container texture */
    std::unique_ptr<ugly::Texture> m_texture_container;

    /*! Texture */
    unsigned int m_texture_wall {0};
};