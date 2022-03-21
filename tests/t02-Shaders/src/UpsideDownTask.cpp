#include "UpsideDownTask.h"


UpsideDownTask::UpsideDownTask() : Task()
{
}


UpsideDownTask::~UpsideDownTask()
{
}


void UpsideDownTask::initialize()
{
    float color_vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    // Create and bind vertex array
    m_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer

    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(color_vertices), color_vertices);
    bo->setLayout(
        std::make_shared<ugly::BufferLayout>(std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false),
        ugly::BufferElement("a_color", ugly::BufferDataType::FLOAT3, false)}));

    // Set vertex pointer
    m_va->addVertexBuffer(bo);

    // Unbind vertex array
    m_va->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/simple_color_inverted.vert"), std::filesystem::path("./data/simple_color.frag"));
}


void UpsideDownTask::shutdown()
{
    m_va.reset();
    m_program.reset();
}


void UpsideDownTask::update()
{
}


void UpsideDownTask::updateGui()
{
}


void UpsideDownTask::render()
{
    m_program->use();
    m_va->bind();
    m_display_manager->drawArrays(3, 0);
    m_va->unbind();
}
