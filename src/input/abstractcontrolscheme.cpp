#include <UneEtoile/input/abstractactionmap.h>
#include <UneEtoile/input/abstractcontrolscheme.h>
#include <UneEtoile/input/binding.h>
#include <UneEtoile/input/inputhandler.h>

#include <algorithm>

AbstractControlScheme::AbstractControlScheme(const char* name) : name(name)
{
    InputHandler::instance().addControlScheme(this);
}

AbstractControlScheme::~AbstractControlScheme()
{
    InputHandler::instance().removeControlScheme(this);
}

void AbstractControlScheme::setActive(bool state)
{
    std::for_each(m_actions.begin(), m_actions.end(),
                  [state](auto action) { action->setActive(state); });
}

bool AbstractControlScheme::isActive() const
{
    return std::any_of(m_actions.cbegin(), m_actions.cend(),
                       [](const auto action) { return action->isActive(); });
}

void AbstractControlScheme::setGamepadId(int id)
{
    m_gamepadId = id;
}

bool AbstractControlScheme::acceptInput(InputData input) const
{
    if (m_gamepadId.has_value() && !input.contains(m_gamepadId.value()))
        return false;
    return (input.id & m_acceptedInputs) != InputEnum::None;
}

void AbstractControlScheme::loadBindings() {}