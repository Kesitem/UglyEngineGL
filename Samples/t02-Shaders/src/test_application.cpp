#include "test_application.h"


TestApplication::TestApplication()
{
}


TestApplication::~TestApplication()
{
}


void TestApplication::initialize()
{
    m_engine = ugly::Engine::getInstance();
    m_input_manager = m_engine->getInputManager();
    m_display_manager = m_engine->getDisplayManager();

    m_input_manager->createButton("quit");
    m_input_manager->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");

    float vertices_simple_triangle[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    m_va_triangle.bind();

    // Create vertex buffer
    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices_simple_triangle), vertices_simple_triangle);
    bo->setLayout({ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)});

    // Set vertex pointer
    m_va_triangle.addVertexBuffer(bo);

    // Unbind vertex array
    m_va_triangle.unbind();

    const char *vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec4 vertexColor;"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
        "}\0";

    const char *fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 vertexColor;"
        "void main()\n"
        "{\n"
        "   FragColor = vertexColor;\n"
        "}\0";

    // Create program
    m_program.create(ugly::Shader(ugly::ShaderType::VERTEX, vertex_shader_source), 
                     ugly::Shader(ugly::ShaderType::FRAGMENT, fragment_shader_source));

    const char *vertex_shader_source_uniform = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform vec4 ourColor;"
        "out vec4 vertexColor;"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   vertexColor = ourColor;"
        "}\0";

    m_program_uniform.create(ugly::Shader(ugly::ShaderType::VERTEX, vertex_shader_source_uniform), 
                     ugly::Shader(ugly::ShaderType::FRAGMENT, fragment_shader_source));
}


void TestApplication::shutdown()
{
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        m_engine->quit();

    float time_value = glfwGetTime();
    float green_value = (sin(time_value) / 2.0f) + 0.5f;

    switch (m_render_mode)
    {
    case 0:
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygonMode::LINE);
        break;
    case 1:
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygonMode::FILL);
        break;
    }

    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();

    if(m_sample == 0)
    {
        m_program.use();
        m_va_triangle.bind();
        m_display_manager->drawArrays(0, 3);
        m_va_triangle.unbind();
    }
    else if(m_sample == 1)
    {
        m_program_uniform.use();
        m_program_uniform.setUniform("ourColor", glm::vec4(0.0f, green_value, 0.0f, 1.0f));
        m_va_triangle.bind();
        m_display_manager->drawArrays(0, 3);
        m_va_triangle.unbind();
    }
}


void TestApplication::updateImgui()
{
    static std::vector<std::string> sample_list({ "simple shader", "uniform"});
    static std::vector<std::string> render_mode_list({ "line", "fill" });
    ImGui::Begin("Options");
    {
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
    }
    ImGui::End();
}