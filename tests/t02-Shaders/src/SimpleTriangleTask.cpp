#include "SimpleTriangleTask.h"


SimpleTriangleTask::SimpleTriangleTask() : Task()
{
}


SimpleTriangleTask::~SimpleTriangleTask()
{
}


void SimpleTriangleTask::initialize()
{
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // Create and bind vertex array
    m_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer

    auto bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    bo->setLayout(
        std::make_shared<ugly::BufferLayout>(std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false) }));

    // Set vertex pointer
    m_va->addVertexBuffer(bo);

    // Unbind vertex array
    m_va->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/simple_red.vert"), std::filesystem::path("./data/simple_red.frag"));
}


void SimpleTriangleTask::shutdown()
{
    m_va.reset();
    m_program.reset();
}


void SimpleTriangleTask::update()
{
}


void SimpleTriangleTask::updateGui()
{
}


void SimpleTriangleTask::render()
{
    m_program->use();
    m_va->bind();
    m_display_manager->drawArrays(3, 0);
    m_va->unbind();
}
