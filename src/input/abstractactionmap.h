#pragma once
#include <map>

#include "action.h"
#include "inputtype.h"

typedef std::vector<std::pair<std::vector<int>, Binding*>> KeyBinding;

class Binding;

class AbstractActionMap
{
public:
    AbstractActionMap() = default;

    std::vector<Action*>& actions() { return m_actions; }

    bool isActive() const;
    void setActive(bool state);

    virtual KeyBinding& typeBinding(InputType type) = 0;

protected:
    std::vector<Action*> m_actions;
};