#include "test_application.h"


TestApplication::TestApplication()
{
}


TestApplication::~TestApplication()
{
}


void TestApplication::initialize()
{
    m_engine = ugly::Engine::get_instance();
    m_input_manager = m_engine->get_input_manager();

    m_input_manager->createButton("quit");
    m_input_manager->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");

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

    const char *vertex_shader_source_uniform = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform vec4 ourColor;"
        "out vec4 vertexColor;"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   vertexColor = ourColor;"
        "}\0";

    const char *vertex_shader_source_more_attribute = "#version 330 core\n"
        "layout (location = 0) in vec3 a_pos;\n"
        "layout (location = 1) in vec3 a_color;"
        "out vec3 vertex_color;"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
        "   vertex_color = a_color;"
        "}\0";

    const char *fragment_shader_source_more_attribute = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 vertex_color;"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(vertex_color, 1.0);\n"
        "}\0";

    // Simple triangle VA
    float vertices_simple_triangle[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // Create va
    glGenVertexArrays(1, &m_va_triangle);
    glBindVertexArray(m_va_triangle);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_simple_triangle), vertices_simple_triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glBindVertexArray(0);


    // More attributes VA . 
   float vertices_more_attributes[] = 
   {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    glGenVertexArrays(1, &m_va_more_attributes);
    glBindVertexArray(m_va_more_attributes);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_more_attributes), vertices_more_attributes, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Programs
    m_program.create(ugly::Shader(GL_VERTEX_SHADER, vertex_shader_source), 
                     ugly::Shader(GL_FRAGMENT_SHADER, fragment_shader_source));


    m_program_uniform.create(ugly::Shader(GL_VERTEX_SHADER, vertex_shader_source_uniform), 
                     ugly::Shader(GL_FRAGMENT_SHADER, fragment_shader_source));

    m_program_attributes.create(ugly::Shader(GL_VERTEX_SHADER, vertex_shader_source_more_attribute), 
                                     ugly::Shader(GL_FRAGMENT_SHADER, fragment_shader_source_more_attribute));

    m_program_inverted.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/inverted.vert")),
                              ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/inverted.frag")));

    m_program_offset.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/offset.vert")),
                            ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/offset.frag")));

    m_program_posascolor.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/posascolor.vert")),
                            ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/posascolor.frag")));
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
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(m_sample == 0)
    {
        glUseProgram(m_program.get_id());
        glBindVertexArray(m_va_triangle);        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
    }
    else if(m_sample == 1)
    {
        glUseProgram(m_program.get_id());
        m_program_uniform.setUniform("ourColor", glm::vec4(0.0f, green_value, 0.0f, 1.0f));
        glBindVertexArray(m_va_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
    }
    else if(m_sample == 2)
    {
        glUseProgram(m_program_attributes.get_id());
        glBindVertexArray(m_va_more_attributes);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
    }
    else if(m_sample == 3)
    {
        glUseProgram(m_program_inverted.get_id());
        glBindVertexArray(m_va_more_attributes);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
    }
    else if(m_sample == 4)
    {
        glUseProgram(m_program_offset.get_id());
        m_program_offset.setUniform("u_offset", 0.25f);
        glBindVertexArray(m_va_more_attributes);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
    }
    else if(m_sample == 5)
    {
        glUseProgram(m_program_posascolor.get_id());
        glBindVertexArray(m_va_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);
    }
}


void TestApplication::updateImgui()
{
    static std::vector<std::string> sample_list({ "simple shader", "uniform", "more attributes", "inverted", "uniform offset", "position as color"});
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