#include "inputhandler.h"

#include "action.h"

InputHandler& InputHandler::instance()
{
    static InputHandler instance;
    return instance;
}

void InputHandler::addAction(Action* action)
{
    m_actions.push_back(action);
}

void InputHandler::removeAction(Action* action)
{
    m_actions.erase(std::remove(m_actions.begin(), m_actions.end(), action));
}

void InputHandler::run()
{
    for (auto action : m_actions)
    {
        if (!action->isActive()) continue;
        for (auto& binding : action->bindings())
        {
            // for (auto input : binding.inputs())
            // {
            //     switch (input.first)
            //     {
            //         case BindingType::GamepadAxis: break;
            //         case BindingType::GamepadButton: break;
            //         case BindingType::Keyboard: break;
            //         case BindingType::MouseButton: break;
            //     }
            // }
        }
    }
}