#include "SimpleQuadTask.h"


SimpleQuadTask::SimpleQuadTask() : Task()
{
}


SimpleQuadTask::~SimpleQuadTask()
{
}


void SimpleQuadTask::initialize()
{
    /** Vertex shader source **/
    char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    /** Fragment shader source **/
    char* fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

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
    m_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer and bind vertex buffer
    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    bo->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_va->addVertexBuffer(bo);

    // Create element buffer
    auto eb = std::make_shared<ugly::IndexBuffer>(sizeof(indices), indices);
    m_va->setIndexBuffer(eb);

    // Unbind vertex array
    m_va->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(vertex_shader_source, fragment_shader_source);
}


void SimpleQuadTask::shutdown()
{
    m_va.reset();
    m_program.reset();
}


void SimpleQuadTask::update()
{
}


void SimpleQuadTask::updateGui()
{
}


void SimpleQuadTask::render()
{
    m_program->use();
    m_va->bind();
    m_display_manager->drawElements(6);
    m_va->unbind();
}
