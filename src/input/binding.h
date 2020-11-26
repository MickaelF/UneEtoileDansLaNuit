#pragma once
#include <glm/glm.hpp>
#include <variant>

class Action;

enum class InputType
{
    MouseButton,
    Keyboard,
    GamepadAxis,
    GamepadButton
};

/*
    Type de Binding :
        - button : value entre -1 et 1 (bouton ou axe unique (x ou y du joystick
   gauche ou droit uniquement))
        - 2D Vector : valeur entre (-1, -1) et (1, 1). Peut être un joystick
   (deux axes) ou un composé (quatres boutons)

*/
class Binding
{
public:
    // virtual const std::vector<std::pair<InputType, int>> inputs() = 0;
};

class ButtonBinding : public Binding
{
public:
    explicit ButtonBinding(InputType type, int key);
    // const std::vector<std::pair<InputType, int>> inputs() override;
    void setValue(unsigned int state);

private:
    InputType m_type;
    int m_key;
    bool m_started;
    bool m_held;
    bool m_released;
};

class AxisBinding : public Binding
{
public:
    explicit AxisBinding(InputType axis, int key);
    explicit AxisBinding(InputType negative, int negativeKey,
                         InputType positive, int positiveKey);

    void setValue(float val);
    void setValue(InputType type, int key, bool pressed);

private:
    struct Axis
    {
        InputType axis;
        int key;
        float value {};
    };

    struct TwoButtonAxis
    {
        InputType negative;
        int negativeKey;
        InputType positive;
        int positiveKey;
        int positiveValue {};
        int negativeValue {};
    };

    std::variant<Axis, TwoButtonAxis> m_axis;
};

class Vector2DBinding
{
public:
    Vector2DBinding(InputType horizontalType, int horizontalKey,
                    InputType verticalType, int verticalKey);
    Vector2DBinding(InputType leftType, int leftKey, InputType topType,
                    int topKey, InputType rightType, int rightKey,
                    InputType bottomType, int bottomKey);

private:
    struct TwoAxisVector
    {
        InputType horizontalType;
        int horizontalKey;
        InputType verticalType;
        int verticalKey;
        float horizontalValue {};
        float verticalValue {};
    };

    struct FourButtonVector
    {
        InputType leftType;
        int leftKey;
        InputType topType;
        int topKey;
        InputType rightType;
        int rightKey;
        InputType bottomType;
        int bottomKey {};
        int leftValue {};
        int topValue {};
        int rightValue {};
        int bottomValue {};
    };
    std::variant<TwoAxisVector, FourButtonVector> m_vector2D;
};