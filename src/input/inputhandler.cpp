#include "inputhandler.h"

#include "abstractactionmap.h"
#include "abstractcontrolscheme.h"
#include "binding.h"

glm::ivec2 InputHandler::m_mousePosition;

InputHandler& InputHandler::instance()
{
    static InputHandler instance;
    return instance;
}

glm::ivec2 InputHandler::mousePosition()
{
    return m_mousePosition;
}

void InputHandler::setMousePosition(int x, int y)
{
    m_mousePosition = {x, y};
}

void InputHandler::addControlScheme(AbstractControlScheme* scheme)
{
    m_controlScheme.push_back(scheme);
}

void InputHandler::removeControlScheme(AbstractControlScheme* scheme)
{
    m_controlScheme.erase(
        std::remove(m_controlScheme.begin(), m_controlScheme.end(), scheme));
}

void InputHandler::handleGamepadInput(const std::vector<GamepadInput>& inputs)
{
    for (auto scheme : m_controlScheme)
        if (scheme->isActive()) scheme->handleGamepadInput(inputs);
}

void InputHandler::handleKeyboardInput(const std::vector<KeyboardInput>& inputs)
{
    for (auto scheme : m_controlScheme)
        if (scheme->isActive()) scheme->handleKeyboardInput(inputs);
}

void InputHandler::handleMouseInput(const std::vector<MouseInput>& inputs)
{
    for (auto scheme : m_controlScheme)
        if (scheme->isActive()) scheme->handleMouseInput(inputs);
}
