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
    m_input_manager->createButton("wireframe");
    m_input_manager->bindKeyToButton(GLFW_KEY_W, "wireframe");
    m_input_manager->createButton("render-type");
    m_input_manager->bindKeyToButton(GLFW_KEY_R, "render-type");

    m_simple_triangle_task = std::make_shared<SimpleTriangleTask>();
    m_simple_quad_task = std::make_shared<SimpleQuadTask>();
    m_simple_2_triangles_task = std::make_shared<Simple2TrianglesTask>();
    m_simple_2_triangles_2va_task = std::make_shared<Simple2Triangles2VATask>();
    m_simple_2_triangles_2va_2program_task = std::make_shared<Simple2Triangles2VA2ProgramTask>();
}


void TestApplication::shutdown()
{
    if (m_simple_triangle_task.get() != nullptr)
    {
        m_simple_triangle_task->shutdown();
        m_simple_triangle_task.reset();
    }
    if (m_simple_quad_task.get() != nullptr)
    {
        m_simple_quad_task->shutdown();
        m_simple_quad_task.reset();
    }
    if (m_simple_2_triangles_task.get() != nullptr)
    {
        m_simple_2_triangles_task->shutdown();
        m_simple_2_triangles_task.reset();
    }
    if (m_simple_2_triangles_2va_task.get() != nullptr)
    {
        m_simple_2_triangles_2va_task->shutdown();
        m_simple_2_triangles_2va_task.reset();
    }
    if (m_simple_2_triangles_2va_2program_task.get() != nullptr)
    {
        m_simple_2_triangles_2va_2program_task->shutdown();
        m_simple_2_triangles_2va_2program_task.reset();
    }
}


void TestApplication::update()
{
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();

    switch (m_render_mode)
    {
    case 0:
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::LINE);
        break;
    case 1:
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::FILL);
        break;
    }

    switch (m_sample)
    {
    case 0:
    {
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
    }
    case 1:
    {
        if (m_current_task.get() != (Task*)m_simple_quad_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_simple_quad_task);
            m_simple_quad_task->initialize();
            m_task_manager->pushTask(m_simple_quad_task);
        }
        break;
    }
    case 2:
    {
        if (m_current_task.get() != (Task*)m_simple_2_triangles_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_simple_2_triangles_task);
            m_simple_2_triangles_task->initialize();
            m_task_manager->pushTask(m_simple_2_triangles_task);
        }
        break;
    }
    case 3:
    {
        if (m_current_task.get() != (Task*)m_simple_2_triangles_2va_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_simple_2_triangles_2va_task);
            m_simple_2_triangles_2va_task->initialize();
            m_task_manager->pushTask(m_simple_2_triangles_2va_task);
        }
        break;
    }
    case 4:
    {
        if (m_current_task.get() != (Task*)m_simple_2_triangles_2va_2program_task.get())
        {
            if (m_current_task.get() != nullptr)
            {
                m_task_manager->popTask(m_current_task);
                m_current_task->shutdown();
            }

            m_current_task = std::static_pointer_cast<Task>(m_simple_2_triangles_2va_2program_task);
            m_simple_2_triangles_2va_2program_task->initialize();
            m_task_manager->pushTask(m_simple_2_triangles_2va_2program_task);
        }
        break;
    }
    }
 
}

void TestApplication::render()
{
    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();
}

void TestApplication::updateGui()
{
    static std::vector<std::string> sample_list({ "simple triangle", "simple quad", "2 triangles", "2 triangles 2 VA", "2 triangles 2 VA 2 Programs"});
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
