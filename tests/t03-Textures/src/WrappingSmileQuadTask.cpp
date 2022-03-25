#include "WrappingSmileQuadTask.h"


WrappingSmileQuadTask::WrappingSmileQuadTask() : Task()
{
}


WrappingSmileQuadTask::~WrappingSmileQuadTask()
{
}


void WrappingSmileQuadTask::initialize()
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
    m_program = std::make_shared<ugly::Program>(std::filesystem::path("./data/shaders/quad.vert"), std::filesystem::path("./data/shaders/quad_reverse.frag"));

    // Create texture
    m_texture0 = std::make_shared<ugly::Texture>("./data/textures/container.jpg");
    m_texture1 = std::make_shared<ugly::Texture>("./data/textures/awesomeface.png");
}


void WrappingSmileQuadTask::shutdown()
{
    m_va.reset();
    m_program.reset();
    m_texture0.reset();
    m_texture1.reset();
}


void WrappingSmileQuadTask::update()
{
    switch (m_wrapping_method)
    {
    case 0:
        m_texture0->setWrap(ugly::Texture::WrapFilter::REPEAT, ugly::Texture::WrapFilter::REPEAT);
        break;
    case 1:
        m_texture0->setWrap(ugly::Texture::WrapFilter::MIRRORED_REPEAT, ugly::Texture::WrapFilter::MIRRORED_REPEAT);
        break;
    case 2:
        m_texture0->setWrap(ugly::Texture::WrapFilter::CLAMP_TO_EDGE, ugly::Texture::WrapFilter::CLAMP_TO_EDGE);
        break;
    case 3:
        m_texture0->setWrap(ugly::Texture::WrapFilter::CLAMP_TO_BORDER, ugly::Texture::WrapFilter::CLAMP_TO_BORDER);
        break;
    }
}


void WrappingSmileQuadTask::updateGui()
{
    static std::vector<std::string> wrapping({ "repeat", "mirrored repeat", "clamp to edge", "clamp to border"});
    if (ImGui::BeginListBox("Wrapping methods"))
    {
        for (int n = 0; n < wrapping.size(); n++)
        {
            const bool is_selected = (m_wrapping_method == n);
            if (ImGui::Selectable(wrapping[n].c_str(), is_selected))
                m_wrapping_method = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
}


void WrappingSmileQuadTask::render()
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
