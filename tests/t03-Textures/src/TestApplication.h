#pragma once

#include "UglyEngine.h"

/**
 * @brief Test application.
 * 
 */
class TestApplication : public ugly::Application
{
public:

    /**
     * @brief Constructor.
     */
    TestApplication();

    /**
     * @brief Initialize application.
     * 
     * @return False if error
     */
    bool initialize();

    /**
     * @brief Shutdown application.
     */
    void shutdown();

    /**
     * @brief Update application.
     */
    void update();

private:

    /**
     * @brief Create triangle data.
     */
    void createTriangle();

    /**
     * @brief Draw triangle.
     */
    void drawTriangle();

    /**
     * @brief Create quad data.
     */
    void createQuad();

    /**
     * @brief Draw triangle.
     */
    void drawQuad();

    /**
     * @brief Draw quad with reverse face.
     */
    void drawQuadReverse();

private:

    std::shared_ptr<ugly::InputManager> m_input_manager;
    std::shared_ptr<ugly::DisplayManager> m_display_manager;

    /*! Triangle VAO */
    std::shared_ptr<ugly::VertexArrays> m_triangle_va;

    /*! Texture */
    std::shared_ptr<ugly::Texture> m_texture;

    /*! Program */
    std::shared_ptr<ugly::Program> m_shader_program;

    /*! Quad VAO */
    std::shared_ptr<ugly::VertexArrays> m_quad_va;

    /*! Quad texture */
    std::shared_ptr<ugly::Texture> m_quad_texture;

    /*! Program */
    std::shared_ptr<ugly::Program> m_quad_shader_program;

    /*! Shader with reverse face */
    std::shared_ptr<ugly::Program> m_quad_reverse_shader_program;

    /*! Face texture */
    std::shared_ptr<ugly::Texture> m_face_texture;

    /*! Wireframe flag */
    bool m_wireframe {false};

    /*! Render type. 0 = triangle, 1 = quad */
    int m_render_type {0};
};