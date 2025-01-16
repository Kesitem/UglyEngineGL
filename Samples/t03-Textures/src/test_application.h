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

    /* Texture size for sandbox */
    GLfloat m_texture_scale {1.0f};

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

    /*! Quad program with color.*/
    ugly::Program m_program_quad_multi;

    /*! Quad program with face reverse.*/
    ugly::Program m_program_quad_multi_reverse;

    /*! Program for the sandbox.*/
    ugly::Program m_program_sandbox;

    /*! Container texture */
    ugly::Texture m_texture_container;

    /*! Face texture */
    ugly::Texture m_texture_face;

    /*! Container texture for wrapping */
    ugly::Texture m_texture_container_wrapping;

    /*! Face texture for wrapping*/
    ugly::Texture m_texture_face_wrapping;

    /*! Texture */
    unsigned int m_texture_wall {0};
};