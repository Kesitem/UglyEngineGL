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
     * @brief Destroy triangle data.
     */
    void destroyTriangle();

    /**
     * @brief Draw triangle.
     */
    void drawTriangle();

private:

    /*! Triangle VAO */
    ugly::gl::VertexArrays m_triangle_va;

    /*! Triangles VBO */
    ugly::gl::BufferObject m_triangle_bo;

    /*! Quad element buffer */
    ugly::gl::BufferObject m_quad_eb;

    /*! Program */
    ugly::gl::Program m_shader_program;

    /*! Wireframe flag */
    bool m_wireframe {false};

    /*! Render type. 0 = triangle, 1 = quad */
    int m_render_type {0};
};