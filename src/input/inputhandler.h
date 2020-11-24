#pragma once
#include <vector>

class Action;

class InputHandler
{
public:
    InputHandler() = default;
    static InputHandler& instance();

    void addAction(Action* action);
    void removeAction(Action* action);

    void run();

private:
    std::vector<Action*> m_actions;
};