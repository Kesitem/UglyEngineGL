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

    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    char vertex_shader_source[] = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    char fragment_shader_source[] = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    
    // Create vertex buffer
    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    bo->setLayout({ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)});

    // Set vertex pointer
    m_va.addVertexBuffer(bo);

    // Unbind vertex array
    m_va.unbind();

    // Create program
    m_program.create(ugly::Shader(ugly::ShaderType::VERTEX, vertex_shader_source), 
                     ugly::Shader(ugly::ShaderType::FRAGMENT, fragment_shader_source));

    
}


void TestApplication::shutdown()
{
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        m_engine->quit();

    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();
}