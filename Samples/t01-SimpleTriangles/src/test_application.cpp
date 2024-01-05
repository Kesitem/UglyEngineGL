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

    const char *vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    // Create program
    m_program.create(ugly::Shader(ugly::ShaderType::VERTEX, vertex_shader_source), 
                     ugly::Shader(ugly::ShaderType::FRAGMENT, fragment_shader_source));

    float vertices_simple_triangle[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    m_va_simple_triangle.bind();

    // Create vertex buffer
    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices_simple_triangle), vertices_simple_triangle);
    bo->setLayout({ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)});

    // Set vertex pointer
    m_va_simple_triangle.addVertexBuffer(bo);

    // Unbind vertex array
    m_va_simple_triangle.unbind();

    float vertices_quad[] = 
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices_quad   [] = 
    {  
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    m_va_quad.bind();

    bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices_quad), vertices_quad);
    bo->setLayout({ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)});

    m_va_quad.addVertexBuffer(bo);

    auto ib = std::make_shared<ugly::IndexBuffer>((uint32_t)sizeof(indices_quad), indices_quad);

    m_va_quad.setIndexBuffer(ib);

    m_va_quad.unbind();
}


void TestApplication::shutdown()
{
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        m_engine->quit();

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
        m_va_simple_triangle.bind();
        m_display_manager->drawArrays(0, 3);
        m_va_simple_triangle.unbind();
    } 
    else if (m_sample == 1)
    {
        m_program.use();
        m_va_quad.bind();
        m_display_manager->drawElements(6);
        m_va_quad.unbind();
    }
}


void TestApplication::updateImgui()
{
    static std::vector<std::string> sample_list({ "simple triangle", "simple quad", "2 triangles", "2 triangles 2 VA", "2 triangles 2 VA 2 Programs"});
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