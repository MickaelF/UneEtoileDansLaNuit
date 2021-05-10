#include <UneEtoile/input/abstractactionmap.h>

#include <algorithm>

AbstractActionMap::AbstractActionMap(const char* name) : name(name) {}

AbstractActionMap::~AbstractActionMap() {}

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