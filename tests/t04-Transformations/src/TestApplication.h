#pragma once

#include "UglyEngine.h"
#include "SmileQuadTask.h"
#include "RotatingSmileQuadTask.h"
#include "TwoSmileQuadTask.h"

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

    std::shared_ptr<SmileQuadTask> m_smile_quad_task{ nullptr };

    std::shared_ptr<RotatingSmileQuadTask> m_rotating_smile_quad_task{ nullptr };

    std::shared_ptr<TwoSmileQuadTask> m_two_smile_quad_task{ nullptr };
};