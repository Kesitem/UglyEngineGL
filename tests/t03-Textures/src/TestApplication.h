#pragma once

#include "UglyEngine.h"
#include "TriangleTask.h"
#include "QuadTask.h"
#include "ColoredQuadTask.h"
#include "SmileQuadTask.h"
#include "InvertedSmileQuadTask.h"
#include "WrappingSmileQuadTask.h"
#include "ZoomSmileQuadTask.h"
#include "AdjustableSmileQuadTask.h"

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
     * @brief Change the current task.
     *
     * @param _task New task
     */
    void changeTask(std::shared_ptr<Task> _task);

private:

    int m_render_mode{ 1 };

    int m_sample{ 0 };

    std::shared_ptr<Task> m_current_task{ nullptr };

    std::shared_ptr<TriangleTask> m_triangle_task {nullptr};

    std::shared_ptr<QuadTask> m_quad_task{ nullptr };

    std::shared_ptr<ColoredQuadTask> m_colored_quad_task{ nullptr };

    std::shared_ptr<SmileQuadTask> m_smile_quad_task{ nullptr };

    std::shared_ptr<InvertedSmileQuadTask> m_inverted_smile_quad_task{ nullptr };

    std::shared_ptr<WrappingSmileQuadTask> m_wrapping_smile_quad_task{ nullptr };

    std::shared_ptr<ZoomSmileQuadTask> m_zoom_smile_quad_task{ nullptr };

    std::shared_ptr<AdjustableSmileQuadTask> m_adjustable_smile_quad_task{ nullptr };
};