#include "TestApplication.h"
#include "config.h"

/** Vertex shader source **/
const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

/** Fragment shader source **/
const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

/** Fragment shader source **/
const char *fragment_shader_source_yellow = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";


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
    ugly::Engine::getInstance()->getInputManager()->createButton("render-type");
    ugly::Engine::getInstance()->getInputManager()->bindKeyToButton(GLFW_KEY_R, "render-type");

    createTriangle();
    createQuad();
    createTriangles();
    createTriangles2VA();

    // Create vertex shader
    ugly::gl::Shader vertex_shader;
    vertex_shader.create(GL_VERTEX_SHADER, vertex_shader_source);

    // Create fragment shader
    ugly::gl::Shader fragment_shader;
    fragment_shader.create(GL_FRAGMENT_SHADER, fragment_shader_source);

    // Create fragment shader yellow
    ugly::gl::Shader fragment_shader_yellow;
    fragment_shader_yellow.create(GL_FRAGMENT_SHADER, fragment_shader_source_yellow);

    // Create program
    m_shader_program.create(&vertex_shader, &fragment_shader);
 
    // Create yellow
    m_shader_program_yellow.create(&vertex_shader, &fragment_shader_yellow);

    // Delete shaders  
    vertex_shader.destroy();
    fragment_shader.destroy(); 
    fragment_shader_yellow.destroy(); 

    return true;
}


/**
 * \brief Shutdown application.
 */
void TestApplication::shutdown()
{
    destroyTriangle();
    destroyQuad();
    destroyTriangles();
    destroyTriangles2VA();
    m_shader_program.destroy();
    m_shader_program_yellow.destroy();
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
    if(ugly::Engine::getInstance()->getInputManager()->getButtonAction("render-type") == ugly::InputAction::released)
    {
        m_render_type++;
        if(m_render_type > 4)
            m_render_type = 0;
    }

        
    ugly::gl::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    ugly::gl::clear(GL_COLOR_BUFFER_BIT);

    if(m_wireframe)
        ugly::gl::setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        ugly::gl::setPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    switch(m_render_type)
    {
        case 0:
        {
            drawTriangle();
            break;
        }
        case 1:
        {
            drawQuad();
            break;
        }
        case 2:
        {
            drawTriangles();
            break;
        }
        case 3:
        {
            drawTriangles2VA();
            break;
        }
        case 4:
        {
            drawTriangles2VA2Programs();
            break;
        }
    }
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
    m_shader_program.use();
    m_triangle_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 3);
    m_triangle_va.unbind();
}


/**
 * @brief Create a Quad data.
 */
void TestApplication::createQuad()
{
    GLfloat vertices[] = 
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    GLuint indices[] = 
    {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create and bind vertex array
    m_quad_va.create();

    // Create vertex buffer and bind vertex buffer
    m_quad_bo.create(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    // Set vertex pointer
    m_quad_va.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    m_quad_va.enableVertexAttribArray(0);    

    // Create element buffer
    m_quad_eb.create(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind vertex array
    m_quad_va.unbind();
}


/**
 * @brief Destroy quad data.
 */
void TestApplication::destroyQuad()
{
    m_quad_va.destroy();
    m_quad_bo.destroy();
    m_quad_eb.destroy();
}


/**
 * @brief Draw Quad.
 */
void TestApplication::drawQuad()
{
    m_shader_program.use();
    m_quad_va.bind();
    ugly::gl::drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_quad_va.unbind();
}


/**
 * @brief Create triangles data.
 */
void TestApplication::createTriangles()
{
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
    m_triangles_va.create();

    // Create vertex buffer
    m_triangles_bo.create(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex pointer
    m_triangles_va.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_triangles_va.enableVertexAttribArray(0);

    // Unbind vertex array
    m_triangles_va.unbind(); 
}


/**
 * @brief Destroy triangles data.
 */
void TestApplication::destroyTriangles()
{
    m_triangles_va.destroy();
    m_triangles_bo.destroy();
}


/**
 * @brief Draw triangles.
 */
void TestApplication::drawTriangles()
{
    m_shader_program.use();
    m_triangles_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 6);
    m_triangles_va.unbind();
}


/**
 * @brief Create triangles data.
 */
void TestApplication::createTriangles2VA()
{
    float vertices0[] = 
    {
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Create and bind vertex array
    m_triangles_20_va.create();

    // Create vertex buffer
    m_triangles_20_bo.create(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);
    
    // Set vertex pointer
    m_triangles_20_va.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_triangles_20_va.enableVertexAttribArray(0);

    // Unbind vertex array
    m_triangles_20_va.unbind(); 

    float vertices1[] = 
    {
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };   

    // Create and bind vertex array
    m_triangles_21_va.create();

    // Create vertex buffer
    m_triangles_21_bo.create(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    
    // Set vertex pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind vertex array
    glBindVertexArray(0); 
}    


/**
 * @brief Destroy triangles data.
 */
void TestApplication::destroyTriangles2VA()
{
    m_triangles_20_va.destroy();
    m_triangles_20_bo.destroy();
    m_triangles_21_va.destroy();
    m_triangles_21_bo.destroy();
}


/**
 * @brief Draw triangles.
 */
void TestApplication::drawTriangles2VA()
{
    m_shader_program.use();
    m_triangles_20_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 3);
    m_triangles_20_va.unbind();
    m_triangles_21_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 3);
    m_triangles_21_va.unbind();
}


/**
 * @brief Draw triangles.
 */
void TestApplication::drawTriangles2VA2Programs()
{
    m_shader_program.use();
    m_triangles_20_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 3);
    m_triangles_20_va.unbind();

    m_shader_program_yellow.use();
    m_triangles_21_va.bind();
    ugly::gl::drawArrays(GL_TRIANGLES, 0, 3);
    m_triangles_21_va.unbind();
}