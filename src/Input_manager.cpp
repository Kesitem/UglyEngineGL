#include "input_manager.h"
#include "input_button.h"
#include "engine.h"


/**
 * @brief GLFW key callback.
 */
void glfwKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    static auto input_manager = ugly::Engine::getInstance()->getInputManager();

    input_manager->processKeyChange(_key, _action);
}


ugly::InputManager::InputManager()
{
    LOG_INFO << "Initialize input manager";
    
    // Register input callbacks
    glfwSetKeyCallback(ugly::Engine::getInstance()->getWindow(), glfwKeyCallback);
}


ugly::InputManager::~InputManager()
{
    LOG_INFO << "Shutdown input manager";
}


void ugly::InputManager::update()
{
    for(auto button_itor: m_buttons)
    {
        auto button = button_itor.second;
        if(button.getAction() == InputAction::pressed || button.getAction() == InputAction::repeated || button.getAction() == InputAction::released)
        {
            button.setAction(InputAction::none);
        }
    }
}


void ugly::InputManager::processKeyChange(int _key_name, int _action)
{
    // Check if key is binded
    auto key_button_mapping_itor = m_key_button_mapping.find(_key_name);
    if(key_button_mapping_itor == m_key_button_mapping.end())
        return;

    // Update button
    if(_action == GLFW_PRESS)
    {
        m_buttons[key_button_mapping_itor->second].setState(InputState::press);
        m_buttons[key_button_mapping_itor->second].setAction(InputAction::pressed);
    }
    else if(_action == GLFW_REPEAT)
    {
        m_buttons[key_button_mapping_itor->second].setAction(InputAction::repeated);
    }
    else //(action == GLFW_RELEASE)
    {
        m_buttons[key_button_mapping_itor->second].setState(InputState::release);
        m_buttons[key_button_mapping_itor->second].setAction(InputAction::released);
    }
}


void ugly::InputManager::createButton(const std::string& _button_name)
{
    PLOG_INFO << "Create input button: " << _button_name;

    auto button_map_itor = m_buttons.find(_button_name);
    if( button_map_itor != m_buttons.end())
    {
        PLOG_WARNING << "Trying to create a button already existing: " << _button_name;
        return;
    }

    m_buttons.insert(std::make_pair(_button_name, InputButton()));
}


void ugly::InputManager::bindKeyToButton(int _key_name, const std::string& _button_name)
{
    LOG_INFO << "Bind key: " <<  _key_name << " to input button: " << _button_name; 

    auto key_button_mapping_itor = m_key_button_mapping.find(_key_name);
    if(key_button_mapping_itor != m_key_button_mapping.end())
    {
        LOG_ERROR << "Key is already bind to button: " << key_button_mapping_itor->second;
        return;
    }

    auto button_itor = m_buttons.find(_button_name);
    if(button_itor == m_buttons.end())
    {
        LOG_ERROR << "Button: " << _button_name << " not found.";
        return;
    }

    m_key_button_mapping[_key_name] = _button_name;
}


const ugly::InputState& ugly::InputManager::getButtonState(const std::string& _button_name) const
{
    auto button_map_itor = m_buttons.find(_button_name);
    if(button_map_itor == m_buttons.end())
    {
        LOG_WARNING << "InputButton: " << _button_name << " not found";
        throw std::invalid_argument("Invalid button name");
    }

    return button_map_itor->second.getState();
}


const ugly::InputAction& ugly::InputManager::getButtonAction(const std::string& _button_name) const
{
    auto button_map_itor = m_buttons.find(_button_name);
    if (button_map_itor == m_buttons.end())
    {
        LOG_WARNING << "InputButton: " << _button_name << " not found.";
        throw std::invalid_argument("Invalid button name");
    }

    return button_map_itor->second.getAction();
}

