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

    std::shared_ptr<ugly::InputManager> m_input_manager;

    std::shared_ptr<ugly::DisplayManager> m_display_manager;

    std::shared_ptr<ugly::VertexArrays> m_triangle_va;

    std::shared_ptr<ugly::VertexArrays> m_color_triangle_va;

    std::shared_ptr<ugly::Program> m_shader_program_red;

    std::shared_ptr<ugly::Program> m_shader_program_uniform;

    std::shared_ptr<ugly::Program> m_shader_program_color;

    std::shared_ptr<ugly::Program> m_shader_program_color_inverted;

    std::shared_ptr<ugly::Program> m_shader_program_color_offset;

    std::shared_ptr<ugly::Program> m_shader_program_color_pos;

    bool m_wireframe {false};

    /*! Render type. 0 = triangle, 1 = quad */
    int m_render_type {0};
};