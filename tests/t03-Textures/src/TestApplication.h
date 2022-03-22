#pragma once

#include "UglyEngine.h"
#include "TriangleTask.h"
#include "QuadTask.h"
#include "ColoredQuadTask.h"

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
   void initialize();

   /**
    * @brief Shutdown application.
    */
   void shutdown();

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

    int m_render_mode{ 1 };

    int m_sample{ 0 };

    std::shared_ptr<Task> m_current_task{ nullptr };

    std::shared_ptr<TriangleTask> m_triangle_task {nullptr};

    std::shared_ptr<QuadTask> m_quad_task{ nullptr };

    std::shared_ptr<ColoredQuadTask> m_colored_quad_task{ nullptr };

    /*! Triangle VAO */
    std::shared_ptr<ugly::VertexArrays> m_triangle_va;

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



};