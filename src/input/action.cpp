#include <UneEtoile/input/action.h>

#include <UneEtoile/input/binding.h>
#include <UneEtoile/input/iactionlistener.h>
#include <UneEtoile/input/inputhandler.h>

Action::Action(const std::string& name) : m_name(name) {}

void Action::addListener(IActionListener* listener)
{
    if (!hasListener(listener)) m_listeners.push_back(listener);
}

void Action::removeListener(IActionListener* listener)
{
    m_listeners.erase(
        std::remove(m_listeners.begin(), m_listeners.end(), listener));
}

bool Action::hasListener(IActionListener* listener) const
{
    return std::find(m_listeners.cbegin(), m_listeners.cend(), listener) !=
           m_listeners.cend();
}

void Action::setActive(bool state)
{
    if (m_active != state) m_active = state;
}

BinaryAction::BinaryAction(const std::string& name) : Action(name) {}

void BinaryAction::notify(Binding* binding)
{
    BinaryBinding* bb = static_cast<BinaryBinding*>(binding);
    if (bb->pressed() && m_on || !bb->pressed() && !m_on) return;
    m_on = bb->pressed();
    for (auto& listener : m_listeners) listener->onAction(this);
}

RangeAction::RangeAction(const std::string& name) : Action(name) {}

void RangeAction::notify(Binding* binding)
{
    RangeBinding* bb = static_cast<RangeBinding*>(binding);
    m_value = bb->value();
    for (auto& listener : m_listeners) listener->onAction(this);
}

Vector2Action::Vector2Action(const std::string& name) : Action(name) {}

void Vector2Action::notify(Binding* binding)
{
    Vector2Binding* bb = static_cast<Vector2Binding*>(binding);
    m_value = bb->value();
    for (auto& listener : m_listeners) listener->onAction(this);
}
