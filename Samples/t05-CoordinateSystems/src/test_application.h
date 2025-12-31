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

    /*! Vertex array for simple quad */
    GLuint m_va_quad {0};

    /*! Vertex buffer for quad */
    GLuint m_vbo_quad {0};

    /*! Element buffer for quad */
    GLuint m_ebo_quad {0};

    /*! Vertex array for simple cube */
    GLuint m_va_cube {0};

    /*! Vertex buffer for cube */
    GLuint m_vbo_cube {0};

    /*! Quad program .*/
    ugly::Program m_program;

    /*! Container texture */
    ugly::Texture m_texture_container;

    /*! Face texture */
    ugly::Texture m_texture_face;

    /*! Field of view */
    float m_fov{45.0f};

    /*! Aspect ratio */
    float m_aspect_ratio{4.0f / 3.0f};

    /*! View matrix translations */
    float m_view_translation_x{0.0f};
    float m_view_translation_y{0.0f};
    float m_view_translation_z{-3.0f};
};