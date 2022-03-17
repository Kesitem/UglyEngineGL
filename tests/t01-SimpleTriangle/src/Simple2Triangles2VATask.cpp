#include "Simple2Triangles2VATask.h"



Simple2Triangles2VATask::Simple2Triangles2VATask() : Task()
{
}


Simple2Triangles2VATask::~Simple2Triangles2VATask()
{
}


void Simple2Triangles2VATask::initialize()
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

    float vertices0[] =
    {
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Create and bind vertex array
    m_va0 = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto bo0 = std::make_shared<ugly::VertexBuffer>(sizeof(vertices0), vertices0);
    bo0->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list<ugly::BufferElement>{ ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_va0->addVertexBuffer(bo0);

    // Unbind vertex array
    m_va0->unbind();

    float vertices1[] =
    {
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };

    // Create and bind vertex array
    m_va1 = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto bo1 = std::make_shared<ugly::VertexBuffer>(sizeof(vertices1), vertices1);
    bo1->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list{ ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_va1->addVertexBuffer(bo1);

    // Unbind vertex array
    m_va1->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(vertex_shader_source, fragment_shader_source);
}


void Simple2Triangles2VATask::shutdown()
{
    m_va0.reset();
    m_va1.reset();
    m_program.reset();
}


void Simple2Triangles2VATask::update()
{
}


void Simple2Triangles2VATask::updateGui()
{
}


void Simple2Triangles2VATask::render()
{
    m_program->use();
    m_va0->bind();
    m_display_manager->drawArrays(3);
    m_va0->unbind();
    m_va1->bind();
    m_display_manager->drawArrays(3);
    m_va1->unbind();
}
