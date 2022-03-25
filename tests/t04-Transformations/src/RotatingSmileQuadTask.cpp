#include "RotatingSmileQuadTask.h"


RotatingSmileQuadTask::RotatingSmileQuadTask() : Task()
{
}


RotatingSmileQuadTask::~RotatingSmileQuadTask()
{
}


void RotatingSmileQuadTask::initialize()
{
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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
    m_texture0 = std::make_shared<ugly::Texture>("./data/textures/container.jpg");
    m_texture1 = std::make_shared<ugly::Texture>("./data/textures/awesomeface.png");
}


void RotatingSmileQuadTask::shutdown()
{
    m_va.reset();
    m_program.reset();
    m_texture0.reset();
    m_texture1.reset();
}


void RotatingSmileQuadTask::update()
{
    if(m_transform_order == 0)
    { 
        m_transform_matrix = glm::mat4(1.0f);
        m_transform_matrix = glm::translate(m_transform_matrix, glm::vec3(0.5f, -0.5f, 0.0f));
        m_transform_matrix = glm::rotate(m_transform_matrix, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    }
    else
    {
        m_transform_matrix = glm::mat4(1.0f);
        m_transform_matrix = glm::rotate(m_transform_matrix, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        m_transform_matrix = glm::translate(m_transform_matrix, glm::vec3(0.5f, -0.5f, 0.0f));
    }
}


void RotatingSmileQuadTask::updateGui()
{
    static std::vector<std::string> wrapping({ "rotate then translate", "translate then rotate" });
    if (ImGui::BeginListBox("Wrapping methods"))
    {
        for (int n = 0; n < wrapping.size(); n++)
        {
            const bool is_selected = (m_transform_order == n);
            if (ImGui::Selectable(wrapping[n].c_str(), is_selected))
                m_transform_order = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
}


void RotatingSmileQuadTask::render()
{
    m_program->use();
    m_program->setUniform("texture0", 0);
    m_program->setUniform("texture1", 1);
    m_program->setUniform("u_transform", m_transform_matrix);
    m_va->bind();
    m_texture0->bind(0);
    m_texture1->bind(1);
    m_display_manager->drawElements(6);
    m_va->unbind();
}
