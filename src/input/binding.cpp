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
    m_axis = TwoButtonAxis {negative, negativeKey, positive, positiveKey};
}

void AxisBinding::setValue(float value)
{
    if (m_axis.index() != 0)
    {
        // TODO Send exception
        return;
    }
    std::get<Axis>(m_axis).value = value;
}

void AxisBinding::setValue(InputType type, int key, bool pressed)
{
    if (m_axis.index() != 1)
    {
        // TODO Send exception
        return;
    }
    auto& axis = std::get<TwoButtonAxis>(m_axis);

    if (axis.negative == type && axis.negativeKey == key)
        axis.negativeValue = -1.0f;
    else
        axis.positiveValue = 1.0f;
}

Vector2DBinding::Vector2DBinding(InputType horizontalType, int horizontalKey,
                                 InputType verticalType, int verticalKey)
{
    if (horizontalType != InputType::GamepadAxis ||
        verticalType != InputType::GamepadAxis)
    {
        // TODO Send exception
        return;
    }
    m_vector2D = TwoAxisVector {horizontalType, horizontalKey, verticalType,
                                verticalKey};
}

Vector2DBinding::Vector2DBinding(InputType leftType, int leftKey,
                                 InputType topType, int topKey,
                                 InputType rightType, int rightKey,
                                 InputType bottomType, int bottomKey)
{
    if (leftType == InputType::GamepadAxis ||
        topType == InputType::GamepadAxis ||
        rightType == InputType::GamepadAxis ||
        bottomType == InputType::GamepadAxis)
    {
        // TODO Send an exception
        return;
    }
    m_vector2D = FourButtonVector {leftType,  leftKey,  topType,    topKey,
                                   rightType, rightKey, bottomType, bottomKey};
}