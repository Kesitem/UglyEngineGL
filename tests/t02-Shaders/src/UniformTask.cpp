#include "UniformTask.h"


UniformTask::UniformTask() : Task()
{
}


UniformTask::~UniformTask()
{
}


void UniformTask::initialize()
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
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/simple_uniform.vert"), std::filesystem::path("./data/simple_uniform.frag"));
}


void UniformTask::shutdown()
{
    m_va.reset();
    m_program.reset();
}


void UniformTask::update()
{
    // Update timer
    float time_value = (float)glfwGetTime();
    m_green_value = (sin(time_value) / 2.0f) + 0.5f;
}


void UniformTask::updateGui()
{
}


void UniformTask::render()
{
    m_program->use();
    m_program->setUniform("ourColor", glm::vec4(0.0f, m_green_value, 0.0f, 1.0f));
    m_va->bind();
    m_display_manager->drawArrays(3, 0);
    m_va->unbind();
}
