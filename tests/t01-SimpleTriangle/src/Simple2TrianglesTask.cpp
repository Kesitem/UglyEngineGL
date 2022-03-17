#include "Simple2TrianglesTask.h"



Simple2TrianglesTask::Simple2TrianglesTask() : Task()
{
}


Simple2TrianglesTask::~Simple2TrianglesTask()
{
}


void Simple2TrianglesTask::initialize()
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
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
    };

    // Create and bind vertex array
    m_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    bo->setLayout(
        std::make_shared<ugly::BufferLayout>(
            std::initializer_list<ugly::BufferElement>{ ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_va->addVertexBuffer(bo);

    // Unbind vertex array
    m_va->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(vertex_shader_source, fragment_shader_source);
}


void Simple2TrianglesTask::shutdown()
{
    m_va.reset();
    m_program.reset();
}


void Simple2TrianglesTask::update()
{
}


void Simple2TrianglesTask::updateGui()
{
}


void Simple2TrianglesTask::render()
{
    m_program->use();
    m_va->bind();
    m_display_manager->drawArrays(6);
    m_va->unbind();
}
