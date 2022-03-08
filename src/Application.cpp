#include "Application.h"
#include "Engine.h"


ugly::Application::Application()
{
    LOG_INFO << "--- Create application";
    Engine::getInstance()->getInputManager()->createButton("quit");
    Engine::getInstance()->getInputManager()->bindKeyToButton(GLFW_KEY_ESCAPE, "quit");
}


ugly::Application::~Application()
{
    LOG_INFO << "--- Destroy application";
}


void ugly::Application::update()
{
    if(Engine::getInstance()->getInputManager()->getButtonAction("quit") == InputAction::released)
        Engine::getInstance()->quit();
}


void ugly::Application::draw()
{
    Engine::getInstance()->getDisplayManager()->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    Engine::getInstance()->getDisplayManager()->clear();
}


void ugly::Application::renderGui()
{
    ImGui::Begin("Ugly");
    ImGui::Text("UglyEngine Base application");
    ImGui::End();
}


const std::string &ugly::Application::getName() const
{
    return m_name;
}