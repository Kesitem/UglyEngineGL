#include "InputManager.h"
#include "InputButton.h"
#include "Engine.h"


/**
 * \brief GLFW key callback.
 */
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static ugly::Engine* engine = ugly::Engine::getInstance();

    engine->getInputManager()->processKeyChange(key, action);
}


ugly::InputManager::InputManager()
{
    // Register input callbacks
    glfwSetKeyCallback(ugly::Engine::getInstance()->getWindow(), glfwKeyCallback);
}


void ugly::InputManager::update()
{
    for(auto const &button_itor : m_buttons)
    {
        auto button = (button_itor.second).get();
        if(button->getAction() == InputAction::pressed || button->getAction() == InputAction::repeated || button->getAction() == InputAction::released)
        {
            LOG_DEBUG << "Button: " << button_itor.first << "action is set to NONE";
            button->setAction(InputAction::none);
        }
    }
}


void ugly::InputManager::processKeyChange(int key_name, int action)
{
    // Check if key is binded
    auto key_button_mapping_itor = m_key_button_mapping.find(key_name);
    if(key_button_mapping_itor == m_key_button_mapping.end())
        return;

    // Update button
    auto button = (m_buttons[key_button_mapping_itor->second]).get();
    if(action == GLFW_PRESS)
    {
        LOG_DEBUG << "Button: " << key_button_mapping_itor->second << " is pressed";
        button->setState(InputState::press);
        button->setAction(InputAction::pressed);
    }
    else if(action == GLFW_REPEAT)
    {
        LOG_DEBUG << "Button: " << key_button_mapping_itor->second << " is repeated";
        button->setAction(InputAction::repeated);
    }
    else //(action == GLFW_RELEASE)
    {
        LOG_DEBUG << "Button: " << key_button_mapping_itor->second << " is released";
        button->setState(InputState::release);
        button->setAction(InputAction::released);
    }
}


void ugly::InputManager::createButton(const std::string& button_name)
{
    PLOG_INFO << "Create input button: " << button_name;

    auto button_map_itor = m_buttons.find(button_name);
    if( button_map_itor != m_buttons.end())
    {
        PLOG_ERROR << "Trying to create a button already existing: " << button_name;
        return;
    }

    m_buttons.insert(std::make_pair(button_name, std::make_unique<InputButton>()));
}


void ugly::InputManager::bindKeyToButton(int key_name, const std::string& button_name)
{
    LOG_INFO << "Bind key: " <<  key_name << " to input button: " << button_name; 

    auto key_button_mapping_itor = m_key_button_mapping.find(key_name);
    if(key_button_mapping_itor != m_key_button_mapping.end())
    {
        LOG_ERROR << "Key is already bind to button: " << key_button_mapping_itor->second;
        return;
    }

    auto button_itor = m_buttons.find(button_name);
    if(button_itor == m_buttons.end())
    {
        LOG_ERROR << "Button: " << button_name << " not found. Creating it";
        createButton(button_name);
    }

    m_key_button_mapping[key_name] = button_name;
}


const ugly::InputState& ugly::InputManager::getButtonState(const std::string& button_name)
{
    auto button_map_itor = m_buttons.find(button_name);
    if(button_map_itor == m_buttons.end())
    {
        LOG_WARNING << "InputButton: " << button_name << " not found.";
        createButton(button_name);
        button_map_itor = m_buttons.find(button_name);
    }

    return button_map_itor->second.get()->getState();
}


const ugly::InputAction& ugly::InputManager::getButtonAction(const std::string& button_name)
{
    auto button_map_itor = m_buttons.find(button_name);
    if (button_map_itor == m_buttons.end())
    {
        LOG_WARNING << "InputButton: " << button_name << " not found.";
        createButton(button_name);
        button_map_itor = m_buttons.find(button_name);
    }

    return button_map_itor->second.get()->getAction();
}

