#include "ColoredQuadTask.h"


ColoredQuadTask::ColoredQuadTask() : Task()
{
}


ColoredQuadTask::~ColoredQuadTask()
{
}


void ColoredQuadTask::initialize()
{
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
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
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/shaders/quad_colored.vert"), std::filesystem::path("./data/shaders/quad_colored.frag"));

    // Create texture
    m_texture = std::make_shared<ugly::Texture>("./data/textures/container.jpg");
}


void ColoredQuadTask::shutdown()
{
    m_va.reset();
    m_program.reset();
    m_texture.reset();
}


void ColoredQuadTask::update()
{
}


void ColoredQuadTask::updateGui()
{
}


void ColoredQuadTask::render()
{
    m_program->use();
    m_program->setUniform("texture0", 0);
    m_va->bind();
    m_texture->bind(0);
    m_display_manager->drawElements(6);
    m_va->unbind();
}
