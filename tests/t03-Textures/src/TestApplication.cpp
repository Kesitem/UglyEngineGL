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
    m_input_manager->createButton("wrap-filter");
    m_input_manager->bindKeyToButton(GLFW_KEY_Z, "wrap-filter");

    createTriangle();
    createQuad();

    return true;
}


void TestApplication::shutdown()
{
    m_texture.reset();
    m_shader_program.reset();
    m_triangle_va.reset();
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();
    if(m_input_manager->getButtonAction("wireframe") == ugly::InputAction::released)
        m_wireframe = !m_wireframe;
    if (m_input_manager->getButtonAction("render-type") == ugly::InputAction::released)
    {
        m_render_type++;
        if (m_render_type > 2)
            m_render_type = 0;
    }
    if (m_input_manager->getButtonAction("wrap-filter") == ugly::InputAction::released)
    {
        m_wrap_filter++;
        if (m_wrap_filter > 3)
            m_wrap_filter = 0;
    }

    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();

    if(m_wireframe)
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::LINE);
    else
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::FILL);

    switch (m_render_type)
    {
    case 0:
        drawTriangle();
        break;
    case 1:
        drawQuad();
        break;
    case 2:
        drawQuadReverse();
        break;
    }
}


void TestApplication::createTriangle()
{
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    float tex_coords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };

    // Create and bind vertex array
    m_triangle_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto triangle_vertices_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    triangle_vertices_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
            ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)}));

    // Set vertex pointer
    m_triangle_va->addVertexBuffer(triangle_vertices_bo);

    auto triangle_tex_coords_bo = std::make_shared<ugly::VertexBuffer>(sizeof(tex_coords), tex_coords);
    triangle_tex_coords_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_texcoord", ugly::BufferDataType::FLOAT2, false)}));

    m_triangle_va->addVertexBuffer(triangle_tex_coords_bo);
   
    // Unbind vertex array
    m_triangle_va->unbind();

    // Create program
    m_shader_program = std::make_shared<ugly::Program>("./data/shaders/simple.vert", "./data/shaders/simple.frag");

    // Create texture
    m_texture = std::make_shared<ugly::Texture>("./data/textures/wall.jpg");
}



void TestApplication::drawTriangle()
{
    m_shader_program->use();
    m_triangle_va->bind();
    m_texture->bind();
    m_display_manager->drawArrays(3);
    m_triangle_va->unbind();
}


void TestApplication::createQuad()
{
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
    };

    uint32_t indices[] =
    {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create and bind vertex array
    m_quad_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto quad_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    quad_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false),
        ugly::BufferElement("a_color", ugly::BufferDataType::FLOAT3, false),
        ugly::BufferElement("a_texcoord", ugly::BufferDataType::FLOAT2, false)}));

    // Set vertex pointer
    m_quad_va->addVertexBuffer(quad_bo);

    // Create element buffer
    auto quad_eb = std::make_shared<ugly::IndexBuffer>(sizeof(indices), indices);
    m_quad_va->setIndexBuffer(quad_eb);

    // Unbind vertex array
    m_quad_va->unbind();

    m_quad_shader_program = std::make_shared<ugly::Program>("./data/shaders/quad.vert", "./data/shaders/quad.frag");
    m_quad_reverse_shader_program = std::make_shared<ugly::Program>("./data/shaders/quad.vert", "./data/shaders/quad_reverse.frag");
    // Create texture
    m_quad_texture = std::make_shared<ugly::Texture>("./data/textures/container.jpg");
    m_face_texture = std::make_shared<ugly::Texture>("./data/textures/awesomeface.png");
}


void TestApplication::drawQuad()
{
    m_quad_va->bind();
    m_quad_texture->bind(0);
    m_face_texture->bind(1);
    m_quad_shader_program->use();
    m_quad_shader_program->setUniform("texture0", 0);
    m_quad_shader_program->setUniform("texture1", 1);
    m_display_manager->drawElements(6);
    m_quad_va->unbind();
}


void TestApplication::drawQuadReverse()
{
    m_quad_va->bind();
    m_quad_texture->bind(0);
    m_face_texture->bind(1);
    m_quad_reverse_shader_program->use();
    m_quad_shader_program->setUniform("texture0", 0);
    m_quad_shader_program->setUniform("texture1", 1);
    m_display_manager->drawElements(6);
    m_quad_va->unbind();
}
