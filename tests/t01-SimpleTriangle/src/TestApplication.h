#pragma once

#include "UglyEngine.h"
#include "SimpleTriangleTask.h"
#include "SimpleQuadTask.h"
#include "Simple2TrianglesTask.h"
#include "Simple2Triangles2VATask.h"
#include "Simple2Triangles2VA2ProgramTask.h"

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
     */
    void initialize() override;

    /**
     * @brief Shutdown application.
     */
    void shutdown() override;

    /**
     * @brief Update application.
     */
    void update() override;

    /**
     * @brief Render Gui.
     */
    void updateGui() override;

    /**
     * @brief Render application.
     */
    void render() override;

private:

    /*! Wireframe flag */
    int m_render_mode{ 1 };

    /*! Render type. 0 = triangle, 1 = quad, etc ...*/
    int m_sample{ 0 };

    std::shared_ptr<Task> m_current_task{ nullptr };

    std::shared_ptr<SimpleTriangleTask> m_simple_triangle_task{ nullptr };

    std::shared_ptr<SimpleQuadTask> m_simple_quad_task{ nullptr };

    std::shared_ptr<Simple2TrianglesTask> m_simple_2_triangles_task{ nullptr };

    std::shared_ptr<Simple2Triangles2VATask> m_simple_2_triangles_2va_task{ nullptr };

    std::shared_ptr<Simple2Triangles2VA2ProgramTask> m_simple_2_triangles_2va_2program_task{ nullptr };
};