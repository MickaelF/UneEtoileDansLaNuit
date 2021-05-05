#include <UneEtoile/input/inputhandler.h>

#include <UneEtoile/input/abstractactionmap.h>
#include <UneEtoile/input/abstractcontrolscheme.h>
#include <UneEtoile/input/binding.h>
#include <UneEtoile/input/inputrecorder.h>

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

void InputHandler::handleGamepadInput(
    const std::vector<GamepadInput>& inputs,
    std::chrono::time_point<std::chrono::steady_clock> now)
{
    if (m_recorder) m_recorder->handleGamepadInput(inputs, now);
    for (auto scheme : m_controlScheme)
        if (scheme->isActive()) scheme->handleGamepadInput(inputs);
}

void InputHandler::handleKeyboardInput(
    const std::vector<KeyboardInput>& inputs,
    std::chrono::time_point<std::chrono::steady_clock> now)
{
    if (m_recorder) m_recorder->handleKeyboardInput(inputs, now);
    for (auto scheme : m_controlScheme)
        if (scheme->isActive()) scheme->handleKeyboardInput(inputs);
}

void InputHandler::handleMouseInput(
    const std::vector<MouseInput>& inputs,
    std::chrono::time_point<std::chrono::steady_clock> now)
{
    if (m_recorder) m_recorder->handleMouseInput(inputs, now);
    for (auto scheme : m_controlScheme)
        if (scheme->isActive()) scheme->handleMouseInput(inputs);
}

void InputHandler::startRecording()
{
    m_recorder = new InputRecorder();
    m_recorder->start();
}
