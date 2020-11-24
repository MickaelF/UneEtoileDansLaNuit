#include "action.h"

#include "iactionlistener.h"
#include "inputhandler.h"

Action::Action(const std::string& name, int id) : m_name(name), m_id(id)
{
    InputHandler::instance().addAction(this);
}

Action::~Action()
{
    InputHandler::instance().removeAction(this);
}

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