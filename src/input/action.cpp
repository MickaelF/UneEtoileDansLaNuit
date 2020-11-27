#include "action.h"

#include "iactionlistener.h"
#include "inputhandler.h"
namespace
{
static int id = 0;
}

Action::Action(const std::string& name) : m_name(name), m_id(id++) {}

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

ActionContext Action::context(bool started, bool ended) const
{
    return {m_value, started, m_inUse && !started, ended, m_id};
}

void Action::setActive(bool state)
{
    if (m_active != state) m_active = state;
}

void Action::addBinding(Binding* binding)
{
    m_bindings.push_back(binding);
}