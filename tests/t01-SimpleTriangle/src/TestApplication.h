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

    /**
     * @brief Create quad data.
     */
    void createQuad();

    /**
     * @brief Destroy quad data.
     */
    void destroyQuad();

    /**
     * @brief Draw quad.
     */
    void drawQuad();

    /**
     * @brief Create triangles data.
     */
    void createTriangles();

    /**
     * @brief Destroy triangles data.
     */
    void destroyTriangles();

    /**
     * @brief Draw triangles.
     */
    void drawTriangles();

        /**
     * @brief Create triangles data.
     */
    void createTriangles2VA();

    /**
     * @brief Destroy triangles data.
     */
    void destroyTriangles2VA();

    /**
     * @brief Draw triangles.
     */
    void drawTriangles2VA();

    /**
     * @brief Draw triangles.
     */
    void drawTriangles2VA2Programs();

private:

    /*! Triangle VAO */
    ugly::gl::VertexArrays m_triangle_va;

    /*! Triangle VAO */
    ugly::gl::VertexArrays m_triangles_va;

    /*! Quad VAO */
    ugly::gl::VertexArrays m_quad_va;

    ugly::gl::VertexArrays m_triangles_20_va;

    ugly::gl::VertexArrays m_triangles_21_va;
    /*! Triangle VBO */
    ugly::gl::BufferObject m_triangle_bo;

    /*! Triangles VBO */
    ugly::gl::BufferObject m_triangles_bo;

    /*! Quad element buffer */
    ugly::gl::BufferObject m_quad_eb;

    /*! Quad VBO */
    ugly::gl::BufferObject m_quad_bo;

    ugly::gl::BufferObject m_triangles_20_bo;
    ugly::gl::BufferObject m_triangles_21_bo;

    /*! Program */
    ugly::gl::Program m_shader_program;

    /*! Program yellow */
    ugly::gl::Program m_shader_program_yellow;

    /*! Wireframe flag */
    bool m_wireframe {false};

    /*! Render type. 0 = triangle, 1 = quad */
    int m_render_type {0};
};