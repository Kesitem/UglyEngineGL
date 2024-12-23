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
    // Create progam for triangle
    //////////

    m_program.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/basic.vert")),
        ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/basic.frag")));

    //////////
    // Create vertex array for simple triangle
    //////////

    float vertices_triangle[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    float tex_coords_triangles[] = 
    {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };

    glGenVertexArrays(1, &m_va_triangle);
    glBindVertexArray(m_va_triangle);

    GLuint vbo_pos;
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint vbo_tex_coord;
    glGenBuffers(1, &vbo_tex_coord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_coord);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords_triangles), tex_coords_triangles, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Unbind vertex array
    glBindVertexArray(0);

    //////////
    // Texture loading (by hand)
    //////////

    // Load image data
    int width, height, nb_channels;
    unsigned char *data = stbi_load("data/textures/wall.jpg", &width, &height, &nb_channels, 0); 
    
    // Create texture object
    glGenTextures(1, &m_texture_wall);  

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, m_texture_wall); 

    // Set texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

   // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Free texture data
    stbi_image_free(data);

 


    //////////
    // Create vertex array for quad
    //////////

    float vertices_quad[] = 
    {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quad), indices_quad, GL_STATIC_DRAW);

    glBindVertexArray(0);

    m_texture_container = std::make_unique<ugly::Texture>("data/textures/container.jpg");
    m_texture_face = std::make_unique<ugly::Texture>("data/textures/awesomeface.png");

    //////////
    // Create progam for triangle
    //////////

    m_program_quad.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/simple.vert")),
        ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/simple.frag")));

    m_program_quad_color.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/simple.vert")),
        ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/simple_color.frag")));

    m_program_quad_multi.create(ugly::Shader(GL_VERTEX_SHADER, std::filesystem::path("data/shaders/simple.vert")),
        ugly::Shader(GL_FRAGMENT_SHADER, std::filesystem::path("data/shaders/simple_multi.frag")));
    glUseProgram(m_program_quad_multi.get_id());
    m_program_quad_multi.setUniform("texture0", 0);
    m_program_quad_multi.setUniform("texture1", 1);


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
        glUseProgram(m_program.get_id());
        glBindTexture(GL_TEXTURE_2D, m_texture_wall);
        glBindVertexArray(m_va_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }
    else if(m_sample == 1)
    {
        glUseProgram(m_program_quad.get_id());
        glBindTexture(GL_TEXTURE_2D, m_texture_container->get_id());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 2)
    {
        glUseProgram(m_program_quad_color.get_id());
        glBindTexture(GL_TEXTURE_2D, m_texture_container->get_id());
        glBindVertexArray(m_va_quad);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glBindVertexArray(0);
    }
    else if(m_sample == 3)
    {
        glUseProgram(m_program_quad_multi.get_id());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_container->get_id());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_face->get_id());
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
    static std::vector<std::string> sample_list({ "Texture triangle", "Textured quad", "Texture quad with color", "Multi texturing" });    
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