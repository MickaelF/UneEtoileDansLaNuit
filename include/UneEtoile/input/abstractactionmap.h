#pragma once
#include <UneEtoile/input/action.h>
#include <UneEtoile/input/inputtype.h>

#include <map>

typedef std::vector<std::pair<std::vector<int>, Binding*>> KeyBinding;

class Binding;

class AbstractActionMap
{
public:
    AbstractActionMap(const char* name);
    virtual ~AbstractActionMap();

    const char* name;

    std::vector<Action*>& actions() { return m_actions; }

    bool isActive() const;
    void setActive(bool state);

    virtual KeyBinding& typeBinding(InputType type) = 0;

protected:
    std::vector<Action*> m_actions;
};