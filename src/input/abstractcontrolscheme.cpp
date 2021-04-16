#include "abstractcontrolscheme.h"

#include <algorithm>

#include "abstractactionmap.h"
#include "binding.h"
#include "inputhandler.h"

AbstractControlScheme::AbstractControlScheme()
{
    InputHandler::instance().addControlScheme(this);
}

AbstractControlScheme::~AbstractControlScheme()
{
    InputHandler::instance().removeControlScheme(this);
}

void AbstractControlScheme::setActive(bool state)
{
    std::for_each(m_actionMaps.begin(), m_actionMaps.end(),
                  [state](auto action) { action->setActive(state); });
}

bool AbstractControlScheme::isActive() const
{
    return std::any_of(m_actionMaps.cbegin(), m_actionMaps.cend(),
                       [](const auto action) { return action->isActive(); });
}

void AbstractControlScheme::setGamepadId(int id)
{
    m_gamepadId = id;
}

void AbstractControlScheme::handleGamepadInput(
    const std::vector<GamepadInput>& inputs)
{
    for (auto& maps : m_actionMaps)
    {
        if (!maps->isActive()) continue;
        auto axisBindings = maps->typeBinding(InputType::GamepadAxis);
        auto buttonBindings = maps->typeBinding(InputType::GamepadButton);
        if (axisBindings.empty() && buttonBindings.empty()) continue;
        for (auto& input : inputs)
        {
            if (m_gamepadId.has_value() && m_gamepadId != input.padId) continue;
            if (input.isAxis)
            {
                for (auto& pair : axisBindings)
                    if (std::find(pair.first.cbegin(), pair.first.cend(),
                                  input.btnId) != pair.first.cend())
                        pair.second->setValue(InputType::GamepadAxis,
                                              input.btnId, input.value);
            }
            else
            {
                for (auto& pair : buttonBindings)
                    if (std::find(pair.first.cbegin(), pair.first.cend(),
                                  input.btnId) != pair.first.cend())
                        pair.second->setValue(InputType::GamepadButton,
                                              input.btnId, input.value);
            }
        }
    }
}

void AbstractControlScheme::handleKeyboardInput(
    const std::vector<KeyboardInput>& inputs)
{
    for (auto& maps : m_actionMaps)
    {
        if (!maps->isActive()) continue;
        auto bindings = maps->typeBinding(InputType::Keyboard);
        if (bindings.empty()) continue;
        for (auto& input : inputs)
        {
            for (auto& pair : bindings)
                if (std::find(pair.first.cbegin(), pair.first.cend(),
                              input.key) != pair.first.cend())
                    pair.second->setValue(InputType::GamepadAxis, input.key,
                                          input.value);
        }
    }
}

void AbstractControlScheme::handleMouseInput(
    const std::vector<MouseInput>& inputs)
{
    for (auto& maps : m_actionMaps)
    {
        if (!maps->isActive()) continue;
        auto bindings = maps->typeBinding(InputType::MouseButton);
        if (bindings.empty()) continue;
        for (auto& input : inputs)
        {
            for (auto& pair : bindings)
                if (std::find(pair.first.cbegin(), pair.first.cend(),
                              input.button) != pair.first.cend())
                    pair.second->setValue(InputType::GamepadAxis, input.button,
                                          input.value);
        }
    }
}