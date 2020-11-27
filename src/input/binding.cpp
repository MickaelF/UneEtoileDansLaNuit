#include "binding.h"

#include <algorithm>

ButtonBinding::ButtonBinding(InputType type, int key, const std::string& name)
    : Binding(name),
      m_type(type),
      m_key(key)
{
}

void ButtonBinding::setValue(InputType type, int key, float value) {}

void ButtonBinding::setValue(InputType type, int key, int value)
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

const std::vector<std::pair<InputType, int>> ButtonBinding::inputs() const
{
    return {std::make_pair(m_type, m_key)};
}

AxisBinding::AxisBinding(InputType axis, int key, const std::string& name)
    : Binding(name)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (axis != InputType::GamepadAxis)
    {
        // TODO Send an exception.
        return;
    }
#endif
    m_axis = Axis {axis, key};
}

AxisBinding::AxisBinding(InputType negative, int negativeKey,
                         InputType positive, int positiveKey,
                         const std::string& name)
    : Binding(name)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (negative == InputType::GamepadAxis ||
        positive == InputType::GamepadAxis)
    {
        // TODO Send an exception
        return;
    }
#endif
    m_axis = TwoButtonAxis {negative, negativeKey, positive, positiveKey};
}

void AxisBinding::setValue(InputType type, int key, float value)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (m_axis.index() != 0)
    {
        // TODO Send exception
        return;
    }
#endif
    std::get<Axis>(m_axis).value = value;
}

void AxisBinding::setValue(InputType type, int key, int value)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (m_axis.index() != 1)
    {
        // TODO Send exception
        return;
    }
#endif
    auto& axis = std::get<TwoButtonAxis>(m_axis);

    if (axis.negative == type && axis.negativeKey == key)
        axis.negativeValue = -1;
    else
        axis.positiveValue = 1;
}

const std::vector<std::pair<InputType, int>> AxisBinding::inputs() const
{
    if (m_axis.index() == 0)
    {
        auto& axis = std::get<Axis>(m_axis);
        return {std::make_pair(axis.type, axis.key)};
    }
    else
    {
        auto& axis = std::get<TwoButtonAxis>(m_axis);
        return {std::make_pair(axis.negative, axis.negativeKey),
                std::make_pair(axis.positive, axis.positiveKey)};
    }
}

Vector2DBinding::Vector2DBinding(InputType horizontalType, int horizontalKey,
                                 InputType verticalType, int verticalKey,
                                 const std::string& name)
    : Binding(name)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (horizontalType != InputType::GamepadAxis ||
        verticalType != InputType::GamepadAxis)
    {
        // TODO Send exception
        return;
    }
#endif
    m_vector2D = TwoAxisVector {horizontalType, horizontalKey, verticalType,
                                verticalKey};
}

Vector2DBinding::Vector2DBinding(InputType leftType, int leftKey,
                                 InputType topType, int topKey,
                                 InputType rightType, int rightKey,
                                 InputType bottomType, int bottomKey,
                                 const std::string& name)
    : Binding(name)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (leftType == InputType::GamepadAxis ||
        topType == InputType::GamepadAxis ||
        rightType == InputType::GamepadAxis ||
        bottomType == InputType::GamepadAxis)
    {
        // TODO Send an exception
        return;
    }
#endif
    m_vector2D = FourButtonVector {leftType,  leftKey,  topType,    topKey,
                                   rightType, rightKey, bottomType, bottomKey};
}

void Vector2DBinding::setValue(InputType type, int key, float value)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (m_vector2D.index() != 0)
    {
        // TODO Send exception
        return;
    }
#endif
    auto& vector = std::get<TwoAxisVector>(m_vector2D);
    if (type == vector.horizontalType && key == vector.horizontalValue)
        vector.horizontalValue = value;
    else
        vector.verticalValue = value;
}

void Vector2DBinding::setValue(InputType type, int key, int value)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (m_vector2D.index() != 1)
    {
        // TODO Send exception
        return;
    }
#endif
    auto& vector = std::get<FourButtonVector>(m_vector2D);
    if (type == vector.leftType && key == vector.leftKey)
        vector.leftValue = value;
    else if (type == vector.topType && key == vector.topKey)
        vector.topValue = value;
    else if (type == vector.rightType && key == vector.rightKey)
        vector.rightValue = value;
    else
        vector.bottomValue = value;
}

const std::vector<std::pair<InputType, int>> Vector2DBinding::inputs() const
{
    if (m_vector2D.index() == 0)
    {
        auto& vector = std::get<TwoAxisVector>(m_vector2D);
        return {std::make_pair(vector.horizontalType, vector.horizontalKey),
                std::make_pair(vector.verticalType, vector.verticalKey)};
    }
    else
    {
        auto& vector = std::get<FourButtonVector>(m_vector2D);
        return {std::make_pair(vector.leftType, vector.leftKey),
                std::make_pair(vector.topType, vector.topKey),
                std::make_pair(vector.rightType, vector.rightKey),
                std::make_pair(vector.bottomType, vector.bottomKey)};
    }
}
