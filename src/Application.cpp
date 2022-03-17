#include "Application.h"
#include "Engine.h"


ugly::Application::Application()
{
    LOG_INFO << "--- Create application";

    m_task_manager = ugly::Engine::getInstance()->getTaskManager();
    m_input_manager = ugly::Engine::getInstance()->getInputManager();
    m_display_manager = ugly::Engine::getInstance()->getDisplayManager();

    Engine::getInstance()->getInputManager()->createButton("quit");
    Engine::getInstance()->getInputManager()->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");
}


ugly::Application::~Application()
{
    LOG_INFO << "--- Destroy application";
}

void ugly::Application::initialize()
{
}

void ugly::Application::shutdown()
{
}


void ugly::Application::update()
{
    if(Engine::getInstance()->getInputManager()->getButtonAction("quit") == InputAction::released)
        Engine::getInstance()->quit();
}


void ugly::Application::render()
{
    Engine::getInstance()->getDisplayManager()->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    Engine::getInstance()->getDisplayManager()->clear();
}


void ugly::Application::updateGui()
{
    ImGui::Begin("Ugly");
    ImGui::Text("UglyEngine Base application");
    ImGui::End();
}


const std::string &ugly::Application::getTitle() const
{
    return m_title;
}