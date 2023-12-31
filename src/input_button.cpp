#include "input_button.h"


ugly::InputButton::InputButton()
{
}


const ugly::InputState& ugly::InputButton::getState() const
{
    return m_state;
}


void ugly::InputButton::setState(const ugly::InputState& _state)
{
    m_state = _state;
}


const ugly::InputAction& ugly::InputButton::getAction() const
{
    return m_action;
}


void ugly::InputButton::setAction(const ugly::InputAction& _action)
{
    m_action = _action;
}