#include "abstractactionmap.h"

#include <algorithm>

void AbstractActionMap::setActive(bool state)
{
    std::for_each(m_actions.begin(), m_actions.end(),
                  [state](auto& action) { action->setActive(state); });
}

bool AbstractActionMap::isActive() const
{
    return std::any_of(m_actions.cbegin(), m_actions.cend(),
                       [](const auto& action) { return action->isActive(); });
}