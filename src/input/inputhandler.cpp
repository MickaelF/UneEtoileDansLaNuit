#include "inputhandler.h"

#include <pttk/executiontimer.h>

#include "abstractactionmap.h"
#include "abstractcontrolscheme.h"
#include "binding.h"

InputHandler& InputHandler::instance()
{
    static InputHandler instance;
    return instance;
}

void InputHandler::addControlScheme(AbstractControlScheme* scheme)
{
    m_controlScheme.push_back(scheme);
}

void InputHandler::removeControlScheme(AbstractControlScheme* scheme)
{
    m_controlScheme.erase(
        std::remove(m_controlScheme.begin(), m_controlScheme.end(), scheme));
}

void InputHandler::handleGamepadInput(const std::vector<GamepadInput>& inputs)
{
    int i = 0;
    i++;
    i += 2;
}

void InputHandler::handleKeyboardInput(const std::vector<KeyboardInput>& inputs)
{
    int i = 0;
    i++;
    i += 2;
}

void InputHandler::handleMouseInput(const std::vector<MouseInput>& inputs)
{
    int i = 0;
    i++;
    i += 2;
}

// void InputHandler::run()
// {
//     for (auto& controlScheme : m_controlScheme)
//     {
//         if (!controlScheme->isActive()) continue;
//         for (auto& actionMaps : controlScheme->actionsMaps())
//         {
//             if (!actionMaps->isActive()) continue;
//             for (Action& action : actionMaps->actions())
//             {
//                 if (action.isActive()) continue;

//                 for (auto binding : action.bindings())
//                 {
//                     for (auto input : binding->inputs())
//                     {
//                         switch (input.first)
//                         {
//                             case InputType::GamepadAxis:
//                             {
//                                 binding->setValue(
//                                     input.first, input.second,
//                                     getAxisValueFromGamepad(
//                                         input.second,
//                                         controlScheme->gamepadId()));
//                                 break;
//                             }
//                             case InputType::GamepadButton:
//                             {
//                                 binding->setValue(
//                                     input.first, input.second,
//                                     getButtonValueFromGamepad(
//                                         input.second,
//                                         controlScheme->gamepadId()));
//                                 break;
//                             }
//                             case InputType::Keyboard:
//                             {
//                                 binding->setValue(
//                                     input.first, input.second,
//                                     glfwGetKey(m_window, input.second));
//                                 break;
//                             }
//                             case InputType::MouseButton:
//                             {
//                                 binding->setValue(
//                                     input.first, input.second,
//                                     glfwGetMouseButton(m_window,
//                                     input.second));
//                                 break;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
