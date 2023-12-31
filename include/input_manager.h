#pragma once

#include "core.h"
#include "input_state.h"
#include "input_button.h"

namespace ugly
{

/**
 * @class InputManager
 * @brief Input manager
 */
class InputManager
{
public:

    /**
     *  @brief Constructor.
     */
    InputManager();

    /**
     * @brief Destructor.
     */
    virtual ~InputManager();

    /**
     * @brief Update state manager.
     *
     * This function updates state(for exemple pass key state from released to none).
     * It must be call after event processing and before polling events.
     */
    void update();

    /**
     * @brief Process a key change.
     * 
     * This method is mainly used by GLFW key callback.
     * If key is not bind, nothing happens.
     * @param key_name  GLFW key name
     * @param action    GLFW action
     */
    void processKeyChange(int _key_name, int _action);

    /**
     * @brief Create a button.
     * 
     * @param _button_name   Input button name
     */
    void createButton(const std::string& _button_name);

    /**
     * @brief Bind a key to a button.
     * 
     * @param _key_name      GFLW key name
     * @param _button_name   Button name
     */
    void bindKeyToButton(int _key_name, const std::string& _button_name);

    /**
     * @brief Get a button state.
     * 
     * @param _button_name   Input button name
     * @return input_button state
     */
    const InputState& getButtonState(const std::string& _button_name) const;

    /**
     * @brief Get a button action.
     * 
     * @param button_name   input_button name
     * @return input_button last action
     */
    const InputAction& getButtonAction(const std::string& _button_name) const;

private:

    /*! input_button list. */
    std::map<std::string, InputButton> m_buttons;

    /*! Key to button mapping*/
    std::map<int, std::string> m_key_button_mapping;
};

}//namespace ugly