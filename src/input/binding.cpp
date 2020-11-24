#include "binding.h"

#include <algorithm>

ButtonBinding::ButtonBinding(InputType type, int key) : m_type(type), m_key(key)
{
}

void ButtonBinding::setValue(unsigned int value)
{
    if (value)
    {
        if (m_held) return;
        if (m_started)
        {
            m_started = false;
            m_held = true;
        }
        else
        {
            m_started = true;
            if (m_released) m_released = false;
        }
    }
    else
    {
        if (m_started || m_held)
        {
            m_started = false;
            m_held = false;
            m_released = true;
        }
        else if (m_released)
        {
            m_released = false;
        }
    }
}

AxisBinding::AxisBinding(InputType axis, int key)
{
    if (axis != InputType::GamepadAxis)
    {
        // TODO Send an exception.
        return;
    }
    m_axis = Axis {axis, key};
}

AxisBinding::AxisBinding(InputType negative, int negativeKey,
                         InputType positive, int positiveKey)
{
    if (negative == InputType::GamepadAxis ||
        positive == InputType::GamepadAxis)
    {
        // TODO Send an exception
        return;
    }
    m_axis = TwoButtonAxis {negative, positive, negativeKey, positiveKey};
}