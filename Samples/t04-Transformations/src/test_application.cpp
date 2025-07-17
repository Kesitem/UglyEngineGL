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

    //////////
    // Create vertex array for quad
    //////////

    float vertices_quad[] = 
    {
        // positions         // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left 
    };

    unsigned int indices_quad[] = 
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &m_va_quad);
    glBindVertexArray(m_va_quad);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quad), vertices_quad, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);

    glBindVertexArray(0);

    //////////
    // Create textures
    //////////
    m_texture_container.create("data/textures/container.jpg");
    m_texture_face.create("data/textures/awesomeface.png");

    //////////
    // Create progam for triangle
    //////////
    m_program_quad.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/base.vert")),
        ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/base.frag")));


    glUseProgram(m_program_quad.getId());
    m_program_quad.setUniform("u_texture0", 0);
    m_program_quad.setUniform("u_texture1", 1);
}


void TestApplication::shutdown()
{
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        m_engine->quit();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(m_sample == 0)
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        glUseProgram(m_program_quad.getId());
        m_program_quad.setUniform("u_transform", trans);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 1)
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

        glUseProgram(m_program_quad.getId());
        m_program_quad.setUniform("u_transform", trans);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 2)
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        glUseProgram(m_program_quad.getId());
        m_program_quad.setUniform("u_transform", trans);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::scale(trans, glm::vec3(glm::sin((float)glfwGetTime())));

        glUseProgram(m_program_quad.getId());
        m_program_quad.setUniform("u_transform", trans);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
}


void TestApplication::updateImgui()
{
    static std::vector<std::string> sample_list({ "Rotating quad", "Rotate first", "Two containers"});    
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
    }
    ImGui::End();
}