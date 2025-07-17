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
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fragment_shader_source_orange = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    const char *fragment_shader_source_yellow = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\0";

    // Create program
    m_program_orange.create(ugly::Shader(GL_VERTEX_SHADER, vertex_shader_source), 
                     ugly::Shader(GL_FRAGMENT_SHADER, fragment_shader_source_orange));
    m_program_yellow.create(ugly::Shader(GL_VERTEX_SHADER, vertex_shader_source), 
                     ugly::Shader(GL_FRAGMENT_SHADER, fragment_shader_source_yellow));

    // Simple Triangle
    {
        float vertices_simple_triangle[] = 
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        // Create va
        glGenVertexArrays(1, &m_va_triangle);
        glBindVertexArray(m_va_triangle);

        // Create vbo
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_simple_triangle), vertices_simple_triangle, GL_STATIC_DRAW);

        // Set attribs
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        // Unbind vertex array
        glBindVertexArray(m_va_triangle);

    }

    // Sumple quad
    {
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

        // Create va
        glGenVertexArrays(1, &m_va_quad);
        glBindVertexArray(m_va_quad);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quad), vertices_quad, GL_STATIC_DRAW);

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        glBindVertexArray(0);
    }

    // Two triangles one vertex array
    {
        float vertices_double_triangle[] =
        {
            -0.75f, -0.5f, 0.0f,
            -0.25f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            0.25f, -0.5f, 0.0f,
            0.75f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
        };

        glGenVertexArrays(1, &m_va_double_triangle);
        glBindVertexArray(m_va_double_triangle);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_double_triangle), vertices_double_triangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        // Unbind vertex array
        glBindVertexArray(0);
    }

    // Two triangles two va
    {
        float vertices_triangle_0[] =
        {
            -0.75f, -0.5f, 0.0f,
            -0.25f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        // Bind vertex array
        glGenVertexArrays(1, &m_va_triangle_0);
        glBindVertexArray(m_va_triangle_0);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle_0), vertices_triangle_0, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        // Unbind vertex array
        glBindVertexArray(0);

        float vertices_triangle_1[] =
        {
            0.25f, -0.5f, 0.0f,
            0.75f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f
        };

        // Bind vertex array
        glGenVertexArrays(1, &m_va_triangle_1);
        glBindVertexArray(m_va_triangle_1);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle_1), vertices_triangle_1, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        // Unbind vertex array
        glBindVertexArray(0);
    }
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
        glUseProgram(m_program_orange.getId());
        glBindVertexArray(m_va_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    } 
    else if (m_sample == 1)
    {
        glUseProgram(m_program_orange.getId());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    else if (m_sample == 2)
    {
        glUseProgram(m_program_orange.getId());
        glBindVertexArray(m_va_double_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    else if (m_sample == 3)
    {
        glUseProgram(m_program_orange.getId());
        glBindVertexArray(m_va_triangle_0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glBindVertexArray(m_va_triangle_1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
    else if (m_sample == 4)
    {
        glUseProgram(m_program_orange.getId());
        glBindVertexArray(m_va_triangle_0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(m_program_yellow.getId());
        glBindVertexArray(m_va_triangle_1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
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