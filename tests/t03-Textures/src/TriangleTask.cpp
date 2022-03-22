#include "TriangleTask.h"


TriangleTask::TriangleTask() : Task()
{
}


TriangleTask::~TriangleTask()
{
}


void TriangleTask::initialize()
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
    m_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto vertices_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    vertices_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false)}));

    // Set vertex pointer
    m_va->addVertexBuffer(vertices_bo);

    auto tex_coords_bo = std::make_shared<ugly::VertexBuffer>(sizeof(tex_coords), tex_coords);
    tex_coords_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
        ugly::BufferElement("a_texcoord", ugly::BufferDataType::FLOAT2, false)}));

    // Set vertex pointer
    m_va->addVertexBuffer(tex_coords_bo);

    // Unbind vertex array
    m_va->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/shaders/simple.vert"), std::filesystem::path("./data/shaders/simple.frag"));

    // Create texture
    m_texture = std::make_shared<ugly::Texture>("./data/textures/wall.jpg");
}


void TriangleTask::shutdown()
{
    m_va.reset();
    m_program.reset();
    m_texture.reset();
}


void TriangleTask::update()
{
}


void TriangleTask::updateGui()
{
}


void TriangleTask::render()
{
    m_program->use();
    m_va->bind();
    m_texture->bind();
    m_display_manager->drawArrays(3);
    m_va->unbind();
}
