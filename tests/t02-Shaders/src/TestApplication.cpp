#include "TestApplication.h"
#include "config.h"

/**
 * @brief Constructor.
 */
TestApplication::TestApplication()
{
    this->m_name = ugly::test::APPLICATION_NAME;
}


/**
 * \brief Initialize application.
 * 
 * \return False if error
 */
bool TestApplication::initialize()
{
    ugly::Engine::getInstance()->getInputManager()->createButton("quit");
    ugly::Engine::getInstance()->getInputManager()->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");
    ugly::Engine::getInstance()->getInputManager()->createButton("wireframe");
    ugly::Engine::getInstance()->getInputManager()->bindKeyToButton(GLFW_KEY_W, "wireframe");

    createTriangle();

    // Create program
    m_shader_program.createFromFile("./data/simple.vert", "./data/simple.frag");

    return true;
}


/**
 * \brief Shutdown application.
 */
void TestApplication::shutdown()
{
    destroyTriangle();

    m_shader_program.destroy();
}


/**
 * @brief Update application.
 */
void TestApplication::update()
{
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("quit") == ugly::InputAction::released)
        ugly::Engine::getInstance()->quit();
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("wireframe") == ugly::InputAction::released)
        m_wireframe = !m_wireframe;
        
    ugly::gl::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    ugly::gl::clear(GL_COLOR_BUFFER_BIT);

    if(m_wireframe)
        ugly::gl::setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        ugly::gl::setPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    drawTriangle();
}


/**
 * @brief Create triangle data.
 */
void TestApplication::createTriangle()
{
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    // Create and bind vertex array
    m_triangle_va.create();

    // Create vertex buffer
    m_triangle_bo.create(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex pointer
    m_triangle_va.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_triangle_va.enableVertexAttribArray(0);

    // Unbind vertex array
    m_triangle_va.unbind();
}


/**
 * @brief Destroy triangle data.
 */
void TestApplication::destroyTriangle()
{
    m_triangle_va.destroy();
    m_triangle_bo.destroy();
}


/**
 * @brief Draw triangle.
 */
void TestApplication::drawTriangle()
{
    float time_value = (float)glfwGetTime();
    float green_value = (sin(time_value) / 2.0f) + 0.5f;

    m_shader_program.use();
    m_shader_program.setUniform("ourColor", glm::vec4(0.0f, green_value, 0.0f, 0.0f));
    m_shader_program.setUniform("xOffset", 0.5f);
    m_triangle_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 3);
    m_triangle_va.unbind();
}