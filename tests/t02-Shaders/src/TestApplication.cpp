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

    m_simple_triangle_task = std::make_shared<SimpleTriangleTask>();
    m_uniform_task = std::make_shared<UniformTask>();
    m_more_attributes_task = std::make_shared<MoreAttributesTask>();
    m_upside_down_task = std::make_shared<UpsideDownTask>();
    m_offset_task = std::make_shared<OffsetTask>();
    m_pos_as_color_task = std::make_shared<PosAsColorTask>();
}


void TestApplication::shutdown()
{
    if (m_simple_triangle_task.get() != nullptr)
    {
        m_simple_triangle_task->shutdown();
        m_simple_triangle_task.reset();
    }
    if (m_uniform_task.get() != nullptr)
    {
        m_uniform_task->shutdown();
        m_uniform_task.reset();
    }
    if (m_more_attributes_task.get() != nullptr)
    {
        m_more_attributes_task->shutdown();
        m_more_attributes_task.reset();
    }
    if (m_upside_down_task.get() != nullptr)
    {
        m_upside_down_task->shutdown();
        m_upside_down_task.reset();
    }
    if (m_offset_task.get() != nullptr)
    {
        m_offset_task->shutdown();
        m_offset_task.reset();
    }
    if (m_pos_as_color_task.get() != nullptr)
    {
        m_pos_as_color_task->shutdown();
        m_pos_as_color_task.reset();
    }
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();

    if(m_render_mode)
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::LINE);
    else
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::FILL);

    switch (m_sample)
    {
    case 0:
        if (m_current_task.get() != (Task*)m_simple_triangle_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_simple_triangle_task);
            m_simple_triangle_task->initialize();
            m_task_manager->pushTask(m_simple_triangle_task);
        }
        break;
    case 1:
        if (m_current_task.get() != (Task*)m_uniform_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_uniform_task);
            m_uniform_task->initialize();
            m_task_manager->pushTask(m_uniform_task);
        }
        break;
    case 2:
        if (m_current_task.get() != (Task*)m_more_attributes_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_more_attributes_task);
            m_more_attributes_task->initialize();
            m_task_manager->pushTask(m_more_attributes_task);
        }
        break;
    case 3:
        if (m_current_task.get() != (Task*)m_upside_down_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_upside_down_task);
            m_upside_down_task->initialize();
            m_task_manager->pushTask(m_upside_down_task);
        }
        break;
    case 4:
        if (m_current_task.get() != (Task*)m_offset_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_offset_task);
            m_offset_task->initialize();
            m_task_manager->pushTask(m_offset_task);
        }
        break;
    case 5:
        if (m_current_task.get() != (Task*)m_pos_as_color_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_pos_as_color_task);
            m_pos_as_color_task->initialize();
            m_task_manager->pushTask(m_pos_as_color_task);
        }
        break;
    }
}


void TestApplication::updateGui()
{
    static std::vector<std::string> sample_list({ "simple triangle", "uniform", "more attributes", "upside down", "offset", "position as color"});
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
