#pragma once
#include <vector>

#include "action.h"

class AbstractActionMap
{
public:
    AbstractActionMap() = default;

    std::vector<Action*>& actions() { return m_actions; }

    bool isActive() const;
    void setActive(bool state);

protected:
    std::vector<Action*> m_actions;
};