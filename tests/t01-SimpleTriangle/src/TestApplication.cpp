#include "TestApplication.h"
#include "config.h"

/** Vertex shader source **/
const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

/** Fragment shader source **/
const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

/** Fragment shader source **/
const char *fragment_shader_source_yellow = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";


/**
 * @brief Constructor.
 */
TestApplication::TestApplication()
{
    this->m_name = ugly::test::APPLICATION_NAME;
}


/**
 * \brief Initialize application.
 * 
 * \return False if error
 */
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

    createTriangle();
    createQuad();
    createTriangles();
    createTriangles2VA();

    // Create vertex shader
    auto vertex_shader = std::make_shared<ugly::Shader>(ugly::ShaderType::VERTEX, vertex_shader_source);

    // Create fragment shader
    auto fragment_shader = std::make_shared<ugly::Shader>(ugly::ShaderType::FRAGMENT, fragment_shader_source);

    // Create fragment shader yellow
    auto fragment_shader_yellow = std::make_shared< ugly::Shader>(ugly::ShaderType::FRAGMENT, fragment_shader_source_yellow);

    // Create program
    m_shader_program = std::make_shared<ugly::Program>(vertex_shader, fragment_shader);
 
    // Create yellow
    m_shader_program_yellow = std::make_shared<ugly::Program>(vertex_shader, fragment_shader_yellow);

    return true;
}


/**
 * \brief Shutdown application.
 */
void TestApplication::shutdown()
{
}


/**
 * @brief Update application.
 */
void TestApplication::update()
{
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("wireframe") == ugly::InputAction::released)
        m_wireframe = !m_wireframe;
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("render-type") == ugly::InputAction::released)
    {
        m_render_type++;
        if(m_render_type > 4)
            m_render_type = 0;
    }

        
    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();

    if (m_wireframe)
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::LINE);
    else
        m_display_manager->setPolygonMode(ugly::DisplayManager::PolygoneMode::FILL);


    switch(m_render_type)
    {
        case 0:
        {
            drawTriangle();
            break;
        }
        case 1:
        {
            drawQuad();
            break;
        }
        case 2:
        {
            drawTriangles();
            break;
        }
        case 3:
        {
            drawTriangles2VA();
            break;
        }
        case 4:
        {
            drawTriangles2VA2Programs();
            break;
        }
    }
}


/**
 * @brief Create triangle data.
 */
void TestApplication::createTriangle()
{
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    // Create and bind vertex array
    m_triangle_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    
    m_triangle_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    m_triangle_bo->setLayout(
        std::make_shared<ugly::BufferLayout>(std::initializer_list<ugly::BufferElement>{
            ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_triangle_va->addVertexBuffer(m_triangle_bo);

    // Unbind vertex array
    m_triangle_va->unbind();
}


void TestApplication::drawTriangle()
{
    m_shader_program->use();
    m_triangle_va->bind();
    m_display_manager->drawArrays(3, 0);
    m_triangle_va->unbind();
}


void TestApplication::createQuad()
{
    float vertices[] = 
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    uint32_t indices[] = 
    {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create and bind vertex array
    m_quad_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer and bind vertex buffer
    auto quad_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    quad_bo->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list<ugly::BufferElement>{ 
                ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));
 
    // Set vertex pointer
    m_quad_va->addVertexBuffer(quad_bo);

    // Create element buffer
    auto quad_eb = std::make_shared<ugly::IndexBuffer>(sizeof(indices), indices);
    m_quad_va->setIndexBuffer(quad_eb);

    // Unbind vertex array
    m_quad_va->unbind();
}


void TestApplication::drawQuad()
{
    m_shader_program->use();
    m_quad_va->bind();
    m_display_manager->drawElements(6);
    m_quad_va->unbind();

}


void TestApplication::createTriangles()
{
    float vertices[] = 
    {
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
    };  

    // Create and bind vertex array
    m_triangles_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto triangles_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    triangles_bo->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list<ugly::BufferElement>{ ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_triangles_va->addVertexBuffer(triangles_bo);

    // Unbind vertex array
    m_triangles_va->unbind(); 
}


void TestApplication::drawTriangles()
{
    m_shader_program->use();
    m_triangles_va->bind();
    m_display_manager->drawArrays(6);
    m_triangles_va->unbind();
}


/**
 * @brief Create triangles data.
 */
void TestApplication::createTriangles2VA()
{
    float vertices0[] = 
    {
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Create and bind vertex array
    m_triangles_20_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto triangles_20_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices0), vertices0);
    triangles_20_bo->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list<ugly::BufferElement>{ ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));
    
    // Set vertex pointer
    m_triangles_20_va->addVertexBuffer(triangles_20_bo);

    // Unbind vertex array
    m_triangles_20_va->unbind(); 

    float vertices1[] = 
    {
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };   

    // Create and bind vertex array
    m_triangles_21_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto triangles_21_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices1), vertices1);
    triangles_21_bo->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list{ ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_triangles_21_va->addVertexBuffer(triangles_21_bo);

    // Unbind vertex array
    m_triangles_21_va->unbind();
}    


void TestApplication::drawTriangles2VA()
{
    m_shader_program->use();
    m_triangles_20_va->bind();
    m_display_manager->drawArrays(3);
    m_triangles_20_va->unbind();
    m_triangles_21_va->bind();
    m_display_manager->drawArrays(3);
    m_triangles_21_va->unbind();
}


/**
 * @brief Draw triangles.
 */
void TestApplication::drawTriangles2VA2Programs()
{
    m_shader_program->use();
    m_triangles_20_va->bind();
    m_display_manager->drawArrays(3);
    m_triangles_20_va->unbind();

    m_shader_program_yellow->use();
    m_triangles_21_va->bind();
    m_display_manager->drawArrays(3);
    m_triangles_21_va->unbind();
}