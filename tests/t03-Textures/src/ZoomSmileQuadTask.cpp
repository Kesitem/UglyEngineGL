#include "ZoomSmileQuadTask.h"


ZoomSmileQuadTask::ZoomSmileQuadTask() : Task()
{
}


ZoomSmileQuadTask::~ZoomSmileQuadTask()
{
}


void ZoomSmileQuadTask::initialize()
{
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.60f, 0.60f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.60f, 0.40f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.40f, 0.40f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.40f, 0.60f    // top left 
    };

    uint32_t indices[] =
    {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create and bind vertex array
    m_va = std::make_shared<ugly::VertexArrays>();

    // Create vertex buffer
    auto quad_bo = std::make_shared<ugly::VertexBuffer>(sizeof(vertices), vertices);
    quad_bo->setLayout(std::make_shared<ugly::BufferLayout>(
        std::initializer_list<ugly::BufferElement>{
            ugly::BufferElement("a_vertex", ugly::BufferDataType::FLOAT3, false),
            ugly::BufferElement("a_color", ugly::BufferDataType::FLOAT3, false),
            ugly::BufferElement("a_texcoord", ugly::BufferDataType::FLOAT2, false)}));

    // Set vertex pointer
    m_va->addVertexBuffer(quad_bo);

    // Create element buffer
    auto eb = std::make_shared<ugly::IndexBuffer>(sizeof(indices), indices);
    m_va->setIndexBuffer(eb);

    // Unbind vertex array
    m_va->unbind();

    // Create program
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/shaders/quad.vert"), std::filesystem::path("./data/shaders/quad.frag"));

    // Create texture
    m_texture0 = std::make_shared<ugly::Texture>("./data/textures/container.jpg", ugly::Texture::MinMagFilter::NEAREST, ugly::Texture::MinMagFilter::NEAREST);
    m_texture1 = std::make_shared<ugly::Texture>("./data/textures/awesomeface.png", ugly::Texture::MinMagFilter::NEAREST, ugly::Texture::MinMagFilter::NEAREST);
}


void ZoomSmileQuadTask::shutdown()
{
    m_va.reset();
    m_program.reset();
    m_texture0.reset();
    m_texture1.reset();
}


void ZoomSmileQuadTask::update()
{
}


void ZoomSmileQuadTask::updateGui()
{
}


void ZoomSmileQuadTask::render()
{
    m_program->use();
    m_program->setUniform("texture0", 0);
    m_program->setUniform("texture1", 1);
    m_va->bind();
    m_texture0->bind(0);
    m_texture1->bind(1);
    m_display_manager->drawElements(6);
    m_va->unbind();
}
