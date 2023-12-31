#include "test_application.h"


TestApplication::TestApplication()
{
}


TestApplication::~TestApplication()
{
}


void TestApplication::initialize()
{
    m_engine = ugly::Engine::getInstance();
    m_input_manager = m_engine->getInputManager();
    m_display_manager = m_engine->getDisplayManager();

    m_input_manager->createButton("quit");
    m_input_manager->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");
}


void TestApplication::shutdown()
{
}


void TestApplication::update()
{
    if(m_input_manager->getButtonAction("quit") == ugly::InputAction::released)
        m_engine->quit();

    m_display_manager->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_display_manager->clear();
}