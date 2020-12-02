#include "inputhandler.h"

#include <pttk/executiontimer.h>

#include "GLFW/glfw3.h"
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

void InputHandler::setWindow(GLFWwindow* window)
{
    m_window = window;
    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void InputHandler::run()
{
    glfwPollEvents();
    for (auto& controlScheme : m_controlScheme)
    {
        if (!controlScheme->isActive()) continue;
        for (auto& actionMaps : controlScheme->actionsMaps())
        {
            if (!actionMaps->isActive()) continue;
            for (Action& action : actionMaps->actions())
            {
                if (action.isActive()) continue;

                for (auto binding : action.bindings())
                {
                    for (auto input : binding->inputs())
                    {
                        switch (input.first)
                        {
                            case InputType::GamepadAxis:
                            {
                                binding->setValue(
                                    input.first, input.second,
                                    getAxisValueFromGamepad(
                                        input.second,
                                        controlScheme->gamepadId()));
                                break;
                            }
                            case InputType::GamepadButton:
                            {
                                binding->setValue(
                                    input.first, input.second,
                                    getButtonValueFromGamepad(
                                        input.second,
                                        controlScheme->gamepadId()));
                                break;
                            }
                            case InputType::Keyboard:
                            {
                                binding->setValue(
                                    input.first, input.second,
                                    glfwGetKey(m_window, input.second));
                                break;
                            }
                            case InputType::MouseButton:
                            {
                                binding->setValue(
                                    input.first, input.second,
                                    glfwGetMouseButton(m_window, input.second));
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

float InputHandler::getAxisValueFromGamepad(int key,
                                            std::optional<int> gamepadId)
{
    GLFWgamepadstate state {};
    if (gamepadId.has_value())
    {
        if (glfwGetGamepadState(gamepadId.value(), &state))
            return state.axes[key];
    }
    else
    {
        for (int i = 0; i < GLFW_JOYSTICK_LAST; ++i)
        {
            if (glfwJoystickIsGamepad(i) &&
                glfwGetGamepadState(gamepadId.value(), &state))
                return state.axes[key];
        }
    }
    return .0f;
}
int InputHandler::getButtonValueFromGamepad(int key,
                                            std::optional<int> gamepadId)
{
    GLFWgamepadstate state {};
    if (gamepadId.has_value())
    {
        if (glfwGetGamepadState(gamepadId.value(), &state))
            return state.buttons[key];
    }
    else
    {
        for (int i = 0; i < GLFW_JOYSTICK_LAST; ++i)
        {
            if (glfwJoystickIsGamepad(i) &&
                glfwGetGamepadState(gamepadId.value(), &state))
                return state.buttons[key];
        }
    }
    return 0;
}