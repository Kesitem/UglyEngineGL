#include "TestApplication.h"
#include "config.h"

TestApplication::TestApplication() : ugly::Application()
{
    this->m_title = ugly::test::APPLICATION_NAME;
}


void TestApplication::initialize()
{
    m_input_manager->createButton("quit");
    m_input_manager->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");

    m_triangle_task = std::make_shared<TriangleTask>();
    m_quad_task = std::make_shared<QuadTask>();
    m_colored_quad_task = std::make_shared<ColoredQuadTask>();
    m_smile_quad_task = std::make_shared<SmileQuadTask>();
    m_inverted_smile_quad_task = std::make_shared<InvertedSmileQuadTask>();
    m_wrapping_smile_quad_task = std::make_shared<WrappingSmileQuadTask>();
    m_zoom_smile_quad_task = std::make_shared<ZoomSmileQuadTask>();
    m_adjustable_smile_quad_task = std::make_shared<AdjustableSmileQuadTask>();
}


void TestApplication::shutdown()
{
    m_triangle_task.reset();
    m_quad_task.reset();
    m_colored_quad_task.reset();
    m_smile_quad_task.reset();
    m_inverted_smile_quad_task.reset();
    m_wrapping_smile_quad_task.reset();
    m_zoom_smile_quad_task.reset();
    m_adjustable_smile_quad_task.reset();
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();

    if (m_render_mode == 0)
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::LINE);
    else
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::FILL);

    switch (m_sample)
    {
    case 0:
        changeTask(std::static_pointer_cast<Task>(m_triangle_task));
        break;
    case 1:
        changeTask(std::static_pointer_cast<Task>(m_quad_task));
        break;
    case 2:
        changeTask(std::static_pointer_cast<Task>(m_colored_quad_task));
        break;
    case 3:
        changeTask(std::static_pointer_cast<Task>(m_smile_quad_task));
        break;
    case 4:
        changeTask(std::static_pointer_cast<Task>(m_inverted_smile_quad_task));
        break;
    case 5:
        changeTask(std::static_pointer_cast<Task>(m_wrapping_smile_quad_task));
        break;
    case 6:
        changeTask(std::static_pointer_cast<Task>(m_zoom_smile_quad_task));
        break;
    case 7:
        changeTask(std::static_pointer_cast<Task>(m_adjustable_smile_quad_task));
        break;
    }

    /*if (m_input_manager->getButtonAction("wrap-filter") == ugly::InputAction::released)
    {
        m_wrap_filter++;
        if (m_wrap_filter > 3)
            m_wrap_filter = 0;
    }*/

}


void TestApplication::updateGui()
{
    static std::vector<std::string> sample_list({ "triangle", "quad", "colored quad", "happy quad", "inverted happy quad", "wrapping happy quad", "zoom happy quad", "adjustable happy quad"});
    ImGui::Begin("Options");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    if (ImGui::BeginListBox("Sample"))
    {
        for (int n = 0; n < sample_list.size(); n++)
        {
            const bool is_selected = (m_sample == n);
            if (ImGui::Selectable(sample_list[n].c_str(), is_selected))
                m_sample = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }

    static std::vector<std::string> render_mode_list({ "line", "fill" });
    if (ImGui::BeginListBox("Render mode"))
    {
        for (int n = 0; n < render_mode_list.size(); n++)
        {
            const bool is_selected = (m_render_mode == n);
            if (ImGui::Selectable(render_mode_list[n].c_str(), is_selected))
                m_render_mode = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
    ImGui::End();
}


void TestApplication::render()
{
    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();
}

void TestApplication::changeTask(std::shared_ptr<Task> _task)
{
    if (m_current_task.get() != _task.get())
    {
        if (m_current_task.get() != nullptr)
        {
            m_task_manager->popTask(m_current_task);
            m_current_task->shutdown();
        }

        m_current_task = _task;
        _task->initialize();
        m_task_manager->pushTask(_task);
    }
}
