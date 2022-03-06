#include "TestApplication.h"
#include "config.h"


TestApplication::TestApplication()
{
    this->m_name = ugly::test::APPLICATION_NAME;
}


bool TestApplication::initialize()
{
    m_input_manager = ugly::Engine::getInstance()->getInputManager();
    m_display_manager = ugly::Engine::getInstance()->getDisplayManager();

    m_input_manager->createButton("quit");
    m_input_manager->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");
    m_input_manager->createButton("wireframe");
    m_input_manager->bindKeyToButton(GLFW_KEY_W, "wireframe");
    m_input_manager->createButton("render-type");
    m_input_manager->bindKeyToButton(GLFW_KEY_R, "render-type");

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // Create and bind vertex array
    m_triangle_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto triangle_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    triangle_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)}));
    // Set vertex pointer
    m_triangle_va->addVertexBuffer(triangle_bo);

    // Unbind vertex array
    m_triangle_va->unbind();

    float color_vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    m_color_triangle_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto color_triangle_bo = std::make_shared<ugly::VertexBuffer>(sizeof(color_vertices), color_vertices);
    color_triangle_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
            ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false),
            ugly::BufferElement("a_color", ugly::BufferDataType::FLOAT3, false)}));
    // Set vertex pointer
    m_color_triangle_va->addVertexBuffer(color_triangle_bo);

    // Create program
    m_shader_program_red = std::make_shared<ugly::Program>("./data/simple_red.vert", "./data/simple_red.frag");
    m_shader_program_uniform = std::make_shared<ugly::Program>("./data/simple_uniform.vert", "./data/simple_uniform.frag");
    m_shader_program_color = std::make_shared<ugly::Program>("./data/simple_color.vert", "./data/simple_color.frag");
    m_shader_program_color_inverted = std::make_shared<ugly::Program>("./data/simple_color_inverted.vert", "./data/simple_color.frag");
    m_shader_program_color_offset = std::make_shared<ugly::Program>("./data/simple_color_offset.vert", "./data/simple_color.frag");
    m_shader_program_color_pos = std::make_shared<ugly::Program>("./data/simple_color_pos.vert", "./data/simple_color.frag");
    return true;
}


void TestApplication::shutdown()
{
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();
    if(m_input_manager->getButtonAction("wireframe") == ugly::InputAction::released)
        m_wireframe = !m_wireframe;
    if (ugly::Engine::getInstance()->getInputManager()->getButtonAction("render-type") == ugly::InputAction::released)
    {
        m_render_type++;
        if (m_render_type > 5)
            m_render_type = 0;
    }
        
    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();

    if(m_wireframe)
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::LINE);
    else
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::FILL);

    // Update timer
    float time_value = (float)glfwGetTime();
    float green_value = (sin(time_value) / 2.0f) + 0.5f;

    // Draw simple red triangle
    switch (m_render_type)
    {
    case 0:
        m_shader_program_red->use();
        m_triangle_va->bind();
        m_display_manager->drawArrays(3);
        m_triangle_va->unbind();
        break;
    case 1:
        m_shader_program_uniform->use();
        m_shader_program_uniform->setUniform("ourColor", glm::vec4(0.0f, green_value, 0.0f, 1.0f));
        m_triangle_va->bind();
        m_display_manager->drawArrays(3);
        m_triangle_va->unbind();
        break;
    case 2:
        m_shader_program_color->use();
        m_color_triangle_va->bind();
        m_display_manager->drawArrays(3);
        m_color_triangle_va->unbind();
        break;
    case 3:
        m_shader_program_color_inverted->use();
        m_color_triangle_va->bind();
        m_display_manager->drawArrays(3);
        m_color_triangle_va->unbind();
        break;
    case 4:
        m_shader_program_color_offset->use();
        m_shader_program_color_offset->setUniform("u_offset", 0.5f);
        m_color_triangle_va->bind();
        m_display_manager->drawArrays(3);
        m_color_triangle_va->unbind();
        break;
    case 5:
        m_shader_program_color_pos->use();
        m_color_triangle_va->bind();
        m_display_manager->drawArrays(3);
        m_color_triangle_va->unbind();
        break;
    }
}

