#pragma once

#include "UglyEngine.h"
#include "SimpleTriangleTask.h"
#include "UniformTask.h"
#include "MoreAttributesTask.h"
#include "UpsideDownTask.h"
#include "OffsetTask.h"
#include "PosAsColorTask.h"

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
    int m_render_mode{ 0 };

    /*! Render type. 0 = triangle, 1 = quad, etc ...*/
    int m_sample{ 0 };

    std::shared_ptr<Task> m_current_task{ nullptr };

    std::shared_ptr<SimpleTriangleTask> m_simple_triangle_task{ nullptr };

    std::shared_ptr<UniformTask> m_uniform_task{ nullptr };

    std::shared_ptr<MoreAttributesTask> m_more_attributes_task{ nullptr };

    std::shared_ptr<UpsideDownTask> m_upside_down_task{ nullptr };

    std::shared_ptr<OffsetTask> m_offset_task{ nullptr };

    std::shared_ptr<PosAsColorTask> m_pos_as_color_task{ nullptr };
};