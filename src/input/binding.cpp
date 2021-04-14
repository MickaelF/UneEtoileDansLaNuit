#include "binding.h"

#include <algorithm>

std::vector<Binding*> Binding::bindings;

BinaryBinding::BinaryBinding(InputType type, int key, Action& action,
                             const std::string& name)
    : Binding(action, name),
      m_type(type),
      m_key(key)
{
}

void BinaryBinding::setValue(InputType type, int key, float value) {}

void BinaryBinding::setValue(InputType type, int key, int value)
{
    m_pressed = value;
}

const std::vector<std::pair<InputType, int>> BinaryBinding::inputs() const
{
    return {std::make_pair(m_type, m_key)};
}

RangeBinding::RangeBinding(InputType axis, int key, Action& action,
                           const std::string& name)
    : Binding(action, name)
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

RangeBinding::RangeBinding(InputType negative, int negativeKey,
                           InputType positive, int positiveKey, Action& action,
                           const std::string& name)
    : Binding(action, name)
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

void RangeBinding::setValue(InputType type, int key, float value)
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

void RangeBinding::setValue(InputType type, int key, int value)
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

const std::vector<std::pair<InputType, int>> RangeBinding::inputs() const
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

float RangeBinding::value() const
{
    if (m_axis.index() == 0)
        return std::get<0>(m_axis).value;
    else
        return std::get<1>(m_axis).negativeValue +
               std::get<1>(m_axis).positiveValue;
}

Vector2Binding::Vector2Binding(InputType horizontalType, int horizontalKey,
                               InputType verticalType, int verticalKey,
                               Action& action, const std::string& name)
    : Binding(action, name)
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

Vector2Binding::Vector2Binding(InputType leftType, int leftKey,
                               InputType topType, int topKey,
                               InputType rightType, int rightKey,
                               InputType bottomType, int bottomKey,
                               Action& action, const std::string& name)
    : Binding(action, name)
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

void Vector2Binding::setValue(InputType type, int key, float value)
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

void Vector2Binding::setValue(InputType type, int key, int value)
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

const std::vector<std::pair<InputType, int>> Vector2Binding::inputs() const
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

glm::vec2 Vector2Binding::value() const
{
    if (m_vector2D.index() == 0)
        return glm::vec2 {std::get<0>(m_vector2D).horizontalValue,
                          std::get<0>(m_vector2D).verticalValue};
    else
        return glm::vec2 {std::get<1>(m_vector2D).leftValue +
                              std::get<1>(m_vector2D).rightValue,
                          std::get<1>(m_vector2D).topValue +
                              std::get<1>(m_vector2D).bottomValue};
}
