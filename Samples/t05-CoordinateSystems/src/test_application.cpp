#include "test_application.h"


glm::vec3 g_cube_positions[] = 
{
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


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

    glGenBuffers(1, &m_vbo_quad);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_quad);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quad), vertices_quad, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 

    glGenBuffers(1, &m_ebo_quad);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_quad);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);

    glBindVertexArray(0);


    //////////
    // Create vertex array for cube
    //////////

    float vertices_cube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &m_va_cube);
    glBindVertexArray(m_va_cube);

    glGenBuffers(1, &m_vbo_cube);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 

    glBindVertexArray(0);


    //////////
    // Create textures
    //////////
    m_texture_container.create("data/textures/container.jpg");
    m_texture_face.create("data/textures/awesomeface.png");

    //////////
    // Create progam for triangle
    //////////
    m_program.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/base.vert")),
        ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/base.frag")));


    glUseProgram(m_program.getId());
    m_program.setUniform("u_texture0", 0);
    m_program.setUniform("u_texture1", 1);
}


void TestApplication::shutdown()
{
    glDeleteVertexArrays(1, &m_va_quad);
    glDeleteVertexArrays(1, &m_va_cube);
    glDeleteBuffers(1, &m_vbo_quad);
    glDeleteBuffers(1, &m_ebo_quad);
    glDeleteBuffers(1, &m_vbo_cube);
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        m_engine->quit();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    if(m_sample == 0)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glUseProgram(m_program.getId());
        m_program.setUniform("u_model", model);
        m_program.setUniform("u_view", view);
        m_program.setUniform("u_projection", projection);
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
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glUseProgram(m_program.getId());
        m_program.setUniform("u_model", model);
        m_program.setUniform("u_view", view);
        m_program.setUniform("u_projection", projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glBindVertexArray(m_va_cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 2)
    {


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glUseProgram(m_program.getId());
        m_program.setUniform("u_view", view);
        m_program.setUniform("u_projection", projection);
        glBindVertexArray(m_va_cube);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, g_cube_positions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_program.setUniform("u_model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 3)
    {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(m_fov), m_aspect_ratio, 0.1f, 100.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glUseProgram(m_program.getId());
        m_program.setUniform("u_view", view);
        m_program.setUniform("u_projection", projection);
        glBindVertexArray(m_va_cube);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, g_cube_positions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_program.setUniform("u_model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 4)
    {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(m_view_translation_x, m_view_translation_y, m_view_translation_z)); 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glUseProgram(m_program.getId());
        m_program.setUniform("u_view", view);
        m_program.setUniform("u_projection", projection);
        glBindVertexArray(m_va_cube);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, g_cube_positions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_program.setUniform("u_model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 5)
    {


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container.getId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face.getId());
        glUseProgram(m_program.getId());
        m_program.setUniform("u_view", view);
        m_program.setUniform("u_projection", projection);
        glBindVertexArray(m_va_cube);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, g_cube_positions[i]);
            if(i % 3 == 0)
            {
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(25.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            else
            {            
                float angle = 20.0f * i; 
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            m_program.setUniform("u_model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); 
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
}


void TestApplication::updateImgui()
{
    static std::vector<std::string> sample_list({ "Simple transformations", "Rotating cube", "Multiple cubes", "FoV and aspect", "View matrix translations", "Some cubes rotate" });    
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

        if(m_sample == 3)
        {
            ImGui::Begin("FoV and Aspect Ratio");
            {
                ImGui::SliderFloat("FoV", &m_fov, 0.0f, 180.0f);
                ImGui::SliderFloat("Aspect", &m_aspect_ratio, 0.1f, 5.0f);
            }
            ImGui::End();
        }

        if(m_sample == 4)
        {
            ImGui::Begin("View matrix translations");
            {
                ImGui::SliderFloat("View Translation X", &m_view_translation_x, -100.0f, 100.0f);
                ImGui::SliderFloat("View Translation Y", &m_view_translation_y, -100.0f, 100.0f);
                ImGui::SliderFloat("View Translation Z", &m_view_translation_z, -100.0f, 100.0f);
            }
            ImGui::End();
        }
    }
    ImGui::End();
}