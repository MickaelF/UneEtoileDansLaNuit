#include "abstractcontrolscheme.h"

#include <algorithm>

#include "abstractactionmap.h"
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