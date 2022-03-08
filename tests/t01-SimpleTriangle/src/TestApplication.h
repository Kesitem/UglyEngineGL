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
     * @brief Update application.
     */
    void update();

    /**
     * @brief Render application.
     */
    void draw();

    /**
     * @brief Render Gui.
     */
    void renderGui();

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
     * @brief Draw quad.
     */
    void drawQuad();

    /**
     * @brief Create triangles data.
     */
    void createTriangles();

    /**
     * @brief Draw triangles.
     */
    void drawTriangles();

    /**
     * @brief Create triangles data.
     */
    void createTriangles2VA();

    /**
     * @brief Draw triangles.
     */
    void drawTriangles2VA();

    /**
     * @brief Draw triangles.
     */
    void drawTriangles2VA2Programs();

private:

    /*! Input manager */
    std::shared_ptr<ugly::InputManager> m_input_manager {nullptr};

    /*! Display manager */
    std::shared_ptr<ugly::DisplayManager> m_display_manager{ nullptr };

    /*! Triangle VAO */
    std::shared_ptr<ugly::VertexArrays> m_triangle_va;

    /*! Triangle VAO */
    std::shared_ptr<ugly::VertexArrays> m_triangles_va;

    /*! Quad VAO */
    std::shared_ptr<ugly::VertexArrays> m_quad_va;

    std::shared_ptr<ugly::VertexArrays> m_triangles_20_va;

    std::shared_ptr<ugly::VertexArrays> m_triangles_21_va;

    /*! Triangle VBO */
    std::shared_ptr<ugly::VertexBuffer> m_triangle_bo;

    /*! Program */
    std::shared_ptr<ugly::Program> m_shader_program;

    /*! Program yellow */
    std::shared_ptr<ugly::Program> m_shader_program_yellow;

    /*! Wireframe flag */
    int m_render_mode{ 1 };

    /*! Render type. 0 = triangle, 1 = quad */
    int m_sample{ 0 };
};