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
    ugly::Renderer* m_renderer {nullptr};

    /*! Selected sample */
    int m_sample {0};

    /*! Render mode (wireframe or fill) */
    int m_render_mode{ 1 };

    /*! Vertex array for simple triangle */
    ugly::VertexArrays m_va_triangle;

    /*! Vertex array for more attributes */
    ugly::VertexArrays m_va_more_attributes;

    /*! Basic program */
    ugly::Program m_program;

    /*! Program for uniform */
    ugly::Program m_program_uniform;

    /*! Program for more attributes*/
    ugly::Program m_program_attributes;

    /*! Program for inverted shader */
    ugly::Program m_program_inverted;

    /*! Program for offset shader */
    ugly::Program m_program_offset;

    /*! Program for pos as color shader */
    ugly::Program m_program_posascolor;
};